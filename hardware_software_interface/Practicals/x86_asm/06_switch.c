#include "practice.h"

// Switch statement with jump table
long switch_example(unsigned long x, long y, long z)
{
    long w = 1;
    switch (x)
    {
    case 1:
        w = y * x;
        break;
    case 2:
        w = y / x;
        // Fall through
    case 3:
        w += z;
        break;
    case 5:
    case 6:
        w -= z;
        break;
    default:
        w = 2;
    }
    return w;
}

// Another switch example
const char *get_day_name(int day)
{
    switch (day)
    {
    case 1:
        return "Monday";
    case 2:
        return "Tuesday";
    case 3:
        return "Wednesday";
    case 4:
        return "Thursday";
    case 5:
        return "Friday";
    case 6:
        return "Saturday";
    case 7:
        return "Sunday";
    default:
        return "Invalid";
    }
}

int main()
{
    printf("=== Switch Examples ===\n\n");

    for (unsigned long x = 0; x <= 7; x++)
    {
        long result = switch_example(x, 10, 5);
        printf("switch_example(%lu, 10, 5) = %ld\n", x, result);
    }

    printf("\n");
    for (int day = 0; day <= 8; day++)
    {
        printf("Day %d: %s\n", day, get_day_name(day));
    }

    print_registers();
    return 0;
}
