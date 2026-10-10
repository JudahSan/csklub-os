CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -std=c11 -g
GO := go

BUILD_DIR := build
C_BIN := $(BUILD_DIR)/mark_sweep
GO_BIN := $(BUILD_DIR)/gc_demo

.PHONY: all build-c build-go run run-c run-go clean help

all: build-c build-go

$(BUILD_DIR):
	mkdir -p $@

$(C_BIN): c/mark_sweep.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(GO_BIN): go/gc_demo.go | $(BUILD_DIR)
	$(GO) build -o $@ $<

build-c: $(C_BIN)

build-go: $(GO_BIN)

run: run-c run-go

run-c: $(C_BIN)
	./$(C_BIN)

run-go: $(GO_BIN)
	./$(GO_BIN)

clean:
	rm -rf $(BUILD_DIR)

help:
	@echo "Targets:"
	@echo "  make all       Build the C and Go examples"
	@echo "  make run       Build and run both examples"
	@echo "  make run-c     Build and run the C mark-and-sweep example"
	@echo "  make run-go    Build and run the Go garbage-collection example"
	@echo "  make clean     Remove generated binaries"
