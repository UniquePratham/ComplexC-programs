// Name - Pratham Agarwal
// Date - 11/12/2023
// 1j. Integer Number to Word Conversion.
// Program Name - IntToWord_14.c
// gcc (tdm64-1) 10.3.0

// Algorithm:
// 1.	Read the input text file containing integer numbers.
// 2.	For each line in the input file, extract the integer value as the current number to be converted.
// 3.	Check if the current number is zero. If it is, add "Zero" to the output text file and proceed to the next number.
// 4.	Divide the current number into groups of three digits from right to left. For example, if the number is 1234567, it will be divided into three groups: 1,234,567.
// 5.	For each group of three digits, convert it into words by examining the hundreds, tens, and units’ positions. Use If-Else statements to handle different cases. For example, "123" becomes "One Hundred Twenty-Three."
// 6.	Combine the word representations of groups to form the complete word representation of the current number. Ensure the appropriate use of words like "Thousand," "Million," etc., to indicate the scale of the number.
// 7.	Write the word representation of the current number to the output text file.
// 8.	Repeat steps 3 to 7 for all the numbers in the input text file.
// 9.	Close both the input and output files.
// 10.	The program has successfully converted integer numbers into their word representations, and the output text file now contains the desired results.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char *units[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
char *teens[] = {"", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
char *tens[] = {"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
char *scale[] = {"", "Thousand", "Million", "Billion", "Trillion"};

void convertNumberToWords(long long number, char *result)
{
    // Initialize result with an empty string
    result[0] = '\0';

    // Handle the special case when the input number is 0
    if (number == 0)
    {
        sprintf(result, "Zero");
        return;
    }

    int scaleIndex = 0;
    int flag = 0;

    while (number > 0)
    {
        int temp = number % 1000;
        int temp2 = temp % 100;
        int temp3 = (temp - temp2) / 100;
        int temp4 = temp2 % 10;
        int temp5 = (temp2 - temp4) / 10;

        char tempResult[500] = ""; // Use a temporary buffer

        if (temp3 > 0)
        {
            strcat(tempResult, units[temp3]);
            strcat(tempResult, " Hundred");
            if (temp2 > 0)
            {
                strcat(tempResult, " and ");
            }
        }

        if (temp2 >= 11 && temp2 <= 19)
        {
            if (temp5 > 0 && result[0] == '\0')
            {
                strcat(tempResult, " and ");
            }
            strcat(tempResult, teens[temp2 - 10]);
        }
        else
        {
            if (temp5 > 0)
            {
                strcat(tempResult, tens[temp5]);
                if (temp4 > 0)
                {
                    strcat(tempResult, "-");
                }
            }

            if (temp4 > 0)
            {
                strcat(tempResult, units[temp4]);
            }
        }

        if (flag > 0)
        {
            strcat(tempResult, " ");
            strcat(tempResult, scale[flag]);
        }

        strcat(tempResult, " ");
        strcat(tempResult, result); // Append to the existing result
        strcpy(result, tempResult); // Copy the temporary buffer back to the result

        flag++;
        number = number / 1000;
    }
}

int main()
{
    printf("*** Integer to Word Conversion (Upto 10 Digits) ***\n\n");
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");
    printf("Reading Integers from input.txt\n\n");
    if (inputFile == NULL || outputFile == NULL)
    {
        printf("Error opening files.\n");
        return 1;
    }

    char line[20];
    while (fgets(line, sizeof(line), inputFile) != NULL)
    {
        long long number = atoi(line);

        char *result = (char *)malloc(500 * sizeof(char));
        if (result == NULL)
        {
            printf("Memory allocation error.\n");
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }

        convertNumberToWords(number, result);

        // Check if the result is empty
        if (result[0] == '\0')
        {
            printf("Conversion error for input: %s\n", line);
            free(result);
            continue;
        }

        fprintf(outputFile, "%s\n", result);

        free(result);
    }
    printf("Integers have been converted and saved to output.txt\n\n");
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
