// Name - Pratham Agarwal
// Date - 11/12/2023
// 1b. Take a series of ‘n’ numbers of characters and generate all permutations.
// Program Name - GenPermut_14.c
// gcc (tdm64-1) 10.3.0

// Algorithm:
// 1.	Start by reading the input text file to obtain the series of 'n' characters.
// 2.	Initialize a list to store the generated permutations.
// 3.	Establish a recursive process that accepts the current characters, the characters not yet used, and the list of permutations as parameters.
// 4.	In the recursive process:
//      a.	If there are no characters left to use, add the current permutation to the list.
//      b.	Otherwise, for each unused character, add it to the current permutation, call the process recursively with the updated parameters, and remove the added character to explore different combinations.
// 5.	After the recursive calls, write the list of permutations to the output text file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PERMUTATIONS 100000 // Maximum number of Permutations
#define MAX_CHARACTERS 1000     // Maximum number of Characters
#define MAX_HEADER_LENGTH 1000  // Maximum length of Header

void generatePermutations(char *current, char *unused, int currentIndex, int n, char **permutations, int *count)
{
    if (currentIndex == n)
    {
        permutations[*count] = strdup(current);
        (*count)++;
        return;
    }

    for (int i = 0; i < strlen(unused); i++)
    {
        current[currentIndex] = unused[i];
        current[currentIndex + 1] = '\0'; // Null-terminate the current string
        char *newUnused = (char *)malloc((n - currentIndex) * sizeof(char));

        // Copy the remaining unused characters to newUnused
        int k = 0;
        for (int j = 0; j < strlen(unused); j++)
        {
            if (j != i)
            {
                newUnused[k++] = unused[j];
            }
        }
        newUnused[k] = '\0'; // Null-terminate the newUnused string

        generatePermutations(current, newUnused, currentIndex + 1, n, permutations, count);
        free(newUnused);
    }
}

int main()
{
    char header[MAX_HEADER_LENGTH];
    char series[MAX_CHARACTERS];
    const char *inputFileName = "input.txt";
    const char *outputFileName = "output.txt";

    // Open input file
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL)
    {
        fprintf(stderr, "Error opening input file\n");
        return 1;
    }
    fgets(header, sizeof(header), inputFile);
    // Read the series of 'n' characters
    fgets(series, sizeof(series), inputFile);
    if (series[0] == '\0' || series[0] == '\n')
    {
        printf("Error reading the series of characters.\n");
        fclose(inputFile);
        return 1;
    }
    printf("%s", header);     // Print the header for reference
    printf("'%s'\n", series); // Print the series for reference

    int n = strlen(series);
    if (n > 0 && series[n - 1] == '\n')
    {
        series[--n] = '\0'; // Remove the newline character if present
    }

    // Initialize variables
    char current[n + 1];
    char unused[n + 1];
    strcpy(unused, series);

    char *permutations[MAX_PERMUTATIONS];
    int count = 0;

    // Generate permutations
    generatePermutations(current, unused, 0, n, permutations, &count);

    // Open output file
    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL)
    {
        fprintf(stderr, "Error opening output file\n");
        return 1;
    }

    fprintf(outputFile, "The Generated Permutations for the Characters %s are: \n\n", series);
    // Write permutations to the output file
    for (int i = 0; i < count; i++)
    {
        fprintf(outputFile, "%s\n", permutations[i]);
        free(permutations[i]);
    }

    fclose(outputFile);

    printf("Permutations generated for the characters %s and written to %s\n", series, outputFileName);
    return 0;
}
