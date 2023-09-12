################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Libs/Algo/Src/fastModes.cpp \
../Libs/Algo/Src/floodfill.cpp \
../Libs/Algo/Src/searchModes.cpp \
../Libs/Algo/Src/sysModes.cpp 

OBJS += \
./Libs/Algo/Src/fastModes.o \
./Libs/Algo/Src/floodfill.o \
./Libs/Algo/Src/searchModes.o \
./Libs/Algo/Src/sysModes.o 

CPP_DEPS += \
./Libs/Algo/Src/fastModes.d \
./Libs/Algo/Src/floodfill.d \
./Libs/Algo/Src/searchModes.d \
./Libs/Algo/Src/sysModes.d 


# Each subdirectory must supply rules for building sources it contributes
Libs/Algo/Src/%.o Libs/Algo/Src/%.su Libs/Algo/Src/%.cyclo: ../Libs/Algo/Src/%.cpp Libs/Algo/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"F:/PROJECTS/SINDiB-MICROMOUSE/code/SINDiB_Firmware/Drivers" -I"F:/PROJECTS/SINDiB-MICROMOUSE/code/SINDiB_Firmware/Libs/Hardware/Inc" -I"F:/PROJECTS/SINDiB-MICROMOUSE/code/SINDiB_Firmware/Libs/Algo/Inc" -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libs-2f-Algo-2f-Src

clean-Libs-2f-Algo-2f-Src:
	-$(RM) ./Libs/Algo/Src/fastModes.cyclo ./Libs/Algo/Src/fastModes.d ./Libs/Algo/Src/fastModes.o ./Libs/Algo/Src/fastModes.su ./Libs/Algo/Src/floodfill.cyclo ./Libs/Algo/Src/floodfill.d ./Libs/Algo/Src/floodfill.o ./Libs/Algo/Src/floodfill.su ./Libs/Algo/Src/searchModes.cyclo ./Libs/Algo/Src/searchModes.d ./Libs/Algo/Src/searchModes.o ./Libs/Algo/Src/searchModes.su ./Libs/Algo/Src/sysModes.cyclo ./Libs/Algo/Src/sysModes.d ./Libs/Algo/Src/sysModes.o ./Libs/Algo/Src/sysModes.su

.PHONY: clean-Libs-2f-Algo-2f-Src

