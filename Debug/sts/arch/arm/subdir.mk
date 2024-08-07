################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../sts/arch/arm/init_arm.s 

C_SRCS += \
../sts/arch/arm/lib_printf.c 

OBJS += \
./sts/arch/arm/init_arm.o \
./sts/arch/arm/lib_printf.o 

S_DEPS += \
./sts/arch/arm/init_arm.d 

C_DEPS += \
./sts/arch/arm/lib_printf.d 


# Each subdirectory must supply rules for building sources it contributes
sts/arch/arm/%.o: ../sts/arch/arm/%.s sts/arch/arm/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
sts/arch/arm/%.o sts/arch/arm/%.su sts/arch/arm/%.cyclo: ../sts/arch/arm/%.c sts/arch/arm/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"/Users/eddiezou/STM32CubeIDE/workspace_1.15.1/test_cfe/sts/include" -O0 -ffunction-sections -fdata-sections -Wall -fno-builtin-printf -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-sts-2f-arch-2f-arm

clean-sts-2f-arch-2f-arm:
	-$(RM) ./sts/arch/arm/init_arm.d ./sts/arch/arm/init_arm.o ./sts/arch/arm/lib_printf.cyclo ./sts/arch/arm/lib_printf.d ./sts/arch/arm/lib_printf.o ./sts/arch/arm/lib_printf.su

.PHONY: clean-sts-2f-arch-2f-arm

