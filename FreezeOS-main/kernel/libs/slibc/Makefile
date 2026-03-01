# Variables
SRC			= $(wildcard src/**/*c)
OBJ			= $(patsubst src/%.c, build/%.o, $(SRC))
LIB			= libs.a

# Flags
CFLAGS		= -Iinclude -I$(PROJECT_ROOT)/kernel/include -Wall -Wextra -ffreestanding -nostdlib -m32
LDFLAGS 	= -shared

# Rules
.PHONY: all

all: clean $(LIB)

$(LIB): $(OBJ)
	ar rcs $@ $^
	rm -rf build

build/%.o: src/%.c
	@mkdir -p $(@D)
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f libs.a