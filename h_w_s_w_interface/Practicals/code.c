// Additional function
// ----------------------------------------------------
// How to compile and run this program:
//
// 1. Compile C source to assembly:
//      gcc -O1 -S code.c -o code.s
//
// 2. Assemble assembly into object file:
//      gcc -c code.s -o code.o
//
// 3. Link object file into an executable:
//      gcc code.o -o code
//
// 4. Run the program:
//      ./code
//
// NB: instead of splitting up, you can just do: 
// gcc code.c -o code
// then
// ./code
// NOTE: This file only defines `sum`.
//       To run it successfully, you need a `main()`
//       function (in C or assembly) that calls `sum`.
// ----------------------------------------------------
#include <stdio.h>

int sum(int x, int y)
{
    int t = x + y;
    return t;
}

int main(void)
{
    int result = sum(2, 3);
    printf("Sum = %d\n", result);
    return 0;
}
