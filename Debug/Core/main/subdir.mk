################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/main/cfe_main.c 

OBJS += \
./Core/main/cfe_main.o 

C_DEPS += \
./Core/main/cfe_main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/main/%.o Core/main/%.su Core/main/%.cyclo: ../Core/main/%.c Core/main/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-main

clean-Core-2f-main:
	-$(RM) ./Core/main/cfe_main.cyclo ./Core/main/cfe_main.d ./Core/main/cfe_main.o ./Core/main/cfe_main.su

.PHONY: clean-Core-2f-main

