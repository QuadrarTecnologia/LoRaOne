################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32l152retx.s 

OBJS += \
./Core/Startup/startup_stm32l152retx.o 

S_DEPS += \
./Core/Startup/startup_stm32l152retx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/startup_stm32l152retx.o: ../Core/Startup/startup_stm32l152retx.s
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -c -I"D:/Workspace/STM32CubeIDE/workspace_1.2.0/quadrar-loraone-devboard-demo/Core/quadrar" -x assembler-with-cpp -MMD -MP -MF"Core/Startup/startup_stm32l152retx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

