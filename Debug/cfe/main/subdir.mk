################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cfe/main/cfe_main.c 

OBJS += \
./cfe/main/cfe_main.o 

C_DEPS += \
./cfe/main/cfe_main.d 


# Each subdirectory must supply rules for building sources it contributes
cfe/main/%.o cfe/main/%.su cfe/main/%.cyclo: ../cfe/main/%.c cfe/main/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I"/Users/eddiezou/STM32CubeIDE/workspace_1.15.1/test_cfe/cfe/include" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fno-builtin-printf -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-cfe-2f-main

clean-cfe-2f-main:
	-$(RM) ./cfe/main/cfe_main.cyclo ./cfe/main/cfe_main.d ./cfe/main/cfe_main.o ./cfe/main/cfe_main.su

.PHONY: clean-cfe-2f-main

