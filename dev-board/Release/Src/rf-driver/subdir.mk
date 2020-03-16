################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/rf-driver/data-link-layer.cpp \
../Src/rf-driver/rf-message-helper.cpp \
../Src/rf-driver/tranport-layer.cpp 

OBJS += \
./Src/rf-driver/data-link-layer.o \
./Src/rf-driver/rf-message-helper.o \
./Src/rf-driver/tranport-layer.o 

CPP_DEPS += \
./Src/rf-driver/data-link-layer.d \
./Src/rf-driver/rf-message-helper.d \
./Src/rf-driver/tranport-layer.d 


# Each subdirectory must supply rules for building sources it contributes
Src/rf-driver/data-link-layer.o: ../Src/rf-driver/data-link-layer.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -O3 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/rf-driver/data-link-layer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/rf-driver/rf-message-helper.o: ../Src/rf-driver/rf-message-helper.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -O3 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/rf-driver/rf-message-helper.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/rf-driver/tranport-layer.o: ../Src/rf-driver/tranport-layer.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -O3 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/rf-driver/tranport-layer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

