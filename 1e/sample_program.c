// SampleProgram.c

#include <stdio.h>

int main()
{
    printf("Hello, this is a sample program!\n");
    long long x = 0;
    // Some time-consuming task
    for (int i = 0; i < 10; ++i)
    {
        x++;
    }
    printf("X = %lld\n", x);
    printf("Sample program execution complete.\n\n");

    return 0;
}
