/*
 * show_bytes.c
 * ------------------------------------------
 * Demonstrates how different data types are represented
 * at the byte level in memory using C.
 *
 * Concept:
 *  - Any data type can be interpreted as a sequence of bytes.
 *  - By casting a variable’s address to (char*), we can examine
 *    each byte in memory.
 *  - This reveals details such as byte order (endianness) and
 *    how data types occupy memory.
 *
 * Compile and run:
 *   $ gcc -o show_bytes_c show_bytes.c
 *   $ ./show_bytes_c
 *
 * Or use the Makefile:
 *   $ make run-c
 */

#include <stdio.h>

/*
 * show_bytes()
 * -------------
 * Prints the byte-level representation of any data value.
 *
 * Parameters:
 *   start - pointer to the beginning of the data in memory
 *   len   - number of bytes to print
 *
 * Output format:
 *   Address    Byte Value (in hex)
 *
 * Example:
 *   0x7fff6f330dcc   0x39
 */

void show_bytes(char *start, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%p\t0x%.2x\n", start + i, *(unsigned char *)(start + i));
    }
    printf("\n");
}

/*
 * Convenience wrappers for specific data types
 * ---------------------------------------------
 * Each function calls show_bytes() with the appropriate type and size.
 */

void show_int(int x)
{
    show_bytes((char *)&x, sizeof(int));
}

void show_float(float x)
{
    show_bytes((char *)&x, sizeof(float));
}

void show_double(double x)
{
    show_bytes((char *)&x, sizeof(double));
}

int main()
{
    int a = 12345;
    float b = 12345.0;
    double c = 12345.0;

    printf("int a = %d;\n", a);
    show_int(a);

    printf("float b = %.2f;\n", b);
    show_float(b);

    printf("double c = %.2f;\n", c);
    show_double(c);

    return 0;
}
