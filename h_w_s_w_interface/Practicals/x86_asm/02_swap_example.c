#include "practice.h"

// 32-bit swap using pointers
void swap32(int *xp, int *yp)
{
    int t0 = *xp;
    int t1 = *yp;
    *xp = t1;
    *yp = t0;
}

// 64-bit swap using pointers
void swap64(long long *xp, long long *yp)
{
    long long t0 = *xp;
    long long t1 = *yp;
    *xp = t1;
    *yp = t0;
}

// Inline assembly swap
void swap_asm(int *xp, int *yp)
{
    __asm__ volatile(
        "movl (%0), %%eax\n"
        "movl (%1), %%ebx\n"
        "movl %%ebx, (%0)\n"
        "movl %%eax, (%1)\n"
        :
        : "r"(xp), "r"(yp)
        : "%eax", "%ebx", "memory");
}

int main()
{
    printf("=== Swap Examples ===\n\n");

    // 32-bit swap
    int a = 5, b = 10;
    printf("32-bit swap:\n");
    printf("Before: a=%d, b=%d\n", a, b);
    swap32(&a, &b);
    printf("After:  a=%d, b=%d\n", a, b);

    // Reset
    a = 5;
    b = 10;

    // Inline assembly swap
    printf("\nInline assembly swap:\n");
    printf("Before: a=%d, b=%d\n", a, b);
    swap_asm(&a, &b);
    printf("After:  a=%d, b=%d\n", a, b);

    // 64-bit swap
    long long c = 10000000000LL, d = 20000000000LL;
    printf("\n64-bit swap:\n");
    printf("Before: c=%lld, d=%lld\n", c, d);
    swap64(&c, &d);
    printf("After:  c=%lld, d=%lld\n\n", c, d);

    return 0;
}