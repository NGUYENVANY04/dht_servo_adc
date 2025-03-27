CC=arm-none-eabi-gcc
MACH=cortex-m3
CFLAGS= -Ilib -mcpu=$(MACH) -mthumb -mfloat-abi=soft -Wall -O0
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T linker.ld -Wl,-Map=final.map
LDFLAGS_SH= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=rdimon.specs -T linker.ld -Wl,-Map=final.map
#CFLAGS := -Ilib -mcpu=$(MACH) -mthumb -Wall # OPTION COMPILER
PRO_SRC := src
PRO_LIB := lib 
PRO_DRI := drivers
PROJ_NAME := TEST 
OUTPUT_PATH := $(PRO_DIR)

all : start_up.o main.o rcc.o gpio.o log_info.o uart.o dht.o systick.o syscall.o firmware.elf firmware.bin flash 
	
main.o: $(strip $(PRO_SRC))/main.c
	$(CC) -c $(CFLAGS) $(strip $(PRO_SRC))/main.c -o  $(strip $(PRO_SRC))/main.o
rcc.o:  $(strip $(PRO_LIB))/rcc.c  $(strip $(PRO_LIB))/rcc.h
	$(CC) -c $(CFLAGS) $(strip $(PRO_LIB))/rcc.c -o  $(strip $(PRO_LIB))/rcc.o

gpio.o: $(strip $(PRO_LIB))/gpio.c  $(strip $(PRO_LIB))/gpio.h
	$(CC) -c $(CFLAGS) $(strip $(PRO_LIB))/gpio.c -o \
	$(strip $(PRO_LIB))/gpio.o
uart.o: $(strip $(PRO_LIB))/uart.c  $(strip $(PRO_LIB))/uart.h
	$(CC) -c $(CFLAGS) $(strip $(PRO_LIB))/uart.c -o \
	$(strip $(PRO_LIB))/uart.o
systick.o: $(strip $(PRO_LIB))/systick.c  $(strip $(PRO_LIB))/systick.h
	$(CC) -c $(CFLAGS) $(strip $(PRO_LIB))/systick.c -o \
	$(strip $(PRO_LIB))/systick.o
dht.o:  $(strip $(PRO_SRC)/$(PRO_DRI))/dht.c  $(strip $(PRO_SRC)/$(PRO_DRI))/dht.h
	$(CC) -c $(CFLAGS) $(strip $(PRO_SRC)/$(PRO_DRI))/dht.c  -o \
        $(strip $(PRO_SRC)/$(PRO_DRI))/dht.o    
log_info.o:  $(strip $(PRO_SRC)/$(PRO_DRI))/log_info.c  $(strip $(PRO_SRC)/$(PRO_DRI))/log_info.h
	$(CC) -c $(CFLAGS) $(strip $(PRO_SRC)/$(PRO_DRI))/log_info.c  -o \
        $(strip $(PRO_SRC)/$(PRO_DRI))/log_info.o   
syscall.o:$(strip $(PRO_LIB))/syscall.c  
	$(CC) -c $(CFLAGS) $(strip $(PRO_LIB))/syscall.c -o \
	$(strip $(PRO_LIB))/syscall.o

start_up.o: Startup/startup.c
	$(CC)  -c $(CFLAGS) Startup/startup.c -o  Startup/startup.o
	
firmware.elf: start_up.o main.o rcc.o gpio.o syscall.o uart.o systick.o linker.ld 
	$(CC) -nostdlib -T linker.ld -Wl,-Map=final.map \
	$(strip $(PRO_LIB))/rcc.o \
	$(strip $(PRO_LIB))/gpio.o \
	$(strip $(PRO_SRC))/main.o  \
	$(strip $(PRO_LIB))/systick.o \
	$(strip $(PRO_SRC)/$(PRO_DRI))/log_info.o \
	$(strip $(PRO_SRC)/$(PRO_DRI))/dht.o \
	$(strip $(PRO_LIB))/uart.o \
	Startup/startup.o $(strip $(PRO_LIB))/syscall.o -o firmware.elf
firmware.bin: firmware.elf
	arm-none-eabi-objcopy -O binary firmware.elf firmware.bin

flash: firmware.bin
	st-flash --reset write firmware.bin 0x8000000

clear:
	rm -rf Startup/startup.o src/main.o lib/rcc.o lib/gpio.o lib/systick.o firmware.bin firmware.elf 
