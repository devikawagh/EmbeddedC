################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
mcan_message_rx_LP_MSPM0G3507_nortos_ticlang/Debug/%.o: ../mcan_message_rx_LP_MSPM0G3507_nortos_ticlang/Debug/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1271/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/User/Practise/mcan_message_rx_LP_MSPM0G3507_nortos_ticlang" -I"C:/Users/User/Practise/mcan_message_rx_LP_MSPM0G3507_nortos_ticlang/Debug" -I"C:/ti/mspm0_sdk_2_02_00_05/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_02_00_05/source" -gdwarf-3 -MMD -MP -MF"mcan_message_rx_LP_MSPM0G3507_nortos_ticlang/Debug/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


