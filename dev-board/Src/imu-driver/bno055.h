#include <stdint.h>
//File Name: bno055.h
//Description: This contains the declarations for BNO055 IMU

//Header Guards
#ifndef BNO055_H_
#define BNO055_H_

//C Public Constants

/**
 * @brief I2C address of the BNO
 */
#define BNO055_ADDRESS 0x28

/**
 * @brief Register addresses for BNO055
 */
typedef enum BNO055_ADDRESSES
{
    CHIP_ID = 0,
    ACC_ID,
    MAG_ID,
    GYR_ID,
    SW_REV_ID_LSB,
    SW_REV_ID_MSB,
    BL_REV_ID,
    PAGE_ID,
    ACC_DATA_X_LSB,
    ACC_DATA_X_MSB,
    ACC_DATA_Y_LSB,
    ACC_DATA_Y_MSB,
    ACC_DATA_Z_LSB,
    ACC_DATA_Z_MSB,
    MAG_DATA_X_LSB,
    MAG_DATA_X_MSB,
    MAG_DATA_Y_LSB,
    MAG_DATA_Y_MSB,
    MAG_DATA_Z_LSB,
    MAG_DATA_Z_MSB,
    GYR_DATA_X_LSB,
    GYR_DATA_X_MSB,
    GYR_DATA_Y_LSB,
    GYR_DATA_Y_MSB,
    GYR_DATA_Z_LSB,
    GYR_DATA_Z_MSB,
    EUL_DATA_X_LSB,
    EUL_DATA_X_MSB,
    EUL_DATA_Y_LSB,
    EUL_DATA_Y_MSB,
    EUL_DATA_Z_LSB,
    EUL_DATA_Z_MSB,
    QUA_DATA_W_LSB,
    QUA_DATA_W_MSB,
    QUA_DATA_X_LSB,
    QUA_DATA_X_MSB,
    QUA_DATA_Y_LSB,
    QUA_DATA_Y_MSB,
    QUA_DATA_Z_LSB,
    QUA_DATA_Z_MSB,
    LIA_DATA_X_LSB,
    LIA_DATA_X_MSB,
    LIA_DATA_Y_LSB,
    LIA_DATA_Y_MSB,
    LIA_DATA_Z_LSB,
    LIA_DATA_Z_MSB,
    GRV_DATA_X_LSB,
    GRV_DATA_X_MSB,
    GRV_DATA_Y_LSB,
    GRV_DATA_Y_MSB,
    GRV_DATA_Z_LSB,
    GRV_DATA_Z_MSB,
    TEMP,
    CALIB_STAT,
    ST_RESULT,
    INT_STA,
    SYS_CLK_STATUS,
    SYS_STATUS,
    SYS_ERR,
    UNIT_SEL,
    OPR_MODE = 0x3D,
    PWR_MODE,
    SYS_TRIGGER,
    TEMP_SOURCE,
    AXIS_MAP_CONFIG,
    AXIS_MAP_SIGN,
    ACC_OFFSET_X_LSB = 0x55,
    ACC_OFFSET_X_MSB,
    ACC_OFFSET_Y_LSB,
    ACC_OFFSET_Y_MSB,
    ACC_OFFSET_Z_LSB,
    ACC_OFFSET_Z_MSB,
    MAG_OFFSET_X_LSB,
    MAG_OFFSET_X_MSB,
    MAG_OFFSET_Y_LSB,
    MAG_OFFSET_Y_MSB,
    MAG_OFFSET_Z_LSB,
    MAG_OFFSET_Z_MSB,
    GYR_OFFSET_X_LSB,
    GYR_OFFSET_X_MSB,
    GYR_OFFSET_Y_LSB,
    GYR_OFFSET_Y_MSB,
    GYR_OFFSET_Z_LSB,
    GYR_OFFSET_Z_MSB,
    ACC_RADIUS_LSB,
    ACC_RADIUS_MSB,
    MAG_RADIUS_LSB,
    MAG_RADIUS_MSB
} BNO055_ADDRESSES;

/**
 * @brief Operational modes for BNO, see datasheet for details
 */
typedef enum OPR_MODES
{
    CONFIGMODE,
    ACCONLY,
    MAGONLY,
    GYROONLY,
    GYROMAG,
    ACCMAG,
    ACCGYRO,
    MAGGYRO,
    AMG,
    IMU,
    COMPASS,
    M4G,
    NDOF_FMC_OFF,
    NDOF
} ORP_MODES;

/**
 * @brief Struct for xyz axis return types
 */
typedef struct bno055_3axis
{
    int16_t x;
    int16_t y;
    int16_t z;
} bno055_3axis;

/**
 * @brief Struct for the Quaternion return type
 */
typedef struct bno055_quat
{
    int16_t w;
    int16_t x;
    int16_t y;
    int16_t z;
} bno055_quat;

/**
 * @brief Struct for the IMU RF data
 */
typedef struct IMU_DATA_t
{
	bno055_3axis accel;
	bno055_3axis gyro;
	bno055_3axis linear;
	uint8_t temp;
} IMU_DATA_t;


//C Public Function Prototypes

/**
 * @brief Get IMU data for RF
 * @ret Returns struct of IMU data
 */
extern IMU_DATA_t bno055GetPacket();

/**
 * @brief Initializes in IMU mode, so only the Accel, Gyro and Relative orientations
 */
extern void bno055Init(void);

/**
 * @brief Acceleration data
 * @ret Returns xyz struct of Acceleration data
 */
extern struct bno055_3axis bno055ReadAccel(void);

/**
 * @brief Gyroscope data
 * @ret Returns xyz struct of Gyroscope data
 */
extern struct bno055_3axis bno055ReadGyro(void);

/**
 * @brief Magnetometer data - CAN NOT BE USED IN IMU MODE SEE bno055Init
 * @ret Returns xyz struct of Magnetometer data
 */
extern struct bno055_3axis bno055ReadMag(void);

/**
 * @brief heading/YAW data - CAN NOT BE USED IN IMU MODE SEE bno055Init
 * @ret Returns xyz struct of heading/YAW data
 */
extern struct bno055_3axis bno055ReadHead(void);

/**
 * @brief Quaternion data - CAN NOT BE USED IN IMU MODE SEE bno055Init
 * @ret Returns wxyz struct of Quaternion data
 */
extern struct bno055_quat bno055ReadQuat(void);

/**
 * @brief Linear Acceleration data
 * @ret Returns xyz struct of Linear Acceleration data
 */
extern struct bno055_3axis bno055ReadLinAccel(void);

/**
 * @brief Gravity Vector data
 * @ret Returns xyz struct of Gravity Vector data
 */
extern struct bno055_3axis bno055ReadGrav(void);

//Returns temperature
/**
 * @brief Outside temperature
 * @ret Returns temoerature as a uint8
 */
extern uint8_t bno055ReadTemp(void);


#endif /* BNO055_H_ */
