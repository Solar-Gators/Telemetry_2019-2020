################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/gps-driver/gps-driver.cpp 

OBJS += \
./Core/Src/gps-driver/gps-driver.o 

CPP_DEPS += \
./Core/Src/gps-driver/gps-driver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/gps-driver/gps-driver.o: ../Core/Src/gps-driver/gps-driver.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F072xB -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Core/Src/subsystem-can-driver -I../Core/Src/imu-driver -I../Core/Src/rf-driver -I../Core/Src/gps-driver -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/Src/gps-driver/gps-driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

