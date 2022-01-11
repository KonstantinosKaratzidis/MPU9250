#ifndef MPU9250REGISTERMAP_H
#define MPU9250REGISTERMAP_H

// identification register (117)
#define WHO_AM_I_MPU9250       0x75 // Should return 0x71
#define WHO_AM_I_MPU9250_VALUE 0x71

////////////////////////////////////////////////////
//           Power management and reset
////////////////////////////////////////////////////

// Power Management 1 (107)
#define PWR_MGMT_1               0x6B
#define PWR_MGMT_1_H_RESET       (1 << 7)
#define PWR_MGMT_1_SLEEP         (1 << 6)
#define PWR_MGMT_1_CYCLE         (1 << 5)
#define PWR_MGMT_1_GYRO_STANDBY  (1 << 4)
#define PWR_MGMT_1_PD_PTAT       (1 << 3)
#define PWR_MGMT_1_CLKSEL(s)     ((s) & 0b111)
#define PWR_MGMT_1_CLKSEL_MASK   (0b111)

// Power Management 2 (108)
#define PWR_MGMT_2             0x6C
#define PWR_MGMT_2_DISABLE_XA  (1 << 5)
#define PWR_MGMT_2_DISABLE_YA  (1 << 4)
#define PWR_MGMT_2_DISABLE_ZA  (1 << 3)
#define PWR_MGMT_2_DISABLE_XG  (1 << 2)
#define PWR_MGMT_2_DISABLE_YG  (1 << 1)
#define PWR_MGMT_2_DISABLE_ZG  (1 << 0)

// Signal Path Reset (120)
#define SIGNAL_PATH_RESET        0x68
#define SIGNAL_PATH_RESET_GYRO   (1 << 2)
#define SIGNAL_PATH_RESET_ACCEL  (1 << 1)
#define SIGNAL_PATH_RESET_TEMP   (1 << 0)

// User Control (106)
#define USER_CTRL               0x6A
#define USER_CTRL_FIFO_EN       (1 << 6)
#define USER_CTRL_I2C_MST_EN    (1 << 5)
#define USER_CTRL_I2C_IF_DIS    (1 << 4)
#define USER_CTRL_FIFO_RST      (1 << 2)
#define USER_CTRL_I2C_MST_RST   (1 << 1)
#define USER_CTRL_SIG_COND_RST  (1 << 0)


////////////////////////////////////////////////////
//                   Interrupts
////////////////////////////////////////////////////

// INT Pin / Bypass Enable Configuration (55)
#define INT_PIN_CFG                    0x37
#define INT_PIN_CFG_ACTL               (1 << 7)
#define INT_PIN_CFG_OPEN               (1 << 6)
#define INT_PIN_CFG_LATCH_INT_EN       (1 << 5)
#define INT_PIN_CFG_ANYRD_2CLEAR       (1 << 4)
#define INT_PIN_CFG_ACTL_FSYNC         (1 << 3)
#define INT_PIN_CFG_FSYNC_INT_MODE_EN  (1 << 2)
#define INT_PIN_CFG_BYPASS_EN          (1 << 1)

// Interrupt Enable (56)
#define INT_ENABLE                0x38
#define INT_ENABLE_WOM            (1 << 6)
#define INT_ENABLE_FIFO_OVERFLOW  (1 << 4)
#define INT_ENABLE_FSYNC          (1 << 3)
#define INT_ENABLE_RAW_RDY        (1 << 0)

// Interrupt Status (58)
#define INT_STATUS                0x3A
#define INT_STATUS_WOM            (1 << 6)
#define INT_STATUS_FIFO_OVERFLOW  (1 << 4)
#define INT_STATUS_FSYNC          (1 << 3)
#define INT_STATUS_RAW_RDY        (1 << 0)

// Accelerometer Interrupt Control (105)
// (the same register as MOT_DETECT_CTRL)
#define MOT_DETECT_CTRL       0x69
#define MOT_DETECT_CTRL_EN   (1 << 7)
#define MOT_DETECT_CTRL_MODE (1 << 6)
#define ACCEL_INTEL_CTRL      0x69
#define ACCEL_INTEL_CTRL_EN   (1 << 7)
#define ACCEL_INTER_CTRL_MODE (1 << 6)

// Wake-on Motion Threshold (31)
#define WOM_THR          0x1F

//////////////////////////////////////////////////////
//               Common Configuration
//////////////////////////////////////////////////////

// sample rate divider (25)
// has an effect only when low pass filter is activated
#define SMPLRT_DIV       0x19

// Configuration (also affects gyroscope) (26)
#define MPU_CONFIG                0x1A
#define MPU_CONFIG_FIFO_MODE      (1 << 6)
#define MPU_CONFIG_SYNC_SET(s)    (((s) & 0b111) << 3)
#define MPU_CONFIG_SYNC_SET_MASK  (0b111 < 3)
#define MPU_CONFIG_DLPF_CFG(s)    ((s) & 0b111)
#define MPU_CONFIG_DLPF_CFG_MASK  (0b111)

//////////////////////////////////////////////////////
//                    Gyroscope
//////////////////////////////////////////////////////

