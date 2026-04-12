#include "practice.h"

// Conditional move example
int absdiff(int x, int y)
{
    int result;
    if (x > y)
    {
        result = x - y;
    }
    else
    {
        result = y - x;
    }
    return result;
}

// Using conditional moves (more efficient)
int absdiff_cmov(int x, int y)
{
    int result = x - y;
    int neg_result = y - x;

    // This can be compiled to cmov instruction
    if (x <= y)
    {
        result = neg_result;
    }
    return result;
}

// Multiple conditions
int max_of_three(int a, int b, int c)
{
    int max = a;
    if (b > max)
        max = b;
    if (c > max)
        max = c;
    return max;
}

// Compare and set
int compare_and_set(int x, int y)
{
    int result = 0;
    if (x > y)
    {
        result = 1;
    }
    else if (x < y)
    {
        result = -1;
    }
    return result;
}

int main()
{
    printf("=== Conditional Operations ===\n\n");

    int test_pairs[][2] = {{10, 5}, {5, 10}, {-5, -10}, {0, 0}};
    for (int i = 0; i < 4; i++)
    {
        int x = test_pairs[i][0];
        int y = test_pairs[i][1];
        printf("absdiff(%d, %d) = %d\n", x, y, absdiff(x, y));
        printf("absdiff_cmov(%d, %d) = %d\n\n", x, y, absdiff_cmov(x, y));
    }

    printf("max_of_three(10, 20, 15) = %d\n", max_of_three(10, 20, 15));
    printf("compare_and_set(5, 3) = %d\n", compare_and_set(5, 3));
    printf("compare_and_set(3, 5) = %d\n", compare_and_set(3, 5));

    print_registers();
    return 0;
}