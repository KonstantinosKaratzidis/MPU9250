#ifndef MPU9250_H
#define MPU9250_H
#include <MPU9250RegisterMap.h>
#include <QuaternionFilter.h>
#include <stdint.h>

namespace MPU9250 {

class Driver {
public:
	virtual void write(uint8_t address, const uint8_t *data, int length) =0;
	virtual void read(uint8_t address, uint8_t *data, int length) =0;
	virtual void delay(uint32_t milli_seconds) =0;
};

constexpr uint8_t MPU9250_WHOAMI_DEFAULT_VALUE {0x71};
constexpr uint8_t MPU9255_WHOAMI_DEFAULT_VALUE {0x73};
constexpr uint8_t MPU6500_WHOAMI_DEFAULT_VALUE {0x70};
constexpr uint8_t AK8963_WHOAMI_DEFAULT_VALUE {0x48};

enum class ACCEL_FS_SEL {
	A2G,
	A4G,
	A8G,
	A16G
};

enum class GYRO_FS_SEL {
	G250DPS,
	G500DPS,
	G1000DPS,
	G2000DPS
};
enum class MAG_OUTPUT_BITS {
	M14BITS,
	M16BITS
};

enum class FIFO_SAMPLE_RATE : uint8_t {
	SMPL_1000HZ,
	SMPL_500HZ,
	SMPL_333HZ,
	SMPL_250HZ,
	SMPL_200HZ,
	SMPL_167HZ,
	SMPL_143HZ,
	SMPL_125HZ,
};

enum class GYRO_DLPF_CFG : uint8_t {
	DLPF_250HZ,
	DLPF_184HZ,
	DLPF_92HZ,
	DLPF_41HZ,
	DLPF_20HZ,
	DLPF_10HZ,
	DLPF_5HZ,
	DLPF_3600HZ,
};

enum class ACCEL_DLPF_CFG : uint8_t {
	DLPF_218HZ_0,
	DLPF_218HZ_1,
	DLPF_99HZ,
	DLPF_45HZ,
	DLPF_21HZ,
	DLPF_10HZ,
	DLPF_5HZ,
	DLPF_420HZ,
};

struct Setting {
	ACCEL_FS_SEL      accel_fs_sel      {ACCEL_FS_SEL::A16G};
	GYRO_FS_SEL       gyro_fs_sel       {GYRO_FS_SEL::G2000DPS};
	MAG_OUTPUT_BITS   mag_output_bits   {MAG_OUTPUT_BITS::M16BITS};
	FIFO_SAMPLE_RATE  fifo_sample_rate  {FIFO_SAMPLE_RATE::SMPL_200HZ};
	uint8_t           gyro_fchoice      {0x03};
	GYRO_DLPF_CFG     gyro_dlpf_cfg     {GYRO_DLPF_CFG::DLPF_41HZ};
	uint8_t           accel_fchoice     {0x01};
	ACCEL_DLPF_CFG    accel_dlpf_cfg    {ACCEL_DLPF_CFG::DLPF_45HZ};
};

enum class Error : uint8_t {
	NONE,
	I2C_ADDRESS,     // invalid i2c address
	CONNECTION_MPU,  // mpu not connected
	CONNECTION_MAG,  // magnetometer not connected
	CONNECTION,      // mpu or magnetometer not connected
};

class MPU {
public:
	static constexpr uint16_t CALIB_GYRO_SENSITIVITY {131};     // LSB/degrees/sec
	static constexpr uint16_t CALIB_ACCEL_SENSITIVITY {16384};  // LSB/g

private:
	// Device address when AD0 = 0
	static constexpr uint8_t MPU9250_DEFAULT_ADDRESS {0x68};
	// magnetometer address
	static constexpr uint8_t AK8963_ADDRESS {0x0C};
	// TODO: this should be configured!!
	static constexpr uint8_t MAG_MODE {0x06};  // 0x02 for 8 Hz, 0x06 for 100 Hz continuous magnetometer data read

	uint8_t mpu_i2c_addr {MPU9250_DEFAULT_ADDRESS};

	// settings
	Setting setting;