// Gyroscope Configuration (27)
#define GYRO_CONFIG                 0x1B
#define GYRO_CONFIG_XGYRO_Cten      (1 << 7)
#define GYRO_CONFIG_YGYRO_Cten      (1 << 6)
#define GYRO_CONFIG_ZGYRO_Cten      (1 << 5)
#define GYRO_CONFIG_FS_SEL(s)       (((s) & 0b11) << 3)
#define GYRO_CONFIG_FS_SEL_MASK     (0b11 << 3)
#define GYRO_CONFIG_Fchoice_b(s)    ((s) & 0b11)
#define GYRO_CONFIG_Fchoice_b_MASK  (0b11)

// Gyroscope Self Test Registers (0, 1, 2)
#define SELF_TEST_X_GYRO 0x00
#define SELF_TEST_Y_GYRO 0x01
#define SELF_TEST_Z_GYRO 0x02

// Gyroscope Offset Registers (13-24)
#define XG_OFFSET_H      0x13
#define XG_OFFSET_L      0x14
#define YG_OFFSET_H      0x15
#define YG_OFFSET_L      0x16
#define ZG_OFFSET_H      0x17
#define ZG_OFFSET_L      0x18

//////////////////////////////////////////////////////
//                   Accelerometer
//////////////////////////////////////////////////////

// Accelerometer Configuration (28)
#define ACCEL_CONFIG              0x1C
#define ACCEL_CONFIG_ax_st_en     (1 << 7)
#define ACCEL_CONFIG_ay_st_en     (1 << 6)
#define ACCEL_CONFIG_az_st_en     (1 << 5)
#define ACCEL_CONFIG_FS_SEL(s)    (((s) & 0b11) << 3)
#define ACCEL_CONFIG_FS_SEL_MAKS  (0b11 << 3)

// Accelerometer Configuration 2 (29)
#define ACCEL_CONFIG2               0x1D
#define ACCEL_CONFIG2_fchoice_b     (1 << 3)
#define ACCEL_CONFIG2_DLPFCFG(s)    (((s) & 0b111))
#define ACCEL_CONFIG2_DLPFCFG_MASK  (0b111)

// Low Power Accelerometer ODR Control (30)
#define LP_ACCEL_ODR             0x1E
#define LP_ACCEL_ODR_clksel(s)   ((s) & 0b1111)
#define LP_ACCEL_ODR_clksel_MASK (0b1111)

// Accelerometer Self Test Registers (13-15)
#define SELF_TEST_X_ACCEL 0x0D
#define SELF_TEST_Y_ACCEL 0x0E
#define SELF_TEST_Z_ACCEL 0x0F

// Accelerometer Offset Value Registers (119-126)
#define XA_OFFSET_H      0x77
#define XA_OFFSET_L      0x78
#define YA_OFFSET_H      0x7A
#define YA_OFFSET_L      0x7B
#define ZA_OFFSET_H      0x7D
#define ZA_OFFSET_L      0x7E

/////////////////////////////////////////////////
//                FIFO
/////////////////////////////////////////////////

// FIFO Enable (35)
#define FIFO_EN        0x23
#define FIFO_EN_TEMP   (1 << 7)
#define FIFO_EN_GYROX  (1 << 6)
#define FIFO_EN_GYROY  (1 << 5)
#define FIFO_EN_GYROZ  (1 << 4)
#define FIFO_EN_ACCEL  (1 << 3)
#define FIFO_EN_SLV_2  (1 << 2)
#define FIFO_EN_SLV_1  (1 << 1)
#define FIFO_EN_SLV_0  (1 << 0)

// Fifo Count (114, 115)
#define FIFO_COUNTH      0x72
#define FIFO_COUNTH_MASK (0b11111)
#define FIFO_COUNTL      0x73

// Fifo data (116)
#define FIFO_R_W         0x74

/////////////////////////////////////////////////
//                I2C Master
/////////////////////////////////////////////////

// I2C Master Control (36)
#define I2C_MST_CTRL                0x24
#define I2C_MST_CTRL_MULT_MST_EN    (1 << 7)
#define I2C_MST_CTRL_WAIT_FOR_ES    (1 << 6)
#define I2C_MST_CTRL_SLV_3_FIFO_EN  (1 << 5)
#define I2C_MST_CTRL_P_NSR          (1 << 4)
#define I2C_MST_CTRL_CLK(s)         ((s) & 0b1111)
#define I2C_MST_CTRL_CLK_MASK       (0b1111)

// I2C Master Delay Control (103)
#define I2C_MST_DELAY_CTRL         0x67
#define I2C_MST_DELAY_CTRL_SHADOW  (1 << 7)
#define I2C_MST_DELAY_CTRL_SLV4    (1 << 4)
#define I2C_MST_DELAY_CTRL_SLV3    (1 << 3)
#define I2C_MST_DELAY_CTRL_SLV2    (1 << 2)
#define I2C_MST_DELAY_CTRL_SLV1    (1 << 1)
#define I2C_MST_DELAY_CTRL_SLV0    (1 << 0)

