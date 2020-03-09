################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../switch-debouncer/sw-debounce.cpp 

OBJS += \
./Src/switch-debouncer/sw-debounce.o 

CPP_DEPS += \
./Src/switch-debouncer/sw-debounce.d 


# Each subdirectory must supply rules for building sources it contributes
Src/switch-debouncer/sw-debounce.o: C:/Users/Danny/STM32CubeIDE/workspace_1.0.2/TFT_Test/switch-debouncer/sw-debounce.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F072xB -DDEBUG -c -I../Inc -I../tft-display-code -I../rotary-encoder -I../switch-debouncer -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/switch-debouncer/sw-debounce.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

