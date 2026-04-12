#ifndef PRACTICE_H
#define PRACTICE_H

#include <stdio.h>
#include <stdlib.h>

// Helper function to print registers (inline assembly)
static inline void print_registers()
{
    unsigned int eax, ebx, ecx, edx, esi, edi, ebp, esp;

    __asm__ volatile(
        "movl %%eax, %0\n"
        "movl %%ebx, %1\n"
        "movl %%ecx, %2\n"
        "movl %%edx, %3\n"
        "movl %%esi, %4\n"
        "movl %%edi, %5\n"
        "movl %%ebp, %6\n"
        "movl %%esp, %7\n"
        : "=m"(eax), "=m"(ebx), "=m"(ecx), "=m"(edx),
          "=m"(esi), "=m"(edi), "=m"(ebp), "=m"(esp));

    printf("\n=== Register Dump ===\n");
    printf("EAX: 0x%08x (%d)\n", eax, eax);
    printf("EBX: 0x%08x (%d)\n", ebx, ebx);
    printf("ECX: 0x%08x (%d)\n", ecx, ecx);
    printf("EDX: 0x%08x (%d)\n", edx, edx);
    printf("ESI: 0x%08x (%d)\n", esi, esi);
    printf("EDI: 0x%08x (%d)\n", edi, edi);
    printf("EBP: 0x%08x (%d)\n", ebp, ebp);
    printf("ESP: 0x%08x (%d)\n", esp, esp);
    printf("===================\n\n");
}

// Function to print memory at address
static inline void print_memory(void *addr, int bytes)
{
    unsigned char *p = (unsigned char *)addr;
    printf("Memory at %p: ", addr);
    for (int i = 0; i < bytes; i++)
    {
        printf("%02x ", p[i]);
    }
    printf("\n");
}

#endif
