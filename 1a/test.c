#include <stdio.h>
#define MAX_NAME_LENGTH 20
#define MAX_INTEGER_LENGTH 20
int main()
{
    float num = 5.5;
    int count = 10;
    // Pratham Agarwal
    char name[MAX_NAME_LENGTH];
    printf("Enter Your Name = ");
    scanf("%s", name);
    printf("Your Name is = %s\n", name);
    /* Program */
    if (num > 4)
    {
        printf("Hello World!\n");
        for (int i = 0; i < count; i++)
        {
            printf("%d x %d = %d\n", i, i + 1, i * (i + 1));
        }
    }
    return 0;
}