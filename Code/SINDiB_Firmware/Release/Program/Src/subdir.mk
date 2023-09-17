################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Program/Src/cppmain.cpp \
../Program/Src/fastModes.cpp \
../Program/Src/floodfill.cpp \
../Program/Src/searchModes.cpp \
../Program/Src/sysModes.cpp 

OBJS += \
./Program/Src/cppmain.o \
./Program/Src/fastModes.o \
./Program/Src/floodfill.o \
./Program/Src/searchModes.o \
./Program/Src/sysModes.o 

CPP_DEPS += \
./Program/Src/cppmain.d \
./Program/Src/fastModes.d \
./Program/Src/floodfill.d \
./Program/Src/searchModes.d \
./Program/Src/sysModes.d 


# Each subdirectory must supply rules for building sources it contributes
Program/Src/%.o Program/Src/%.su Program/Src/%.cyclo: ../Program/Src/%.cpp Program/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"F:/PROJECTS/SINDiB-MICROMOUSE/code/SINDiB_Firmware/Drivers" -I"F:/PROJECTS/SINDiB-MICROMOUSE/code/SINDiB_Firmware/Program/Inc" -I"F:/PROJECTS/SINDiB-MICROMOUSE/code/SINDiB_Firmware/Libs/Inc" -I"F:/PROJECTS/SINDiB-MICROMOUSE/code/SINDiB_Firmware/Drivers/SSD1306/Inc" -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Program-2f-Src

clean-Program-2f-Src:
	-$(RM) ./Program/Src/cppmain.cyclo ./Program/Src/cppmain.d ./Program/Src/cppmain.o ./Program/Src/cppmain.su ./Program/Src/fastModes.cyclo ./Program/Src/fastModes.d ./Program/Src/fastModes.o ./Program/Src/fastModes.su ./Program/Src/floodfill.cyclo ./Program/Src/floodfill.d ./Program/Src/floodfill.o ./Program/Src/floodfill.su ./Program/Src/searchModes.cyclo ./Program/Src/searchModes.d ./Program/Src/searchModes.o ./Program/Src/searchModes.su ./Program/Src/sysModes.cyclo ./Program/Src/sysModes.d ./Program/Src/sysModes.o ./Program/Src/sysModes.su

.PHONY: clean-Program-2f-Src

