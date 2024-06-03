// Name - Pratham Agarwal
// Date - 11/12/2023
// 1i. Indentation of a C- program file.
// Program Name - Prettsy_14.c
// gcc (tdm64-1) 10.3.0

// Algorithm:
// 1.	Read the input file name as provided by the user.
// 2.	Check if the file exists. If not, display an error message and terminate the program.
// 3.	Attempt to open and read the input file. If unsuccessful, display an error message and terminate the program.
// 4.	Create an output file with the same name as the input file, but with '_indented' appended to it.
// 5.	Initialize an indentation level variable to keep track of the current level of indentation (e.g., start with 0).
// 6.	Initialize a Boolean variable to keep track of whether the current line is within a block (e.g., set it to false initially).
// 7.	Read the input file line by line.
// 8.	For each line, analyse its content using if-else statements to determine the appropriate indentation level.
// 9.	If the line contains an opening curly brace '{', increase the indentation level.
// 10.	If the line contains a closing curly brace '}', decrease the indentation level.
// 11.	If the line is not a comment and does not contain '{' or '}', add the current level of indentation before the line.
// 12.	If a line starts with '#', it may indicate a preprocessor directive; keep the indentation level the same.
// 13.	Write the indented line to the output file.
// 14.	Repeat steps 7-9 for all lines in the input file.
// 15.	Close both the input and output files.
// 16.	Display a success message to the user indicating that the indentation process is complete, and the indented code has been saved in the output file.
// 17.	Terminate the program.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 100

int main()
{
    printf("*** Prettsy - A C File Indenter *** \n\n\n");
    int increaseIntent = 0;
    // 1. Read the input file name as provided by the user.
    char inputFileName[MAX_FILENAME_LENGTH];
    printf("Enter the File Name to prettify it = ");
    scanf("%s", inputFileName);

    size_t length = strlen(inputFileName);
    if (((inputFileName[length - 1]) != 'c') && ((inputFileName[length - 1]) != 'C'))
    {
        printf("Only Files with Extension '.c' are Allowed!\n ");
        exit(1);
    }

    // Open the C file for reading
    FILE *inputFile = fopen(inputFileName, "r");

    if (inputFile == NULL)
    {
        printf("Error: File '%s' not found.\n", inputFileName);
        return 1;
    }

    // Create the output file
    char outputFilename[MAX_FILENAME_LENGTH];
    snprintf(outputFilename, sizeof(outputFilename), "Indented_%s", inputFileName);
    FILE *outputFile = fopen(outputFilename, "w");

    if (outputFile == NULL)
    {
        printf("Error: Unable to create the output file.\n");
        fclose(inputFile);
        return 1;
    }

    // 4. Initialize an indentation level variable to keep track of the current level of indentation (e.g., start with 0).
    int indentationLevel = 0;

    // 6. Read the input file line by line.
    char line[1000];
    while (fgets(line, sizeof(line), inputFile) != NULL)
    {
        // Trim leading and trailing whitespace
        char *trimmedLine = line;
        while (*trimmedLine == ' ' || *trimmedLine == '\t')
        {
            trimmedLine++;
        }

        size_t len = strlen(trimmedLine);
        while (len > 0 && (trimmedLine[len - 1] == ' ' || trimmedLine[len - 1] == '\t' || trimmedLine[len - 1] == '\n'))
        {
            trimmedLine[--len] = '\0';
        }

        // 8. For each line, analyze its content using if-else statements to determine the appropriate indentation level.

        // 9. If the line contains an opening curly brace '{', increase the indentation level.
        if ((strstr(trimmedLine, "{") != NULL) && (strstr(trimmedLine, "(") != NULL) && (strstr(trimmedLine, ")") != NULL))
        {
            increaseIntent = 2;
        }
        else if (strstr(trimmedLine, "{") != NULL)
        {
            increaseIntent = 1;
        }
        // 10. If the line contains a closing curly brace '}', decrease the indentation level.
        else if (strstr(trimmedLine, "}") != NULL)
        {
            indentationLevel--;
        }

        // 11. Add the current level of indentation before the line.
        for (int i = 0; i < indentationLevel; i++)
        {
            fprintf(outputFile, "\t");
        }

        // 13. Write the indented line to the output file.
        if (increaseIntent == 2)
        {
            char *newTrimmedLine = strtok(trimmedLine, "{");
            fprintf(outputFile, "%s\n", newTrimmedLine);
            for (int i = 0; i < indentationLevel; i++)
            {
                fprintf(outputFile, "\t");
            }
            fprintf(outputFile, "{\n");
        }
        else
        {
            fprintf(outputFile, "%s\n", trimmedLine);
        }
        if (increaseIntent == 1 || increaseIntent == 2)
        {
            indentationLevel++;
            increaseIntent = 0;
        }
    }

    // 15. Close both the input and output files.
    fclose(inputFile);
    fclose(outputFile);

    // 16. Display a success message to the user indicating that the indentation process is complete.
    printf("Code indentation is complete. Check %s for the indented code.\n", outputFilename);

    // 17. Terminate the program.
    return 0;
}
