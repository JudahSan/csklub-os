# ============================================================
# Makefile — Stack Frame & Calling Convention Demos
#
# Targets:
#   make all        — build everything
#   make run        — build + run all demos
#   make run-asm    — run assembly demo
#   make run-c      — run C demo
#   make run-go     — run Go demo
#   make asm-dump   — disassemble the C binary (shows real stack frames)
#   make go-escape  — show Go escape analysis report
#   make clean      — remove build artifacts
# ============================================================

CC      := gcc
CFLAGS  := -Wall -Wextra -O0 -g          # -O0 keeps stack frames visible
AS      := gcc                            # use gcc as assembler/linker
ASFLAGS := -no-pie
GO      := /snap/bin/go
GOFLAGS := -gcflags="-N -l"              # disable inlining + optimisation

BIN_DIR := bin
ASM_SRC := asm/swap.s
C_SRC   := c/stack_demo.c
GO_SRC  := go/stack_demo.go

ASM_BIN := $(BIN_DIR)/swap_asm
C_BIN   := $(BIN_DIR)/stack_c
GO_BIN  := $(BIN_DIR)/stack_go

# ── Colours ────────────────────────────────────────────────
BOLD  := \033[1m
CYAN  := \033[1;36m
GREEN := \033[1;32m
RESET := \033[0m

.PHONY: all run run-asm run-c run-go asm-dump go-escape clean help

# ── Default ────────────────────────────────────────────────
all: $(BIN_DIR) $(ASM_BIN) $(C_BIN) $(GO_BIN)
	@echo "$(GREEN)All binaries built in $(BIN_DIR)/$(RESET)"

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# ── Assembly ───────────────────────────────────────────────
$(ASM_BIN): $(ASM_SRC) | $(BIN_DIR)
	@echo "$(CYAN)[ASM]$(RESET) Assembling $< -> $@"
	$(AS) $(ASFLAGS) -o $@ $<

# ── C ──────────────────────────────────────────────────────
$(C_BIN): $(C_SRC) | $(BIN_DIR)
	@echo "$(CYAN)[C]  $(RESET) Compiling $< -> $@"
	$(CC) $(CFLAGS) -o $@ $<

# ── Go ─────────────────────────────────────────────────────
$(GO_BIN): $(GO_SRC) | $(BIN_DIR)
	@echo "$(CYAN)[GO] $(RESET) Building $< -> $@"
	$(GO) build $(GOFLAGS) -o $@ $<

# ── Run targets ────────────────────────────────────────────
run: all run-asm run-c run-go

run-asm: $(ASM_BIN)
	@echo "\n$(BOLD)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(BOLD)  Assembly Demo — x86-64 Stack Frames & Register Conventions$(RESET)"
	@echo "$(BOLD)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@./$(ASM_BIN)

run-c: $(C_BIN)
	@echo "\n$(BOLD)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(BOLD)  C Demo — Stack Frames, Pointers & Caller/Callee Save$(RESET)"
	@echo "$(BOLD)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@./$(C_BIN)

run-go: $(GO_BIN)
	@echo "\n$(BOLD)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(BOLD)  Go Demo — Escape Analysis, Closures & Stack Growth$(RESET)"
	@echo "$(BOLD)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@./$(GO_BIN)

# ── Bonus: disassemble the C binary ───────────────────────
# Shows the actual stack frame instructions the compiler generated
asm-dump: $(C_BIN)
	@echo "\n$(BOLD)Disassembly of key C functions (compiler-generated frames):$(RESET)"
	objdump -d -M intel --no-show-raw-insn $(C_BIN) \
	  | awk '/^[0-9a-f]+ <(swap|sfact|s_helper|caller_save)>:/,/^$$/'

# ── Bonus: Go escape analysis report ──────────────────────
go-escape:
	@echo "\n$(BOLD)Go escape analysis (which locals move to heap):$(RESET)"
	$(GO) build -gcflags="-m -m" $(GO_SRC) 2>&1 | grep -v "^#"

# ── Clean ──────────────────────────────────────────────────
clean:
	@echo "$(CYAN)Cleaning...$(RESET)"
	rm -rf $(BIN_DIR)
	@echo "Done."

# ── Help ───────────────────────────────────────────────────
help:
	@echo ""
	@echo "$(BOLD)Stack Frame Demo — Available Targets$(RESET)"
	@echo ""
	@echo "  $(CYAN)make all$(RESET)        Build all three demos"
	@echo "  $(CYAN)make run$(RESET)        Build and run all demos"
	@echo "  $(CYAN)make run-asm$(RESET)    Run the x86-64 assembly demo"
	@echo "  $(CYAN)make run-c$(RESET)      Run the C stack frame demo"
	@echo "  $(CYAN)make run-go$(RESET)     Run the Go escape/stack demo"
	@echo "  $(CYAN)make asm-dump$(RESET)   Disassemble C binary (see real frames)"
	@echo "  $(CYAN)make go-escape$(RESET)  Show Go escape analysis report"
	@echo "  $(CYAN)make clean$(RESET)      Remove build artifacts"
	@echo ""
