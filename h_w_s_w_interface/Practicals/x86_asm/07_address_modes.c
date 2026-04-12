#include "practice.h"

// Demonstrate different addressing modes
void array_operations()
{
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;

    printf("=== Addressing Modes ===\n");
    printf("Base addressing: arr[0] = %d\n", arr[0]);
    printf("Index addressing: arr[2] = %d\n", arr[2]);
    printf("Pointer arithmetic: *(ptr+3) = %d\n", *(ptr + 3));
    printf("Displacement: ptr[4] = %d\n\n", ptr[4]);
}

// Structure to demonstrate displacement addressing
struct Point
{
    int x;
    int y;
    int z;
};

void structure_operations()
{
    struct Point p = {10, 20, 30};
    struct Point *ptr = &p;

    printf("=== Structure Field Access (Displacement Addressing) ===\n");
    printf("p.x = %d (offset 0)\n", p.x);
    printf("p.y = %d (offset 4)\n", p.y);
    printf("p.z = %d (offset 8)\n\n", p.z);
    printf("ptr->x = %d\n", ptr->x);
    printf("ptr->y = %d\n", ptr->y);
    printf("ptr->z = %d\n\n", ptr->z);
}

// Scaled index addressing
void matrix_access(int matrix[4][4], int row, int col)
{
    // This will use scaled index addressing
    int value = matrix[row][col];
    printf("matrix[%d][%d] = %d\n", row, col, value);
}

int main()
{
    array_operations();
    structure_operations();

    int matrix[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}};

    matrix_access(matrix, 2, 3);
    print_registers();

    return 0;
}
