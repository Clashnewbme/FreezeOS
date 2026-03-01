# Variables
BUILD_KERNEL_DIR	:= $(PROJECT_ROOT)/build/kernel
BUILD_BOOT_DIR		:= $(PROJECT_ROOT)/build/boot
BOOT_OBJ			:= $(BUILD_BOOT_DIR)/boot.o
KERNEL_C_FILES		:= $(wildcard *.c) $(wildcard */*.c)
KERNEL_OBJ_FILES	:= $(patsubst %.c, $(BUILD_KERNEL_DIR)/%.o, $(KERNEL_C_FILES))
KERNEL_ELF	 		:= $(BUILD_KERNEL_DIR)/kernel.elf
DEBUG_ELF	 		:= $(BUILD_KERNEL_DIR)/debug.elf
LOADER_ASM	 		:= arch/x86/kernel_loader.asm
LOADER_C	 		:= loader.c
LOADER_OBJ	 		:= $(BUILD_KERNEL_DIR)/loader.o
LOADER_BIN	 		:= $(BUILD_KERNEL_DIR)/loader.bin
KERNEL_BIN	 		:= $(BUILD_KERNEL_DIR)/kernel.bin
KERNEL_ENTRY_ASM	:= arch/x86/kernel_entry.asm
KERNEL_ENTRY_OBJ	:= $(BUILD_KERNEL_DIR)/kernel_entry.o
SLIBC				:= libs/slibc/libs.a

# Configurations
LD_FILE				:= $(PROJECT_ROOT)/configs/kernel/linker.ld
LOADER_LD_FILE		:= $(PROJECT_ROOT)/configs/kernel/loader.ld

# Flags
CFLAGS				:= -Iinclude -Ilibs/slibc/include -ffreestanding -nostdlib -m32 -g -Wall -Wextra

# Rules
.PHONY: all
all: $(LOADER_BIN) $(KERNEL_BIN)

$(LOADER_BIN): $(LOADER_ASM)
	@mkdir -p $(@D)
	nasm -f bin $< -o $@

$(KERNEL_BIN): $(KERNEL_ENTRY_OBJ) $(KERNEL_OBJ_FILES) $(SLIBC)
	ld -T $(LD_FILE) -m elf_i386 -o $(KERNEL_ELF) $^
	objcopy -O binary $(KERNEL_ELF) $@
	
$(BUILD_KERNEL_DIR)/%.o: %.c
	@mkdir -p $(@D)
	gcc $(CFLAGS) -c $< -o $@

$(KERNEL_ENTRY_OBJ): $(KERNEL_ENTRY_ASM)
	@mkdir -p $(@D)
	nasm -f elf32 -g -o $@ $<