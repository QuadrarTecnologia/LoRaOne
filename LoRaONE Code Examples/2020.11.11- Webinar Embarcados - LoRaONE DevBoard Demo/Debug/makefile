################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32L1xx_HAL_Driver/Src/subdir.mk
-include Core/quadrar/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
quadrar-loraone-devboard-demo.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
quadrar-loraone-devboard-demo.list \

OBJCOPY_BIN += \
quadrar-loraone-devboard-demo.bin \


# All Target
all: quadrar-loraone-devboard-demo.elf secondary-outputs

# Tool invocations
quadrar-loraone-devboard-demo.elf: $(OBJS) $(USER_OBJS) D:\Workspace\STM32CubeIDE\workspace_1.2.0\quadrar-loraone-devboard-demo\STM32L152RETX_FLASH.ld
	arm-none-eabi-gcc -o "quadrar-loraone-devboard-demo.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Workspace\STM32CubeIDE\workspace_1.2.0\quadrar-loraone-devboard-demo\STM32L152RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="quadrar-loraone-devboard-demo.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

quadrar-loraone-devboard-demo.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "quadrar-loraone-devboard-demo.list"
	@echo 'Finished building: $@'
	@echo ' '

quadrar-loraone-devboard-demo.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "quadrar-loraone-devboard-demo.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
