# Compiler and assembler settings
CC = gcc
CFLAGS = -m32 -O0 -g -no-pie -fno-stack-protector
ASFLAGS = -m32 -g
LDFLAGS = -m32 -no-pie

# Source files
C_SRCS = $(wildcard [0-9][0-9]_*.c)
ASM_SRCS = $(wildcard [0-9][0-9]_*.s)
TARGETS = $(C_SRCS:.c=) $(ASM_SRCS:.s=)

# Default target
all: compile-all assemble-all

# Compile C files to executables
compile-all: $(C_SRCS:.c=)

%: %.c practice.h
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -o $@ $<

# Assemble .s files to executables
assemble-all: $(ASM_SRCS:.s=)

%: %.s
	@echo "Assembling $<..."
	$(CC) $(ASFLAGS) -o $@ $<

# Generate assembly from C files
generate-asm: $(C_SRCS:.c=.generated.s)

%.generated.s: %.c practice.h
	@echo "Generating assembly for $<..."
	$(CC) $(CFLAGS) -S -o $@ $<

# Clean up
clean:
	@echo "Cleaning up..."
	rm -f $(TARGETS) *.generated.s
	rm -f $(C_SRCS:.c=.o) $(ASM_SRCS:.s=.o)

# Run all examples
run-all: all
	@echo "\n=== Running all examples ===\n"
	@for prog in $(TARGETS); do \
		echo "\n--- Running $$prog ---"; \
		./$$prog; \
	done

# Debug with GDB
debug-%: %
	gdb -q -ex "break main" -ex "run" ./$*

# View disassembly
disasm-%: %
	objdump -d -M intel ./$* | less

# Help
help:
	@echo "Available targets:"
	@echo "  make all          - Compile all C and assembly files"
	@echo "  make generate-asm - Generate assembly from C files"
	@echo "  make run-all      - Run all compiled examples"
	@echo "  make clean        - Remove compiled files"
	@echo "  make debug-<file> - Debug specific file with GDB"
	@echo "  make disasm-<file>- View disassembly of executable"
	@echo ""
	@echo "Example files:"
	@echo "  01_basic_moves    - MOV instructions and registers"
	@echo "  02_swap_example   - 32-bit vs 64-bit swapping"
	@echo "  03_arithmetic     - Arithmetic operations"
	@echo "  04_conditionals   - Condition codes and branches"
	@echo "  05_loops          - Loop implementations"
	@echo "  06_switch         - Switch statements and jump tables"
	@echo "  07_address_modes  - Memory addressing modes"

.PHONY: all clean run-all help generate-asm assemble-all