	// resolutions per bit
	float acc_resolution  {0.f};
	float gyro_resolution {0.f};
	float mag_resolution  {0.f};

	// Calibration Parameters
	float acc_bias[3] {0., 0., 0.};      // in ACCEL_FS_SEL: 2g
	float gyro_bias[3] {0., 0., 0.};     // in GYRO_FS_SEL: 250dps
	float mag_bias[3] {0., 0., 0.};      // in MAG_OUTPUT_BITS: 16BITS
	float mag_bias_factory[3] {0., 0., 0.};
	float mag_scale[3] {1., 1., 1.};
	float magnetic_declination = -7.51;  // Japan, 24th June

	// Temperature
	int16_t temperature_count {0}; // temperature raw count output
	float temperature {0.f};       // in Celcius

	// Self Test
	float self_test_result[6] {0.f};  // holds results of gyro and accelerometer self test

	// IMU Data
	float a[3] {0.f, 0.f, 0.f};
	float g[3] {0.f, 0.f, 0.f};
	float m[3] {0.f, 0.f, 0.f};
	float q[4] = {1.0f, 0.0f, 0.0f, 0.0f};  // quaternion(w, x, y, z)
	float rpy[3] {0.f, 0.f, 0.f};
  // linear acceleration (acceleration with gravity component subtracted)
	float lin_acc[3] {0.f, 0.f, 0.f};

	// filter
	Filter* filter;
	size_t n_filter_iter {1};

	// Other settings
	bool has_connected {false};
	bool b_ahrs {true};
	bool b_verbose {false};

	// platform functions
	Driver* driver;

public:
	Error setup(uint8_t addr, Driver& w,
              Filter& filter, const Setting& setting = Setting{});

	bool selftest() { return self_test_impl(); }
	void verbose(const bool b) { b_verbose = b; }
	void ahrs(const bool b) { b_ahrs = b; }

	// connection
	bool isConnected() {
		has_connected = isConnectedMPU9250() && isConnectedAK8963();
		return has_connected;
	}
	bool isConnectedMPU9250();
	bool isConnectedAK8963();

	// sleep
	void sleep(bool b);
	bool isSleeping() {
		return read_byte(mpu_i2c_addr, PWR_MGMT_1) & PWR_MGMT_1_SLEEP;
	}

	// calibration
	void calibrateAccelGyro() { calibrate_acc_gyro_impl(); }
	void calibrateMag()       { calibrate_mag_impl(); }

	// filter
	void setFilterIterations(const size_t n) { if (n > 0) n_filter_iter = n; }

	// update
	bool available() {
		return has_connected && 
			(read_byte(mpu_i2c_addr, INT_STATUS) & INT_STATUS_RAW_RDY);
	}
	void update_rpy(float qw, float qx, float qy, float qz);
	void update_accel_gyro();
	void update_mag();
	bool update();

	float getRoll()  const { return rpy[0]; }
	float getPitch() const { return rpy[1]; }
	float getYaw()   const { return rpy[2]; }

	float getEulerX() const { return  rpy[0]; }
	float getEulerY() const { return -rpy[1]; }
	float getEulerZ() const { return -rpy[2]; }

	float getQuaternionW() const { return q[0]; }
	float getQuaternionX() const { return q[1]; }
	float getQuaternionY() const { return q[2]; }
	float getQuaternionZ() const { return q[3]; }

	// accelerometer
	float getAcc(uint8_t i) const       { return (i < 3) ? a[i] : 0.f; }
	float getLinearAcc(uint8_t i) const { return (i < 3) ? lin_acc[i] : 0.f; }
	float getAccX() const { return a[0]; }
	float getAccY() const { return a[1]; }
	float getAccZ() const { return a[2]; }
	float getLinearAccX() const { return lin_acc[0]; }
	float getLinearAccY() const { return lin_acc[1]; }
	float getLinearAccZ() const { return lin_acc[2]; }
	float getAccBias(uint8_t i) const { return (i < 3) ? acc_bias[i] : 0.f; }
	void setAccBias(const float x, const float y, const float z) {
		acc_bias[0] = x; acc_bias[1] = y; acc_bias[2] = z;
		write_accel_offset();
	}
	float getAccBiasX() const { return acc_bias[0]; }
	float getAccBiasY() const { return acc_bias[1]; }
	float getAccBiasZ() const { return acc_bias[2]; }

