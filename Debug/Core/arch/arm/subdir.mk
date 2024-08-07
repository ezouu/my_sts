################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/arch/arm/init_arm.s 

C_SRCS += \
../Core/arch/arm/lib_printf.c 

OBJS += \
./Core/arch/arm/init_arm.o \
./Core/arch/arm/lib_printf.o 

S_DEPS += \
./Core/arch/arm/init_arm.d 

C_DEPS += \
./Core/arch/arm/lib_printf.d 


# Each subdirectory must supply rules for building sources it contributes
Core/arch/arm/%.o: ../Core/arch/arm/%.s Core/arch/arm/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
Core/arch/arm/%.o Core/arch/arm/%.su Core/arch/arm/%.cyclo: ../Core/arch/arm/%.c Core/arch/arm/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-arch-2f-arm

clean-Core-2f-arch-2f-arm:
	-$(RM) ./Core/arch/arm/init_arm.d ./Core/arch/arm/init_arm.o ./Core/arch/arm/lib_printf.cyclo ./Core/arch/arm/lib_printf.d ./Core/arch/arm/lib_printf.o ./Core/arch/arm/lib_printf.su

.PHONY: clean-Core-2f-arch-2f-arm

