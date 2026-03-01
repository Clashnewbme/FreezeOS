# Variables
BUILD_BOOT_DIR		:= ../build/boot
BOOT_ASM			:= boot.asm
BOOT_DEBUG_ASM		:= boot-debug.asm
BOOT_BIN			:= $(BUILD_BOOT_DIR)/boot.bin
BOOT_OBJ			:= $(BUILD_BOOT_DIR)/boot.o
BOOT_ELF			:= $(BUILD_BOOT_DIR)/boot.elf

# Configurations
LD_FILE				:= ../configs/boot/linker.ld

# Rulues
.PHONY: all
all: $(BOOT_BIN)

$(BOOT_BIN) : $(BOOT_ASM)
	@mkdir -p $(@D)
	nasm -f bin $< -o $@

# sed 's/\[org 0x7c00\]/;org here/i' $< > $(BOOT_DEBUG_ASM)
# nasm -f elf -g $(BOOT_DEBUG_ASM) -o $(BOOT_OBJ)
# ld -T $(LD_FILE) -m elf_i386 -o $(BOOT_ELF) $(BOOT_OBJ)