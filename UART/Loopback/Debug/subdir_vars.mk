################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
SYSCFG_SRCS += \
../UART_15hello_loopback.syscfg 

C_SRCS += \
../UART_15hello_loopback.c \
./ti_msp_dl_config.c \
C:/ti/mspm0_sdk_2_02_00_05/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c 

GEN_CMDS += \
./device_linker.cmd 

GEN_FILES += \
./device_linker.cmd \
./device.opt \
./ti_msp_dl_config.c 

C_DEPS += \
./UART_15hello_loopback.d \
./ti_msp_dl_config.d \
./startup_mspm0g350x_ticlang.d 

GEN_OPTS += \
./device.opt 

OBJS += \
./UART_15hello_loopback.o \
./ti_msp_dl_config.o \
./startup_mspm0g350x_ticlang.o 

GEN_MISC_FILES += \
./device.cmd.genlibs \
./ti_msp_dl_config.h 

OBJS__QUOTED += \
"UART_15hello_loopback.o" \
"ti_msp_dl_config.o" \
"startup_mspm0g350x_ticlang.o" 

GEN_MISC_FILES__QUOTED += \
"device.cmd.genlibs" \
"ti_msp_dl_config.h" 

C_DEPS__QUOTED += \
"UART_15hello_loopback.d" \
"ti_msp_dl_config.d" \
"startup_mspm0g350x_ticlang.d" 

GEN_FILES__QUOTED += \
"device_linker.cmd" \
"device.opt" \
"ti_msp_dl_config.c" 

C_SRCS__QUOTED += \
"../UART_15hello_loopback.c" \
"./ti_msp_dl_config.c" \
"C:/ti/mspm0_sdk_2_02_00_05/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c" 

SYSCFG_SRCS__QUOTED += \
"../UART_15hello_loopback.syscfg" 


