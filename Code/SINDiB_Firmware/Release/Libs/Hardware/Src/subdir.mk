################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libs/Hardware/Src/L3GD20.c \
../Libs/Hardware/Src/encoder.c \
../Libs/Hardware/Src/led.c \
../Libs/Hardware/Src/motor.c 

C_DEPS += \
./Libs/Hardware/Src/L3GD20.d \
./Libs/Hardware/Src/encoder.d \
./Libs/Hardware/Src/led.d \
./Libs/Hardware/Src/motor.d 

OBJS += \
./Libs/Hardware/Src/L3GD20.o \
./Libs/Hardware/Src/encoder.o \
./Libs/Hardware/Src/led.o \
./Libs/Hardware/Src/motor.o 


# Each subdirectory must supply rules for building sources it contributes
Libs/Hardware/Src/%.o Libs/Hardware/Src/%.su Libs/Hardware/Src/%.cyclo: ../Libs/Hardware/Src/%.c Libs/Hardware/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"F:/PROJECTS/SINDiB-MICROMOUSE/code/SINDiB_Firmware/Drivers" -I"F:/PROJECTS/SINDiB-MICROMOUSE/code/SINDiB_Firmware/Libs/Hardware/Inc" -I"F:/PROJECTS/SINDiB-MICROMOUSE/code/SINDiB_Firmware/Libs/Algo/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libs-2f-Hardware-2f-Src

clean-Libs-2f-Hardware-2f-Src:
	-$(RM) ./Libs/Hardware/Src/L3GD20.cyclo ./Libs/Hardware/Src/L3GD20.d ./Libs/Hardware/Src/L3GD20.o ./Libs/Hardware/Src/L3GD20.su ./Libs/Hardware/Src/encoder.cyclo ./Libs/Hardware/Src/encoder.d ./Libs/Hardware/Src/encoder.o ./Libs/Hardware/Src/encoder.su ./Libs/Hardware/Src/led.cyclo ./Libs/Hardware/Src/led.d ./Libs/Hardware/Src/led.o ./Libs/Hardware/Src/led.su ./Libs/Hardware/Src/motor.cyclo ./Libs/Hardware/Src/motor.d ./Libs/Hardware/Src/motor.o ./Libs/Hardware/Src/motor.su

.PHONY: clean-Libs-2f-Hardware-2f-Src

