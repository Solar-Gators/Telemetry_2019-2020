################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subsystem-can-driver/helper-code/subdir.mk
-include Src/subsystem-can-driver/subdir.mk
-include Src/rf-messaging-module/subdir.mk
-include Src/rf-driver/subdir.mk
-include Src/imu-driver/subdir.mk
-include Src/gps-driver/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F0xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
telemetry-dev-board.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
telemetry-dev-board.list \


# All Target
all: telemetry-dev-board.elf secondary-outputs

# Tool invocations
telemetry-dev-board.elf: $(OBJS) $(USER_OBJS) C:\Users\Danny\STM32CubeIDE\workspace_1.0.2\TFT_Test\dev-board\STM32F072RBTX_FLASH.ld
	arm-none-eabi-g++ -o "telemetry-dev-board.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"C:\Users\Danny\STM32CubeIDE\workspace_1.0.2\TFT_Test\dev-board\STM32F072RBTX_FLASH.ld" -Wl,-Map="telemetry-dev-board.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

telemetry-dev-board.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "telemetry-dev-board.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
