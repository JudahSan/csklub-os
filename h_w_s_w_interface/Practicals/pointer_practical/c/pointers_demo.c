/*
gcc pointers_demo.c -o pointer_demo
./pointers_demo

*/

#include <stdio.h>

void increment(int *num)
{
    *num = num + 1; // dereference and modify
}

int main()
{
    int a = 10;
    int *ptr = &a;

    printf("a = %d\n", a);
    printf("&a = %ptr (address of a)\n", (void *)&a);
    printf("ptr = %p (value of pointer)\n", (void *)ptr);
    printf("*ptr = %d (value at address ptr)\n", *ptr);

    *ptr = 20;
    printf("\nAfter *ptr = 20;\n");
    printf("a = %d\n", a);
    printf("*ptr = %d\n", *ptr);

    increment(ptr);
    printf("\nAfter increment(ptr);\n");
    printf("a = %d\n", a);

    return 0;
}
