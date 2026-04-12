#include "practice.h"

// Function to demonstrate basic MOV instructions
void demonstrate_mov()
{
    int a = 42;
    int b = 0;
    int c = 0;

    printf("=== Basic MOV Instructions ===\n");
    printf("Initial: a=%d, b=%d, c=%d\n", a, b, c);

    // These will be compiled to MOV instructions
    b = a;     // movl %eax, %ebx (register to register)
    c = 100;   // movl $100, %ecx (immediate to register)
    a = b + c; // This becomes addl, but we'll see in next example

    printf("After moves: a=%d, b=%d, c=%d\n\n", a, b, c);
}

// Function to demonstrate different operand sizes
void demonstrate_sizes()
{
    printf("=== Operand Sizes ===\n");
    int int_val = 0x12345678;
    short short_val = 0;
    char char_val = 0;

    // Different move sizes
    __asm__ volatile(
        "movl %2, %%eax\n" // Move 4 bytes
        "movw %%ax, %0\n"  // Move lower 2 bytes (word)
        "movb %%al, %1\n"  // Move lower 1 byte
        : "=m"(short_val), "=m"(char_val)
        : "m"(int_val)
        : "%eax");

    printf("int_val: 0x%08x\n", int_val);
    printf("short_val (lower 2 bytes): 0x%04x\n", short_val);
    printf("char_val (lower 1 byte): 0x%02x\n\n", char_val);
}

int main()
{
    demonstrate_mov();
    demonstrate_sizes();
    print_registers();
    return 0;
}