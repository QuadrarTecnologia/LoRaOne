################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/quadrar/ds18b20.c \
../Core/quadrar/dwt_stm32_delay.c \
../Core/quadrar/onewire.c \
../Core/quadrar/quadrar_gps.c \
../Core/quadrar/quadrar_loraone.c 

OBJS += \
./Core/quadrar/ds18b20.o \
./Core/quadrar/dwt_stm32_delay.o \
./Core/quadrar/onewire.o \
./Core/quadrar/quadrar_gps.o \
./Core/quadrar/quadrar_loraone.o 

C_DEPS += \
./Core/quadrar/ds18b20.d \
./Core/quadrar/dwt_stm32_delay.d \
./Core/quadrar/onewire.d \
./Core/quadrar/quadrar_gps.d \
./Core/quadrar/quadrar_loraone.d 


# Each subdirectory must supply rules for building sources it contributes
Core/quadrar/ds18b20.o: ../Core/quadrar/ds18b20.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L152xE -DDEBUG -c -I"D:/Workspace/STM32CubeIDE/workspace_1.2.0/quadrar-loraone-devboard-demo/Core/quadrar" -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/quadrar/ds18b20.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/quadrar/dwt_stm32_delay.o: ../Core/quadrar/dwt_stm32_delay.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L152xE -DDEBUG -c -I"D:/Workspace/STM32CubeIDE/workspace_1.2.0/quadrar-loraone-devboard-demo/Core/quadrar" -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/quadrar/dwt_stm32_delay.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/quadrar/onewire.o: ../Core/quadrar/onewire.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L152xE -DDEBUG -c -I"D:/Workspace/STM32CubeIDE/workspace_1.2.0/quadrar-loraone-devboard-demo/Core/quadrar" -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/quadrar/onewire.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/quadrar/quadrar_gps.o: ../Core/quadrar/quadrar_gps.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L152xE -DDEBUG -c -I"D:/Workspace/STM32CubeIDE/workspace_1.2.0/quadrar-loraone-devboard-demo/Core/quadrar" -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/quadrar/quadrar_gps.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/quadrar/quadrar_loraone.o: ../Core/quadrar/quadrar_loraone.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L152xE -DDEBUG -c -I"D:/Workspace/STM32CubeIDE/workspace_1.2.0/quadrar-loraone-devboard-demo/Core/quadrar" -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/quadrar/quadrar_loraone.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

