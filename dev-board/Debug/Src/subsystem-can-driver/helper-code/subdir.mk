################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/subsystem-can-driver/helper-code/rx-module-binary-tree.cpp 

OBJS += \
./Src/subsystem-can-driver/helper-code/rx-module-binary-tree.o 

CPP_DEPS += \
./Src/subsystem-can-driver/helper-code/rx-module-binary-tree.d 


# Each subdirectory must supply rules for building sources it contributes
Src/subsystem-can-driver/helper-code/rx-module-binary-tree.o: ../Src/subsystem-can-driver/helper-code/rx-module-binary-tree.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F072xB -DDEBUG -c -I../Inc -I../Src/imu-driver -I../Src/gps-driver -I../Src/rf-messaging-module -I../Src/subsystem-can-driver -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/subsystem-can-driver/helper-code/rx-module-binary-tree.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

