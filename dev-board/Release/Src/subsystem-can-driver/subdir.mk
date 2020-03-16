################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../subsystem-can-driver/bms-data-module.cpp \
../subsystem-can-driver/mppt-data-module.cpp \
../subsystem-can-driver/subsystem-data-module.cpp 

OBJS += \
./Src/subsystem-can-driver/bms-data-module.o \
./Src/subsystem-can-driver/mppt-data-module.o \
./Src/subsystem-can-driver/subsystem-data-module.o 

CPP_DEPS += \
./Src/subsystem-can-driver/bms-data-module.d \
./Src/subsystem-can-driver/mppt-data-module.d \
./Src/subsystem-can-driver/subsystem-data-module.d 


# Each subdirectory must supply rules for building sources it contributes
Src/subsystem-can-driver/bms-data-module.o: C:/Users/Danny/STM32CubeIDE/workspace_1.0.2/TFT_Test/dev-board/subsystem-can-driver/bms-data-module.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -O3 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/subsystem-can-driver/bms-data-module.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/subsystem-can-driver/mppt-data-module.o: C:/Users/Danny/STM32CubeIDE/workspace_1.0.2/TFT_Test/dev-board/subsystem-can-driver/mppt-data-module.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -O3 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/subsystem-can-driver/mppt-data-module.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/subsystem-can-driver/subsystem-data-module.o: C:/Users/Danny/STM32CubeIDE/workspace_1.0.2/TFT_Test/dev-board/subsystem-can-driver/subsystem-data-module.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -O3 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/subsystem-can-driver/subsystem-data-module.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