// I2C Master Status (54)
#define I2C_MST_STATUS               0x36
#define I2C_MST_STATUS_PASS_THROUGH  (1 << 7)
#define I2C_MST_STATUS_SLV4_DONE     (1 << 6)
#define I2C_MST_STATUS_LOST_ARB      (1 << 5)
#define I2C_MST_STATUS_SLV4_NACK     (1 << 4)
#define I2C_MST_STATUS_SLV3_NACK     (1 << 3)
#define I2C_MST_STATUS_SLV2_NACK     (1 << 2)
#define I2C_MST_STATUS_SLV1_NACK     (1 << 1)
#define I2C_MST_STATUS_SLV0_NACK     (1 << 0)

//////////////////////////////////////////////
//            I2C slave registers
//////////////////////////////////////////////

// Bitfielfs for slave address register
#define I2C_SLV_ADDR_RW     (1 << 7)
#define I2C_SLV_ADDR_ID(s)  ((s) & 0b1111111)
#define I2C_SLV_ADDR_MASK   (0b1111111)

// Bitfielfs for slave control register
#define I2C_SLV_CTRL_EN         (1 << 7)
#define I2C_SLV_CTRL_BYTE_SW    (1 << 6)
#define I2C_SLV_CTRL_REG_DIS    (1 << 5)
#define I2C_SLV_CTRL_GRP        (1 << 4)
#define I2C_SLV_CTRL_LENG(s)    ((s) & 0b1111)
#define I2C_SLV_CTRL_LENG_MASK  (0b1111)

// slave 0
#define I2C_SLV0_ADDR    0x25
#define I2C_SLV0_REG     0x26
#define I2C_SLV0_CTRL    0x27
#define I2C_SLV0_DO      0x63

// slave 1
#define I2C_SLV1_ADDR    0x28
#define I2C_SLV1_REG     0x29
#define I2C_SLV1_DO      0x64
#define I2C_SLV1_CTRL    0x2A

// slave 2
#define I2C_SLV2_ADDR    0x2B
#define I2C_SLV2_REG     0x2C
#define I2C_SLV2_DO      0x65
#define I2C_SLV2_CTRL    0x2D

// slave 3
#define I2C_SLV3_ADDR    0x2E
#define I2C_SLV3_REG     0x2F
#define I2C_SLV3_DO      0x66
#define I2C_SLV3_CTRL    0x30

// slave 4
// This slave's control register is a bit different
#define I2C_SLV4_ADDR    0x31
#define I2C_SLV4_REG     0x32
#define I2C_SLV4_DO      0x33
#define I2C_SLV4_DI      0x35
#define I2C_SLV4_CTRL    0x34
#define I2C_SLV4_CTRL_EN           (1 << 7)
#define I2C_SLV4_CTRL_INT_EN       (1 << 6)
#define I2C_SLV4_CTRL_REG_DIS      (1 << 5)
#define I2C_SLV4_CTRL_MST_DLY(s)   ((s) & 0b11111)
#define I2C_SLV4_CTRL_MST_DLY_MASK (0b11111)

/////////////////////////////////////////////////
//              Data Registers
/////////////////////////////////////////////////

// data registers (59-96)
#define ACCEL_XOUT_H     0x3B
#define ACCEL_XOUT_L     0x3C
#define ACCEL_YOUT_H     0x3D
#define ACCEL_YOUT_L     0x3E
#define ACCEL_ZOUT_H     0x3F
#define ACCEL_ZOUT_L     0x40
#define TEMP_OUT_H       0x41
#define TEMP_OUT_L       0x42
#define GYRO_XOUT_H      0x43
#define GYRO_XOUT_L      0x44
#define GYRO_YOUT_H      0x45
#define GYRO_YOUT_L      0x46
#define GYRO_ZOUT_H      0x47
#define GYRO_ZOUT_L      0x48
#define EXT_SENS_DATA_00 0x49
#define EXT_SENS_DATA_01 0x4A
#define EXT_SENS_DATA_02 0x4B
#define EXT_SENS_DATA_03 0x4C
#define EXT_SENS_DATA_04 0x4D
#define EXT_SENS_DATA_05 0x4E
#define EXT_SENS_DATA_06 0x4F
#define EXT_SENS_DATA_07 0x50
#define EXT_SENS_DATA_08 0x51
#define EXT_SENS_DATA_09 0x52
#define EXT_SENS_DATA_10 0x53
#define EXT_SENS_DATA_11 0x54
#define EXT_SENS_DATA_12 0x55
#define EXT_SENS_DATA_13 0x56
#define EXT_SENS_DATA_14 0x57
#define EXT_SENS_DATA_15 0x58
#define EXT_SENS_DATA_16 0x59
#define EXT_SENS_DATA_17 0x5A
#define EXT_SENS_DATA_18 0x5B
#define EXT_SENS_DATA_19 0x5C
#define EXT_SENS_DATA_20 0x5D
#define EXT_SENS_DATA_21 0x5E
#define EXT_SENS_DATA_22 0x5F
#define EXT_SENS_DATA_23 0x60

#endif // MPU9250REGISTERMAP_H
