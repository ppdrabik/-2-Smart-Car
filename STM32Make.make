##########################################################################################################################
# File automatically-generated by STM32forVSCode
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#   2024-04-27 - Added env file inclusion. 
#                Added way to overide: build directory, target name and optimisation.
#                Added GCC_PATH by env file to not make the makefile machine dependent.
#                Currently folder structure in build directory is preserved
#                Switching of debug/release build output folder now happens based on debug flag
#   2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# Environment Variables
######################################
# Imports the environment file in which the compiler and other tooling is set
# for the build machine.
# This can also be used to overwrite some makefile variables
file_exists = $(or $(and $(wildcard $(1)),1),0)
ifeq ($(call file_exists,.stm32env),1)
  include .stm32env
endif

######################################
# Target
######################################
# This is the name of the embedded target which will be build
# The final file name will also have debug or release appended to it.
TARGET ?= car

#######################################
# Build directories
#######################################
# Build path can be overwritten when calling make or setting the environment variable
# in .stm32env

BUILD_DIRECTORY ?= build


######################################
# Optimization
######################################
# Optimization is switched based upon the DEBUG variable. If set to 1
# it will be build in debug mode with the Og optimization flag (optimized for debugging).
# If set to 0 (false) then by default the variable is used in the configuration yaml
# This can also be overwritten using the environment variable or by overwriting it
# by calling make with the OPTIMIZATION variable e.g.:
# make -f STM32Make.make -j 16  OPTIMIZATION=Os

# variable which determines if it is a debug build
DEBUG ?= 1

# debug flags when debug is defined
OPTIMIZATION ?= -Og

RELEASE_DIRECTORY = $(BUILD_DIRECTORY)/debug
ifeq ($(DEBUG),1)
  # Sets debugging optimization -Og and the debug information output
  OPTIMIZATION_FLAGS += -Og -g -gdwarf -ggdb
  $(TARGET) := $(TARGET)-debug
  RELEASE_DIRECTORY := $(BUILD_DIRECTORY)/debug
else
  OPTIMIZATION_FLAGS += $(OPTIMIZATION)
  $(TARGET) := $(TARGET)-release
  RELEASE_DIRECTORY := $(BUILD_DIRECTORY)/release
endif

######################################
# source
######################################
# C sources
C_SOURCES =  \
Core/Src/app_freertos.c \
Core/Src/dma.c \
Core/Src/gpio.c \
Core/Src/i2c.c \
Core/Src/main.c \
Core/Src/spi.c \
Core/Src/stm32g4xx_hal_msp.c \
Core/Src/stm32g4xx_hal_timebase_tim.c \
Core/Src/stm32g4xx_it.c \
Core/Src/syscalls.c \
Core/Src/sysmem.c \
Core/Src/system_stm32g4xx.c \
Core/Src/tim.c \
Core/Src/vl53l0x.c \
Drivers/BSP/STM32G4xx_Nucleo/stm32g4xx_nucleo.c \
Drivers/LoRa/lora.c \
Drivers/Motor/motor.c \
Drivers/RGB_LED/rgb.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_cortex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_exti.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ramfunc.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_gpio.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_i2c.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_i2c_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_uart.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_uart_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_usart.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_usart_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_dma.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_exti.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_gpio.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_pwr.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_spi.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_tim.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_utils.c \
Drivers/VL53L0X/core/src/vl53l0x_api.c \
Drivers/VL53L0X/core/src/vl53l0x_api_calibration.c \
Drivers/VL53L0X/core/src/vl53l0x_api_core.c \
Drivers/VL53L0X/core/src/vl53l0x_api_ranging.c \
Drivers/VL53L0X/core/src/vl53l0x_api_strings.c \
Drivers/VL53L0X/platform/src/vl53l0x_platform.c \
Drivers/VL53L0X/platform/src/vl53l0x_platform_log.c \
Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c \
Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
Middlewares/Third_Party/FreeRTOS/Source/list.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c \
Middlewares/Third_Party/FreeRTOS/Source/queue.c \
Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c \
Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
Middlewares/Third_Party/FreeRTOS/Source/timers.c


CPP_SOURCES = \


# ASM sources
ASM_SOURCES =  \
startup_stm32g491xx.s


#######################################
# Tools
#######################################
ARM_PREFIX = arm-none-eabi-
POSTFIX = "
PREFIX = "
# The gcc compiler bin path can be defined in the make command via ARM_GCC_PATH variable (e.g.: make ARM_GCC_PATH=xxx)
# or it can be added to the PATH environment variable.
# By default the variable be used from the environment file: .stm32env.
# if it is not defined

