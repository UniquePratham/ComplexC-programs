// Name - Pratham Agarwal
// Date - 11/12/2023
// 1c. Take a ten-digit integer number and convert it to equivalent number representation in ROMAN and vice-versa.
// Program Name - ConRoman_14.c
// gcc (tdm64-1) 10.3.0

// Algorithm:
// 1.	Read the input text file line by line.
// 2.	For each line, check if it represents a valid input:
//      a.	Use regular expressions or other appropriate methods to validate if the line is a valid ten-digit integer or a Roman numeral.
//      b.  If the line is a valid input, proceed to the conversion step; otherwise, skip it and display error message.
// 3.	For each valid input, determine whether it's a ten-digit integer or a Roman numeral.
// 4.	If the input is a ten-digit integer:
//      a.	Convert the ten-digit integer to its equivalent Roman numeral using the following steps:
//          i.	Break down the integer into its decimal places (billions, hundreds of millions, tens of millions, millions, etc.).
//          ii.	Convert each decimal place to its Roman numeral equivalent independently.
//          iii.Combine the Roman numeral representations of all decimal places to form the complete Roman numeral.
//      b.	Write the input (ten-digit integer) and the corresponding Roman numeral to the output text file in the specified format: [Input] -> [Output]
// 5.	If the input is a Roman numeral:
//      a.	Convert the Roman numeral to its corresponding ten-digit integer using the following steps:
//          i.	Initialize a variable to keep track of the total integer value.
//          ii.	Iterate through the Roman numeral from left to right.
//          iii.Compare each Roman numeral character to the next character:
//              •	If the value of the current character is less than the next character, subtract the current character's value from the total.
//              •	If the value of the current character is greater than or equal to the next character, add the current character's value to the total.
//          iv.	At the end of the iteration, the total will represent the equivalent ten-digit integer.
//       b.	Write the input (Roman numeral) and the corresponding ten-digit integer to the output text file in the specified format: [Input] -> [Output]

// Note - 10 Digit is not possible because the Maximum number of notation possible in roman is for 7 digits.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Function to check if a given string is a valid ten-digit integer
int isValidInteger(const char *line)
{
    int len = strlen(line);
    for (int i = 0; i < len; i++)
    {
        if (!isdigit(line[i]))
        {
            return 0;
        }
    }
    return 1;
}

// Function to check if a given string is a valid Roman numeral
int isValidRoman(const char *line)
{
    const char *validChars = "IVXLCDM̅";
    size_t len = strlen(line);

    for (size_t i = 0; i < len; i++)
    {
        if (strchr(validChars, line[i]) == NULL)
        {
            return 0;
        }
    }

    return 1;
}

// Function to check if a given string is a valid input (either integer or Roman numeral)
int isValidInput(const char *line)
{
    return isValidInteger(line) || isValidRoman(line);
}
// Function to convert a ten-digit integer to its Roman numeral equivalent
void convertToRoman(long long number, char *result)
{
    const char *romanNumerals[] = {"_M", "_I_M", "_D", "_I_D", "_C", "_I_C", "_L", "_I_L", "_X", "_I_X", "_V", "_I_V", "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const long long values[] = {1000000, 900000, 500000, 400000, 100000, 90000, 50000, 40000, 10000, 9000, 5000, 4000, 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

    // Ensure the number is within the valid range
    if (number < 1 || number > 9999999) // Adjust the upper limit as needed
    {
        printf("Error: Input number is out of range\n");
        return;
    }

    int resIndex = 0; // Index for the result string
    for (int k = 0; k < 26; k++)
    {
        while (number >= values[k])
        {
            int arrIndex = k;
            // Append the Roman numeral to the result string
            const char *currentSymbol = romanNumerals[arrIndex];
            size_t len = strlen(currentSymbol);
            if (len == 1)
            {
                result[resIndex++] = currentSymbol[0];
            }
            else
            {
                for (size_t i = 0; i < len; i++)
                {
                    result[resIndex++] = currentSymbol[i];
                }
            }

            number -= values[arrIndex];
            arrIndex++;
        }
    }

    // Null-terminate the result string
    result[resIndex] = '\0';
}

// Function to convert a Roman numeral to its corresponding ten-digit integer
long long convertToInteger(const char *roman)
{
    const char *romanNumerals = "IVXLCDM";
    const int values[] = {1, 5, 10, 50, 100, 500, 1000};
    const char *overline = "M_";

    long long total = 0;
    long long prevValue = 0;

    for (int i = strlen(roman) - 1; i >= 0; i--)
    {
        char currentChar = roman[i];
        long long value;

        if (i >= strlen(overline) && strncmp(&roman[i - strlen(overline) + 1], overline, strlen(overline)) == 0)
        {
            // If the current character is part of the overline sequence, skip it
            continue;
        }

        value = values[strchr(romanNumerals, currentChar) - romanNumerals];

        if (value < prevValue)
        {
            total -= value;
        }
        else
        {
            total += value;
        }

        prevValue = value;
    }

    return total;
}

// Function to process input file and write results to output file
int main()
{
    char line[20];
    char intResult[50];
    long long number, integer;

    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    while (fgets(line, sizeof(line), inputFile) != NULL)
    {
        // Remove newline character if present
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }
        if (isValidInput(line))
        {
            if (isdigit(line[0]))
            {
                number = atoll(line);
                convertToRoman(number, intResult);
                printf("%lld -> %s\n", number, intResult);
                fprintf(outputFile, "%lld -> %s\n", number, intResult);
            }
            else
            {
                integer = convertToInteger(line);
                printf("%s -> %lld\n", line, integer);
                fprintf(outputFile, "%s -> %lld\n", line, integer);
            }
        }
        else
        {
            printf("Invalid input: '%s'\n", line);
        }
        printf("\n");
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
