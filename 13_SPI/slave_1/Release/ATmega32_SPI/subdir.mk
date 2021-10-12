################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ATmega32_SPI/ATmega32_SPI.cpp 

OBJS += \
./ATmega32_SPI/ATmega32_SPI.o 

CPP_DEPS += \
./ATmega32_SPI/ATmega32_SPI.d 


# Each subdirectory must supply rules for building sources it contributes
ATmega32_SPI/%.o: ../ATmega32_SPI/%.cpp ATmega32_SPI/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