ifdef ARM_GCC_PATH
    CC = $(PREFIX)$(ARM_GCC_PATH)/$(ARM_PREFIX)gcc$(POSTFIX)
    CXX = $(PREFIX)$(ARM_GCC_PATH)/$(ARM_PREFIX)g++$(POSTFIX)
    AS = $(PREFIX)$(ARM_GCC_PATH)/$(ARM_PREFIX)gcc$(POSTFIX) -x assembler-with-cpp
    CP = $(PREFIX)$(ARM_GCC_PATH)/$(ARM_PREFIX)objcopy$(POSTFIX)
    SZ = $(PREFIX)$(ARM_GCC_PATH)/$(ARM_PREFIX)size$(POSTFIX)
    DP = $(PREFIX)$(ARM_GCC_PATH)/$(ARM_PREFIX)objdump$(POSTFIX)
else
  CC ?= $(ARM_PREFIX)gcc
  CXX ?= $(ARM_PREFIX)g++$
  AS ?= $(ARM_PREFIX)gcc -x assembler-with-cpp
  CP ?= $(ARM_PREFIX)objcopy
  SZ ?= $(ARM_PREFIX)size
  DP ?= $(ARM_PREFIX)objdump
endif

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
LSS = $(DP) -h -S

# Flash and debug tools
# Default is openocd however will be gotten from the env file when existing
OPENOCD ?= openocd


#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DSTM32G491xx \
-DSTM32_THREAD_SAFE_STRATEGY=4 \
-DUSE_FULL_LL_DRIVER \
-DUSE_HAL_DRIVER \
-DUSE_NUCLEO_64


# CXX defines
CXX_DEFS =  \
-DSTM32G491xx \
-DSTM32_THREAD_SAFE_STRATEGY=4 \
-DUSE_FULL_LL_DRIVER \
-DUSE_HAL_DRIVER \
-DUSE_NUCLEO_64


# AS includes
AS_INCLUDES = \

# C includes
C_INCLUDES =  \
-ICore/Inc \
-IDrivers/BSP/STM32G4xx_Nucleo \
-IDrivers/CMSIS/Device/ST/STM32G4xx/Include \
-IDrivers/CMSIS/Include \
-IDrivers/Lora \
-IDrivers/Motor \
-IDrivers/RGB_LED \
-IDrivers/STM32G4xx_HAL_Driver/Inc \
-IDrivers/STM32G4xx_HAL_Driver/Inc/Legacy \
-IDrivers/VL53L0X/core/inc \
-IDrivers/VL53L0X/platform/inc \
-IMiddlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS \
-IMiddlewares/Third_Party/FreeRTOS/Source/include \
-IMiddlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F



# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(C_INCLUDES) $(C_DEFS) $(OPTIMIZATION_FLAGS) 

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPTIMIZATION_FLAGS)

CXXFLAGS = $(MCU) $(CXX_DEFS) $(C_INCLUDES) $(OPTIMIZATION_FLAGS)

# Add additional flags
CFLAGS += -Wall -fdata-sections -ffunction-sections 
ASFLAGS += -Wall -fdata-sections -ffunction-sections 
CXXFLAGS += 

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
CXXFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

# Output a list file for the compiled source file.
# This is a representative of the source code in assembly
ASSEMBLER_LIST_OUTPUT_FLAG = -Wa,-a,-ad,-alms=$(call add_release_directory,$<,lst)
CFLAGS += $(ASSEMBLER_LIST_OUTPUT_FLAG)
CXXFLAGS += $(ASSEMBLER_LIST_OUTPUT_FLAG)

#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32G491RETx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = \


# Additional LD Flags from config file
ADDITIONALLDFLAGS = -Wl,--print-memory-usage -specs=nano.specs 

LDFLAGS = $(MCU) $(ADDITIONALLDFLAGS) -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIRECTORY)/$(TARGET).map,--cref -Wl,--gc-sections

#######################################
# build the application
#######################################
add_release_directory = $(sort $(addprefix $(RELEASE_DIRECTORY)/,$(addsuffix .$(2),$(basename $(subst ../,parent,$(1))))))

REMOVE_DIRECTORY_COMMAND = rm -fR
mkdir_function = mkdir -p $(1)
ifeq ($(OS),Windows_NT)
  convert_to_windows_path = $(strip $(subst /,\,$(patsubst %/,%,$(1))))
  REMOVE_DIRECTORY_COMMAND = cmd /c rd /s /q
  mkdir_function = cmd /e:on /c md $(call convert_to_windows_path,$(1))
