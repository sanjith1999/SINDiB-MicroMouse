################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SSD1306/Src/ssd1306.c \
../Drivers/SSD1306/Src/ssd1306_fonts.c \
../Drivers/SSD1306/Src/ssd1306_tests.c 

C_DEPS += \
./Drivers/SSD1306/Src/ssd1306.d \
./Drivers/SSD1306/Src/ssd1306_fonts.d \
./Drivers/SSD1306/Src/ssd1306_tests.d 

OBJS += \
./Drivers/SSD1306/Src/ssd1306.o \
./Drivers/SSD1306/Src/ssd1306_fonts.o \
./Drivers/SSD1306/Src/ssd1306_tests.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SSD1306/Src/%.o Drivers/SSD1306/Src/%.su Drivers/SSD1306/Src/%.cyclo: ../Drivers/SSD1306/Src/%.c Drivers/SSD1306/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"F:/PROJECTS/SINDiB-MICROMOUSE/code/SINDiB_Firmware/Drivers" -I"F:/PROJECTS/SINDiB-MICROMOUSE/code/SINDiB_Firmware/Program/Inc" -I"F:/PROJECTS/SINDiB-MICROMOUSE/code/SINDiB_Firmware/Libs/Inc" -I"F:/PROJECTS/SINDiB-MICROMOUSE/code/SINDiB_Firmware/Drivers/SSD1306/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-SSD1306-2f-Src

clean-Drivers-2f-SSD1306-2f-Src:
	-$(RM) ./Drivers/SSD1306/Src/ssd1306.cyclo ./Drivers/SSD1306/Src/ssd1306.d ./Drivers/SSD1306/Src/ssd1306.o ./Drivers/SSD1306/Src/ssd1306.su ./Drivers/SSD1306/Src/ssd1306_fonts.cyclo ./Drivers/SSD1306/Src/ssd1306_fonts.d ./Drivers/SSD1306/Src/ssd1306_fonts.o ./Drivers/SSD1306/Src/ssd1306_fonts.su ./Drivers/SSD1306/Src/ssd1306_tests.cyclo ./Drivers/SSD1306/Src/ssd1306_tests.d ./Drivers/SSD1306/Src/ssd1306_tests.o ./Drivers/SSD1306/Src/ssd1306_tests.su

.PHONY: clean-Drivers-2f-SSD1306-2f-Src

