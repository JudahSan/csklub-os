#include "practice.h"

// While loop: factorial
int fact_while(int n)
{
    int result = 1;
    while (n > 1)
    {
        result *= n;
        n--;
    }
    return result;
}

// Do-while loop
int fact_do_while(int n)
{
    int result = 1;
    do
    {
        result *= n;
        n--;
    } while (n > 1);
    return result;
}

// For loop with bit manipulation
int ipwr_for(int x, unsigned int p)
{
    int result = 1;
    for (result = 1; p != 0; p = p >> 1)
    {
        if (p & 0x1)
            result *= x;
        x *= x;
    }
    return result;
}

// Nested loops
int matrix_sum(int matrix[3][3])
{
    int sum = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            sum += matrix[i][j];
        }
    }
    return sum;
}

int main()
{
    printf("=== Loop Examples ===\n\n");

    printf("fact_while(5) = %d\n", fact_while(5));
    printf("fact_do_while(5) = %d\n", fact_do_while(5));
    printf("2^5 = %d\n", ipwr_for(2, 5));

    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    printf("Matrix sum = %d\n\n", matrix_sum(matrix));

    print_registers();
    return 0;
}