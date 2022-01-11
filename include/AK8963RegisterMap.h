#ifndef AK8963REGISTERMAP_H
#define AK8963REGISTERMAP_H

//Magnetometer Registers
// #define AK8963_ADDRESS   0x0C
#define AK8963_WHO_AM_I  0x00
#define AK8963_WHO_AM_I_VALUE 0x48

// Device Information
#define AK8963_INFO      0x01

// Status 1
#define AK8963_ST1       0x02  // data ready status bit 0
#define AK8963_ST1_DRDY  (1 << 0)
#define AK8963_ST1_DOR   (1 << 1)

// Status 2
#define AK8963_ST2       0x09
#define AK8963_ST2_HOFL  (1 << 3)
#define AK8963_ST2_BITM  (1 << 4)

// Control
#define AK8963_CNTL             0x0A
#define AK8963_CNTL1_BIT        (1 << 4)
#define AK8963_CNTL1_MODE(s)    ((s) & 0b1111)
#define AK8963_CNTL1_MODE_MASK  (0b1111)

// Control 2
#define AK8963_CNTL2       0x0B
#define AK8963_CNTL2_SRST  (1 << 0)

// Self Test Control
#define AK8963_ASTC       0x0C
#define AK8963_ASTC_SELF  (1 << 6)

// Test 1, 2 (only for shipment tests)
#define AK8963_TS1       0x0D
#define AK8963_TS2       0x0E

// I2C disable
#define AK8963_I2CDIS        0x0F
#define AK8963_I2CDIS_MAGIC  (0b00011011)

// Fuse ROM sensitivity adjustment value for x y z
// the formula: adjusted = measurement * ((ASA - 128) * 0.5 / 128 + 1)
// ASA is the adjustment value
#define AK8963_ASAX      0x10
#define AK8963_ASAY      0x11
#define AK8963_ASAZ      0x12

// Measurement Data
// When reading these read until ST2 is also read
#define AK8963_XOUT_L	 0x03  // data
#define AK8963_XOUT_H	 0x04
#define AK8963_YOUT_L	 0x05
#define AK8963_YOUT_H	 0x06
#define AK8963_ZOUT_L	 0x07
#define AK8963_ZOUT_H	 0x08


#endif // AK8963REGISTERMAP_H
