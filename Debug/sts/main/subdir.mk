################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sts/main/sts_main.c 

OBJS += \
./sts/main/sts_main.o 

C_DEPS += \
./sts/main/sts_main.d 


# Each subdirectory must supply rules for building sources it contributes
sts/main/%.o sts/main/%.su sts/main/%.cyclo: ../sts/main/%.c sts/main/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"/Users/eddiezou/STM32CubeIDE/workspace_1.15.1/test_cfe/sts/include" -O0 -ffunction-sections -fdata-sections -Wall -fno-builtin-printf -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-sts-2f-main

clean-sts-2f-main:
	-$(RM) ./sts/main/sts_main.cyclo ./sts/main/sts_main.d ./sts/main/sts_main.o ./sts/main/sts_main.su

.PHONY: clean-sts-2f-main

