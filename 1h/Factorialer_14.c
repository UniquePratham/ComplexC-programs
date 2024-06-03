// Name - Pratham Agarwal
// Date - 11/12/2023
// 1h. Find the factorial of any integer number. The numbers could be at most ten-digit long.
// Program Name - Factorialer_14.c
// gcc (tdm64-1) 10.3.0

// Algorithm:
// 1.	Read the input from the text file, which contains a single integer, and store it in a variable (let's call it 'n').
// 2.	Initialize an accumulator variable (let's call it 'factorial') to 1. This variable will store the final factorial value.
// 3.	Iterate from 1 to 'n', performing the following operation in each iteration:
// -	Multiply 'factorial' by the current value of the iteration variable.
// 4.	After the iteration completes, 'factorial' will contain the factorial of 'n'.
// 5.	Write the value of 'factorial' to the output text file.
// 6.	Close the input and output files, completing the factorial calculation process.
#include <stdio.h>
#include <gmp.h>

int main()
{
    // Step 1: Read input from the text file
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL)
    {
        perror("Error opening input file");
        return 1;
    }

    mpz_t n;
    mpz_init(n);
    fscanf(inputFile, "%Zd", n);

    // Step 2: Initialize accumulator variable
    mpz_t factorial;
    mpz_init_set_ui(factorial, 1);

    // Step 3: Calculate factorial
    for (mpz_t i; mpz_cmp_ui(i, 1) <= 0; mpz_sub_ui(i, i, 1))
    {
        mpz_mul(factorial, factorial, i);
    }

    // Step 4: Write the result to the output text file
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL)
    {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }

    gmp_fprintf(outputFile, "%Zd", factorial);

    // Step 5: Close files
    fclose(inputFile);
    fclose(outputFile);

    // Free allocated memory
    mpz_clear(n);
    mpz_clear(factorial);

    return 0;
}
