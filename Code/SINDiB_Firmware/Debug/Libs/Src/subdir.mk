################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libs/Src/L3GD20.c \
../Libs/Src/adc.c \
../Libs/Src/delay.c \
../Libs/Src/display.c \
../Libs/Src/encoder.c \
../Libs/Src/motor.c \
../Libs/Src/read_sensors.c 

C_DEPS += \
./Libs/Src/L3GD20.d \
./Libs/Src/adc.d \
./Libs/Src/delay.d \
./Libs/Src/display.d \
./Libs/Src/encoder.d \
./Libs/Src/motor.d \
./Libs/Src/read_sensors.d 

OBJS += \
./Libs/Src/L3GD20.o \
./Libs/Src/adc.o \
./Libs/Src/delay.o \
./Libs/Src/display.o \
./Libs/Src/encoder.o \
./Libs/Src/motor.o \
./Libs/Src/read_sensors.o 


# Each subdirectory must supply rules for building sources it contributes
Libs/Src/%.o Libs/Src/%.su Libs/Src/%.cyclo: ../Libs/Src/%.c Libs/Src/subdir.mk
<<<<<<< HEAD
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"F:/PROJECTS/SINDiB-MICROMOUSE/code/SINDiB_Firmware/Drivers" -I"F:/PROJECTS/SINDiB-MICROMOUSE/code/SINDiB_Firmware/Libs/Inc" -I"F:/PROJECTS/SINDiB-MICROMOUSE/code/SINDiB_Firmware/Program/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
=======
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"E:/projects/SINDiB-MicroMouse/Code/SINDiB_Firmware/Drivers" -I"E:/projects/SINDiB-MicroMouse/Code/SINDiB_Firmware/Libs/Inc" -I"E:/projects/SINDiB-MicroMouse/Code/SINDiB_Firmware/Program/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
>>>>>>> origin/master

clean: clean-Libs-2f-Src

clean-Libs-2f-Src:
	-$(RM) ./Libs/Src/L3GD20.cyclo ./Libs/Src/L3GD20.d ./Libs/Src/L3GD20.o ./Libs/Src/L3GD20.su ./Libs/Src/adc.cyclo ./Libs/Src/adc.d ./Libs/Src/adc.o ./Libs/Src/adc.su ./Libs/Src/delay.cyclo ./Libs/Src/delay.d ./Libs/Src/delay.o ./Libs/Src/delay.su ./Libs/Src/display.cyclo ./Libs/Src/display.d ./Libs/Src/display.o ./Libs/Src/display.su ./Libs/Src/encoder.cyclo ./Libs/Src/encoder.d ./Libs/Src/encoder.o ./Libs/Src/encoder.su ./Libs/Src/motor.cyclo ./Libs/Src/motor.d ./Libs/Src/motor.o ./Libs/Src/motor.su ./Libs/Src/read_sensors.cyclo ./Libs/Src/read_sensors.d ./Libs/Src/read_sensors.o ./Libs/Src/read_sensors.su

.PHONY: clean-Libs-2f-Src

