################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/gps-driver/gps-driver.cpp 

OBJS += \
./Src/gps-driver/gps-driver.o 

CPP_DEPS += \
./Src/gps-driver/gps-driver.d 


# Each subdirectory must supply rules for building sources it contributes
Src/gps-driver/gps-driver.o: ../Src/gps-driver/gps-driver.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F072xB -DDEBUG -c -I../Inc -I../Src/imu-driver -I../Src/gps-driver -I../Src/rf-messaging-module -I../Src/subsystem-can-driver -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/gps-driver/gps-driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

