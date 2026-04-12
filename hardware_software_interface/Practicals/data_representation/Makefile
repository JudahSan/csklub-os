# Makefile for Examining Data Representations
# -------------------------------------------
# Project structure:
#   c/show_bytes.c   - C implementation
#   go/show_bytes.go - Go implementation
#
# Usage:
#   make            # Build both executables
#   make run-c      # Run the C version
#   make run-go     # Run the Go version
#   make clean      # Remove build artifacts

# Compiler and flags for C
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Paths
CDIR = c
GODIR = go

# Output binaries
CBIN = $(CDIR)/show_bytes_c
GOBIN = $(GODIR)/show_bytes_go

# Default target
all: $(CBIN) $(GOBIN)

# -----------------------
# Build Targets
# -----------------------

$(CBIN): $(CDIR)/show_bytes.c
	@echo "Building C implementation..."
	$(CC) $(CFLAGS) -o $(CBIN) $(CDIR)/show_bytes.c

$(GOBIN): $(GODIR)/show_bytes.go
	@echo "Building Go implementation..."
	cd $(GODIR) && go build -o show_bytes_go show_bytes.go

# -----------------------
# Run Targets
# -----------------------

run-c: $(CBIN)
	@echo "\n--- Running C version ---"
	./$(CBIN)

run-go: $(GOBIN)
	@echo "\n--- Running Go version ---"
	./$(GOBIN)

# -----------------------
# Clean Target
# -----------------------

clean:
	@echo "Cleaning build artifacts..."
	rm -f $(CBIN) $(GOBIN)
