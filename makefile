
# list of source files
SRCS =  \
  Source/main.c \
  Source/stm32f10x_it.c \
  Source/system_stm32f10x.c \
  Source/stm32f1xx_nucleo.c \
  startup/startup_stm32f10x_md.s \
  Source/FreeRTOS/Source/croutine.c \
  Source/FreeRTOS/Source/event_groups.c \
  Source/FreeRTOS/Source/list.c \
  Source/FreeRTOS/Source/queue.c \
  Source/FreeRTOS/Source/tasks.c \
  Source/FreeRTOS/Source/timers.c \
  Source/FreeRTOS/Source/portable/GCC/ARM_CM3/port.c \
  Source/FreeRTOS/Source/portable/MemMang/heap_1.c

# target binary name
TARGET_NAME = main

# Location of the STM32F10x Standard Peripheral Library
STM_LIB=Source/Library

# Location of the linker scripts
LDSCRIPT_INC=startup

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump
SIZE=arm-none-eabi-size

CFLAGS  = -Wall -g -std=c99 -Os
CFLAGS += -mlittle-endian -mcpu=cortex-m3 -mthumb
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wl,--gc-sections -Wl,-Map=$(TARGET_NAME).map
CFLAGS += -DSTM32F10X_MD
CFLAGS += -DUSE_STDPERIPH_DRIVER

vpath %.a $(STM_LIB)

ROOT=$(shell pwd)

CFLAGS += -I Source \
	  -I Source/Library \
	  -I $(STM_LIB)/CMSIS/Device/ST/STM32F10x/Include \
	  -I $(STM_LIB)/CMSIS/Include \
	  -I $(STM_LIB)/STM32F10x_StdPeriph_Driver/inc \
	  -I Source/FreeRTOS/Source/include \
	  -I Source/FreeRTOS/Source/portable/GCC/ARM_CM3

OBJS = $(SRCS:.c=.o)

.PHONY: lib proj

all: lib proj

lib:
	$(MAKE) -C $(STM_LIB)

proj: 	$(TARGET_NAME).elf

$(TARGET_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ -L$(STM_LIB) -lstm32f1 -L$(LDSCRIPT_INC) -Tstm32f1.ld
	$(OBJCOPY) -O ihex $(TARGET_NAME).elf $(TARGET_NAME).hex
	$(OBJCOPY) -O binary $(TARGET_NAME).elf $(TARGET_NAME).bin
	$(OBJDUMP) -St $(TARGET_NAME).elf >$(TARGET_NAME).lst
	$(SIZE) $(TARGET_NAME).elf
	
clean:
	find ./ -name '*~' | xargs rm -f	
	rm -f *.o
	rm -f $(TARGET_NAME).elf
	rm -f $(TARGET_NAME).hex
	rm -f $(TARGET_NAME).bin
	rm -f $(TARGET_NAME).map
	rm -f $(TARGET_NAME).lst

cleanlib: clean
	$(MAKE) -C $(STM_LIB) clean

ocd:
	openocd -f /usr/local/Cellar/open-ocd/HEAD/share/openocd/scripts/board/st_nucleo_f103rb.cfg -c init -c "reset halt"
