################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sts/ui/ui_commands.c 

OBJS += \
./sts/ui/ui_commands.o 

C_DEPS += \
./sts/ui/ui_commands.d 


# Each subdirectory must supply rules for building sources it contributes
sts/ui/%.o sts/ui/%.su sts/ui/%.cyclo: ../sts/ui/%.c sts/ui/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"/Users/eddiezou/STM32CubeIDE/workspace_1.15.1/test_cfe/sts/include" -O0 -ffunction-sections -fdata-sections -Wall -fno-builtin-printf -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-sts-2f-ui

clean-sts-2f-ui:
	-$(RM) ./sts/ui/ui_commands.cyclo ./sts/ui/ui_commands.d ./sts/ui/ui_commands.o ./sts/ui/ui_commands.su

.PHONY: clean-sts-2f-ui