	// gyroscope
	float getGyro(uint8_t i) const { return (i < 3) ? g[i] : 0.f; }
	float getGyroX() const { return g[0]; }
	float getGyroY() const { return g[1]; }
	float getGyroZ() const { return g[2]; }
	float getGyroBias(uint8_t i) const { return (i < 3) ? gyro_bias[i] : 0.f; }
	void setGyroBias(const float x, const float y, const float z) {
		gyro_bias[0] = x; gyro_bias[1] = y; gyro_bias[2] = z;
		write_gyro_offset();
	}
	float getGyroBiasX() const { return gyro_bias[0]; }
	float getGyroBiasY() const { return gyro_bias[1]; }
	float getGyroBiasZ() const { return gyro_bias[2]; }

	// magnetometer
	float getMag(uint8_t i) const { return (i < 3) ? m[i] : 0.f; }
	float getMagX() const { return m[0]; }
	float getMagY() const { return m[1]; }
	float getMagZ() const { return m[2]; }
	float getMagScale(uint8_t i) const { return (i < 3) ? mag_scale[i] : 0.f; }
	void setMagScale(float x, float y, float z) {
		mag_scale[0] = x; mag_scale[1] = y; mag_scale[2] = z;
	}
	float getMagScaleX() const { return mag_scale[0]; }
	float getMagScaleY() const { return mag_scale[1]; }
	float getMagScaleZ() const { return mag_scale[2]; }
	float getMagBias(uint8_t i) const { return (i < 3) ? mag_bias[i] : 0.f; }
	void setMagBias(float x, float y, float z) {
		mag_bias[0] = x; mag_bias[1] = y; mag_bias[2] = z;
	}
	float getMagBiasX() const { return mag_bias[0]; }
	float getMagBiasY() const { return mag_bias[1]; }
	float getMagBiasZ() const { return mag_bias[2]; }
	void setMagneticDeclination(float d) { magnetic_declination = d; }

	// temperature
	float getTemperature() const { return temperature; }

private:
	// initialization
	void initMPU9250();
	void initAK8963();
	// Accelerometer and gyroscope self test; check calibration wrt
	// factory settings
	// Should return percent deviation from factory trim values,
	// +/- 14 or less deviation is a pass
	bool self_test_impl();

	void read_accel_gyro(int16_t* destination);
	bool read_mag(int16_t* destination);
	int16_t read_temperature_data();

	// Function which accumulates gyro and accelerometer data after device
	// initialization. It calculates the average of the at-rest readings
	// and then loads the resulting offsets into accelerometer and gyro
	// bias registers.
	// ACCEL_FS_SEL: 2g (maximum sensitivity)
	// GYRO_FS_SEL: 250dps (maximum sensitivity)
	void calibrate_acc_gyro_impl();
	void set_acc_gyro_to_calibration();
	void collect_acc_gyro_data_to(float* a_bias, float* g_bias);
	void write_accel_offset();
	void write_gyro_offset();
	// mag calibration is executed in MAG_OUTPUT_BITS: 16BITS
	void calibrate_mag_impl();
	void collect_mag_data_to(float* m_bias, float* m_scale);

	// resolution per bit (helpers)
	float get_acc_resolution(ACCEL_FS_SEL accel_af_sel) const; 
	float get_gyro_resolution(GYRO_FS_SEL gyro_fs_sel) const;
	float get_mag_resolution(MAG_OUTPUT_BITS mag_output_bits) const;

	void write_byte(uint8_t address, uint8_t reg, uint8_t data);
	uint8_t read_byte(uint8_t address, uint8_t reg);
	void read_bytes(uint8_t address, uint8_t reg,
                  uint8_t count, uint8_t* dest);
	void print_i2c_error();
};

} // namespace MPU9250

#endif  // MPU9250_H
