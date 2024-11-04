################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/LEANDRO/Downloads/CH32V307EVT/EVT/EXAM/SRC/Core/core_riscv.c 

OBJS += \
./Core/core_riscv.o 

C_DEPS += \
./Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
Core/core_riscv.o: C:/Users/LEANDRO/Downloads/CH32V307EVT/EVT/EXAM/SRC/Core/core_riscv.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\LEANDRO\Downloads\CH32V307EVT\EVT\EXAM\USB\USBHS\DEVICE\SimulateCDC\User\UART" -I"C:\Users\LEANDRO\Downloads\CH32V307EVT\EVT\EXAM\USB\USBHS\DEVICE\SimulateCDC\User\USB_Device" -I"C:\Users\LEANDRO\Downloads\CH32V307EVT\EVT\EXAM\SRC\Debug" -I"C:\Users\LEANDRO\Downloads\CH32V307EVT\EVT\EXAM\SRC\Core" -I"C:\Users\LEANDRO\Downloads\CH32V307EVT\EVT\EXAM\USB\USBHS\DEVICE\SimulateCDC\User" -I"C:\Users\LEANDRO\Downloads\CH32V307EVT\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


