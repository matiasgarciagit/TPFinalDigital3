################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: TPFinalDigital3.axf

# Tool invocations
TPFinalDigital3.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\lucho\Documents\MCUXpressoIDE_11.4.0_6237\workspace_drivers\CMSISv2p00_LPC17xx\Debug" -Xlinker -Map="TPFinalDigital3.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "TPFinalDigital3_Debug.ld" -o "TPFinalDigital3.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) TPFinalDigital3.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "TPFinalDigital3.axf"; # arm-none-eabi-objcopy -v -O binary "TPFinalDigital3.axf" "TPFinalDigital3.bin" ; # checksum -p LPC1769 -d "TPFinalDigital3.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
