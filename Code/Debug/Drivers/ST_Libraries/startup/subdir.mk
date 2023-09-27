################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/ST_Libraries/startup/startup_stm32f4xx.s 

C_SRCS += \
../Drivers/ST_Libraries/startup/system_stm32f4xx.c 

S_DEPS += \
./Drivers/ST_Libraries/startup/startup_stm32f4xx.d 

C_DEPS += \
./Drivers/ST_Libraries/startup/system_stm32f4xx.d 

OBJS += \
./Drivers/ST_Libraries/startup/startup_stm32f4xx.o \
./Drivers/ST_Libraries/startup/system_stm32f4xx.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ST_Libraries/startup/%.o: ../Drivers/ST_Libraries/startup/%.s Drivers/ST_Libraries/startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"D:/OneDrive - University of Moratuwa/Volume D/Competitions/micromouse/Workspace/MicromouseFirmware/Drivers" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
Drivers/ST_Libraries/startup/%.o Drivers/ST_Libraries/startup/%.su Drivers/ST_Libraries/startup/%.cyclo: ../Drivers/ST_Libraries/startup/%.c Drivers/ST_Libraries/startup/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/OneDrive - University of Moratuwa/Volume D/Competitions/micromouse/Workspace/MicromouseFirmware/Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-ST_Libraries-2f-startup

clean-Drivers-2f-ST_Libraries-2f-startup:
	-$(RM) ./Drivers/ST_Libraries/startup/startup_stm32f4xx.d ./Drivers/ST_Libraries/startup/startup_stm32f4xx.o ./Drivers/ST_Libraries/startup/system_stm32f4xx.cyclo ./Drivers/ST_Libraries/startup/system_stm32f4xx.d ./Drivers/ST_Libraries/startup/system_stm32f4xx.o ./Drivers/ST_Libraries/startup/system_stm32f4xx.su

.PHONY: clean-Drivers-2f-ST_Libraries-2f-startup

