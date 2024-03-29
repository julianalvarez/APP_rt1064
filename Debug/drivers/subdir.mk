################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_adc.c \
../drivers/fsl_adc_etc.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_dmamux.c \
../drivers/fsl_edma.c \
../drivers/fsl_flexcan.c \
../drivers/fsl_flexcan_edma.c \
../drivers/fsl_gpio.c \
../drivers/fsl_gpt.c \
../drivers/fsl_lpuart.c 

C_DEPS += \
./drivers/fsl_adc.d \
./drivers/fsl_adc_etc.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_dmamux.d \
./drivers/fsl_edma.d \
./drivers/fsl_flexcan.d \
./drivers/fsl_flexcan_edma.d \
./drivers/fsl_gpio.d \
./drivers/fsl_gpt.d \
./drivers/fsl_lpuart.d 

OBJS += \
./drivers/fsl_adc.o \
./drivers/fsl_adc_etc.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_dmamux.o \
./drivers/fsl_edma.o \
./drivers/fsl_flexcan.o \
./drivers/fsl_flexcan_edma.o \
./drivers/fsl_gpio.o \
./drivers/fsl_gpt.o \
./drivers/fsl_lpuart.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MIMXRT1064DVL6A -DPRINTF_FLOAT_ENABLE=1 -DCPU_MIMXRT1064DVL6A_cm7 -DSDK_OS_BAREMETAL -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSYSTEM_STEER -D__REDLIB__ -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\APP_rt1064\drivers" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\APP_rt1064\xip" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\APP_rt1064\device" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\APP_rt1064\CMSIS" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\APP_rt1064\component\serial_manager" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\APP_rt1064\component\uart" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\APP_rt1064\utilities" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\APP_rt1064\component\lists" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\APP_rt1064\source" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\CSP_rt1064\CMSIS" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\CSP_rt1064\source" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\CSP_rt1064\utilities" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\CSP_rt1064\drivers" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\CSP_rt1064\board" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\j1939_STEER_LIB\Include" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\j1939_STEER_LIB\CMSIS" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\j1939_STEER_LIB\source" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\j1939_STEER_LIB\board" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\j1939_STEER_LIB" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\BSP_rt1064\CMSIS" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\BSP_rt1064\source" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\BSP_rt1064\board" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_adc.d ./drivers/fsl_adc.o ./drivers/fsl_adc_etc.d ./drivers/fsl_adc_etc.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_dmamux.d ./drivers/fsl_dmamux.o ./drivers/fsl_edma.d ./drivers/fsl_edma.o ./drivers/fsl_flexcan.d ./drivers/fsl_flexcan.o ./drivers/fsl_flexcan_edma.d ./drivers/fsl_flexcan_edma.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_gpt.d ./drivers/fsl_gpt.o ./drivers/fsl_lpuart.d ./drivers/fsl_lpuart.o

.PHONY: clean-drivers

