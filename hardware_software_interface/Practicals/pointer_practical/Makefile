# ================================
# Pointer Practical Makefile
# Supports both C and Go examples
# ================================

# --- Directories ---
C_DIR := c
GO_DIR := go

# --- Executable Names ---
C_EXEC := $(C_DIR)/pointers_demo
GO_FILE := $(GO_DIR)/pointers_demo.go

# --- Default Target ---
.PHONY: all
all: build-c build-go

# --- Build C Program ---
.PHONY: build-c
build-c:
	@echo "🔧 Building C program..."
	gcc $(C_DIR)/pointers_demo.c -o $(C_EXEC)
	@echo "✅ C build complete -> $(C_EXEC)"

# --- Run C Program ---
.PHONY: run-c
run-c: build-c
	@echo "\n🚀 Running C program...\n"
	./$(C_EXEC)

# --- Build Go Program ---
.PHONY: build-go
build-go:
	@echo "🔧 Checking Go module setup..."
	cd $(GO_DIR) && go mod tidy
	@echo "✅ Go module ready"

# --- Run Go Program ---
.PHONY: run-go
run-go: build-go
	@echo "\n🚀 Running Go program...\n"
	cd $(GO_DIR) && go run $(GO_FILE)

# --- Clean ---
.PHONY: clean
clean:
	@echo "🧹 Cleaning build artifacts..."
	rm -f $(C_EXEC)
	@echo "✅ Clean complete"
