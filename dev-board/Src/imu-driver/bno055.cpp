#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "bno055.h"
#include "main.h"

I2C_HandleTypeDef hi2c1;

/**
 * @brief Reads a register
 * @param reg - Should be from register from BNO055_ADDRESSES
 */
static uint8_t bno055ReadReg(uint8_t reg);

/**
 * @brief writes to a register
 * @param reg - Should be from register from BNO055_ADDRESSES
 * @param data - data to write
 */
static void bno055SendReg(uint8_t reg, uint8_t data);

/**
 * @brief Reads two sequential register and returns them combined
 * @param lsbReg - Should be from register from BNO055_ADDRESSES
 */
static int16_t bno055ReadData(uint8_t lsbReg);

/**
 * @brief returns xyz of reg value
 * @param reg - Should be from register from BNO055_ADDRESSES
 */
static struct bno055_3axis bno055Read3Axis(uint8_t reg);

/**
 * @brief INIT for I2C
 */
static void MX_I2C1_Init(void);


void bno055Init()
{
	MX_I2C1_Init();
    //configure sensors
    bno055SendReg(OPR_MODE, IMU);
}

struct bno055_3axis bno055ReadAccel()
{
    return bno055Read3Axis(ACC_DATA_X_LSB);
}
struct bno055_3axis bno055ReadGyro()
{
    return bno055Read3Axis(GYR_DATA_X_LSB);
}
struct bno055_3axis bno055ReadMag()
{
    return bno055Read3Axis(MAG_DATA_X_LSB);
}
struct bno055_3axis bno055ReadHead()
{
    return bno055Read3Axis(EUL_DATA_X_LSB);
}
struct bno055_quat bno055ReadQuat()
{
    struct bno055_quat quat;
    quat.w = bno055ReadData(QUA_DATA_W_LSB);
    quat.x = bno055ReadData(QUA_DATA_X_LSB);
    quat.y = bno055ReadData(QUA_DATA_Y_LSB);
    quat.z = bno055ReadData(QUA_DATA_Z_LSB);
    return quat;
}
struct bno055_3axis bno055ReadLinAccel()
{
    return bno055Read3Axis(LIA_DATA_X_LSB);
}
struct bno055_3axis bno055ReadGrav()
{
    return bno055Read3Axis(GRV_DATA_X_LSB);
}
uint8_t bno055ReadTemp()
{
    return bno055ReadReg(TEMP);
}

static uint8_t bno055ReadReg(uint8_t reg)
{
    uint8_t buffer[1] = { 0x00 };
    HAL_I2C_Mem_Read(&hi2c1, BNO055_ADDRESS<<1, reg, 1, buffer, 1, 100);
    return buffer[0];
}

static void bno055SendReg(uint8_t reg, uint8_t data)
{
    uint8_t buffer[1] = { data };
    HAL_I2C_Mem_Write(&hi2c1, BNO055_ADDRESS<<1, reg, 1, buffer, 1, 100);
}

static int16_t bno055ReadData(uint8_t lsbReg)
{
    uint8_t msbReg = lsbReg + 1; //Little endian

    uint8_t lsbData = bno055ReadReg(lsbReg);
    uint8_t msbData = bno055ReadReg(msbReg);


    return (msbData << 8) | lsbData;
}

static struct bno055_3axis bno055Read3Axis(uint8_t reg)
{
    struct bno055_3axis data;
    data.x = bno055ReadData(reg);
    data.y = bno055ReadData(reg+2);
    data.z = bno055ReadData(reg+4);
    return data;
}

static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}
