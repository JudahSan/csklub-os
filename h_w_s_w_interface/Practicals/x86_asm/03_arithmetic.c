#include "practice.h"

// Various arithmetic operations
int arithmetic_ops(int x, int y, int z)
{
    int t1 = x + y;
    int t2 = z + t1;
    int t3 = x + 4;
    int t4 = y * 48;
    int t5 = t3 + t4;
    int result = t2 * t5;

    printf("x=%d, y=%d, z=%d\n", x, y, z);
    printf("t1 (x+y) = %d\n", t1);
    printf("t2 (z+t1) = %d\n", t2);
    printf("t3 (x+4) = %d\n", t3);
    printf("t4 (y*48) = %d\n", t4);
    printf("t5 (t3+t4) = %d\n", t5);
    printf("Result = %d\n", result);

    return result;
}

// Bitwise operations
int bitwise_ops(int x, int y)
{
    int and_op = x & y;
    int or_op = x | y;
    int xor_op = x ^ y;
    int not_op = ~x;
    int left_shift = x << 2;
    int right_shift = x >> 1;

    printf("\n=== Bitwise Operations ===\n");
    printf("x=0x%08x (%d), y=0x%08x (%d)\n", x, x, y, y);
    printf("x & y = 0x%08x (%d)\n", and_op, and_op);
    printf("x | y = 0x%08x (%d)\n", or_op, or_op);
    printf("x ^ y = 0x%08x (%d)\n", xor_op, xor_op);
    printf("~x = 0x%08x (%d)\n", not_op, not_op);
    printf("x << 2 = 0x%08x (%d)\n", left_shift, left_shift);
    printf("x >> 1 = 0x%08x (%d)\n", right_shift, right_shift);

    return xor_op;
}

// Using LEA for arithmetic
int lea_arithmetic(int x, int y, int z)
{
    // These will be optimized to use LEA instructions
    int a = x + y;      // leal (%eax, %ebx), %ecx
    int b = x * 4;      // leal 0(,%eax,4), %ecx
    int c = y * 8 + 10; // leal 10(%ebx,%ebx,8), %ecx
    int d = x + y * 2;  // leal (%eax,%ebx,2), %ecx

    printf("\n=== LEA Arithmetic ===\n");
    printf("x + y = %d\n", a);
    printf("x * 4 = %d\n", b);
    printf("y * 8 + 10 = %d\n", c);
    printf("x + y*2 = %d\n", d);

    return a + b + c + d;
}

int main()
{
    printf("=== Arithmetic Operations ===\n\n");
    arithmetic_ops(10, 5, 3);
    bitwise_ops(0x0F0F0F0F, 0x00FF00FF);
    lea_arithmetic(7, 3, 2);
    print_registers();
    return 0;
}