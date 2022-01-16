#ifndef QUATERNIONFILTER_H
#define QUATERNIONFILTER_H
#include <inttypes.h>
#include <math.h>

namespace MPU9250 {

enum class QuatFilterSel {
	NONE,
	MADGWICK,
	MAHONY,
};

class Filter {
private:
	double deltaT{0.};
	uint32_t newTime{0}, oldTime{0};
protected:
	virtual void update_impl(float ax, float ay, float az,
                           float gx, float gy, float gz,
                           float mx, float my, float mz,
                           double deltaT, float* q) =0;
public:
	void update(float ax, float ay, float az,
              float gx, float gy, float gz,
              float mx, float my, float mz, float* q);
};

class SimpleFilter : public Filter {
protected:
	virtual void update_impl(float ax, float ay, float az,
                           float gx, float gy, float gz,
                           float mx, float my, float mz,
                           double deltaT, float* q) override;
};

class MadgwickFilter : public Filter {
private:
	// gyroscope measurement error in rads/s (start at 40 deg/s)
	float GyroMeasError;
	// gyroscope measurement drift in rad/s/s (start at 0.0 deg/s/s)
	float GyroMeasDrift;
	// compute beta
	float beta;
	// compute zeta, the other free parameter in the Madgwick scheme
	// usually set to a small or zero value
	float zeta;
public:
	MadgwickFilter();
	virtual void update_impl(float ax, float ay, float az,
                           float gx, float gy, float gz,
                           float mx, float my, float mz,
                           double deltaT, float* q) override;
};

class MahonyFilter : public Filter {
	// Mahony accelleration filter
	// Mahony scheme uses proportional and integral filtering on
	// the error between estimated reference vector (gravity) and measured one.
	// Madgwick's implementation of Mayhony's AHRS algorithm.
	// See: http://www.x-io.co.uk/node/8#open_source_ahrs_and_imu_algorithms
	// Free parameters in the Mahony filter and fusion scheme,
	// Kp for proportional feedback, Ki for integral
	// float Kp = 30.0;
	// float Ki = 0.0;
	// with MPU-9250, angles start oscillating at Kp=40. Ki does not seem to help and is not required.
	// with MPU-6050, some instability observed at Kp=100 Now set to 30.
private:
	float Kp = 30.0;
	float Ki = 0.0;
public:
	virtual void update_impl(float ax, float ay, float az,
                           float gx, float gy, float gz,
                           float mx, float my, float mz,
                           double deltaT, float* q) override;
};

} // namespace MPU9250

#endif  // QUATERNIONFILTER_H