endif



OBJECTS = $(call add_release_directory,$(C_SOURCES),o)
OBJECTS += $(call add_release_directory,$(CPP_SOURCES),o)
OBJECTS += $(call add_release_directory,$(ASM_SOURCES),o)
vpath %.c $(sort $(dir $(C_SOURCES)))
vpath %.cc $(sort $(dir $(CXX_SOURCES)))
vpath %.cp $(sort $(dir $(CXX_SOURCES)))
vpath %.cxx $(sort $(dir $(CXX_SOURCES)))
vpath %.cpp $(sort $(dir $(CXX_SOURCES)))
vpath %.c++ $(sort $(dir $(CXX_SOURCES)))
vpath %.C $(sort $(dir $(CXX_SOURCES)))
vpath %.CPP $(sort $(dir $(CXX_SOURCES)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))

# the tree of folders which needs to be present based on the object files
BUILD_TREE = $(sort $(dir $(OBJECTS)))

# C build
$(RELEASE_DIRECTORY)/%.o: %.c STM32Make.make | $(BUILD_TREE)
	$(CC) -c $(CFLAGS) $< -o $@

# C++ build 
$(RELEASE_DIRECTORY)/%.o: %.cc STM32Make.make | $(BUILD_TREE)
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(RELEASE_DIRECTORY)/%.o: %.cp STM32Make.make | $(BUILD_TREE)
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(RELEASE_DIRECTORY)/%.o: %.cxx STM32Make.make | $(BUILD_TREE)
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(RELEASE_DIRECTORY)/%.o: %.cpp STM32Make.make | $(BUILD_TREE)
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(RELEASE_DIRECTORY)/%.o: %.c++ STM32Make.make | $(BUILD_TREE)
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(RELEASE_DIRECTORY)/%.o: %.C STM32Make.make | $(BUILD_TREE)
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(RELEASE_DIRECTORY)/%.o: %.CPP STM32Make.make | $(BUILD_TREE)
	$(CXX) -c $(CXXFLAGS) $< -o $@

#Assembly build
$(RELEASE_DIRECTORY)/%.o: %.s STM32Make.make | $(BUILD_TREE)
	$(AS) -c $(ASFLAGS) $< -o $@

$(RELEASE_DIRECTORY)/%.o: %.S STM32Make.make | $(BUILD_TREE)
	$(AS) -c $(ASFLAGS) $< -o $@

$(RELEASE_DIRECTORY)/%.o: %.sx STM32Make.make | $(BUILD_TREE)
	$(AS) -c $(ASFLAGS) $< -o $@

$(BUILD_DIRECTORY)/$(TARGET).elf: $(OBJECTS) STM32Make.make | $(BUILD_DIRECTORY)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIRECTORY)/%.hex: $(BUILD_DIRECTORY)/%.elf | $(BUILD_DIRECTORY)
	$(HEX) $< $@

$(BUILD_DIRECTORY)/%.bin: $(BUILD_DIRECTORY)/%.elf | $(BUILD_DIRECTORY)
	$(BIN) $< $@

$(BUILD_DIRECTORY)/%.lss: $(BUILD_DIRECTORY)/%.elf | $(BUILD_DIRECTORY)
	$(LSS) $< > $@

$(BUILD_DIRECTORY):
	$(call mkdir_function, $@)

$(BUILD_TREE):
	$(call mkdir_function, $@)

#######################################
# all
#######################################
# default action: build all
all:
	$(BUILD_DIRECTORY)/$(TARGET).elf 
	$(BUILD_DIRECTORY)/$(TARGET).hex 
	$(BUILD_DIRECTORY)/$(TARGET).bin 
	$(BUILD_DIRECTORY)/$(TARGET).lss 


flash: $(BUILD_DIRECTORY)/$(TARGET).elf
	"$(OPENOCD)" -f ./openocd.cfg -c "program $(BUILD_DIRECTORY)/$(TARGET).elf verify reset exit"

#######################################
# erase
#######################################
erase: $(BUILD_DIRECTORY)/$(TARGET).elf
	"$(OPENOCD)" -f ./openocd.cfg -c "init; reset halt; stm32g4x mass_erase 0; exit"

#######################################
# clean up
#######################################
clean:
	$(REMOVE_DIRECTORY_COMMAND) $(BUILD_DIRECTORY)

#######################################
# custom makefile rules
#######################################

	
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIRECTORY)/*.d)

# *** EOF ***