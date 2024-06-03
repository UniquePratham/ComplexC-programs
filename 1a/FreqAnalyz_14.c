// Name - Pratham Agarwal
// Date - 4/12/2023
// 1a. Take an extensive program written by others in C language. Perform the frequency analysis of characters, reserved words.
// Program Name - FreqAnalyz_14.c
// gcc (tdm64-1) 10.3.0

// Algorithm:
// 1.	Start by reading the provided C program source code.
// 2.	Initialize two dictionaries or lists for character frequency and reserved word frequency, setting all counters to zero.
// 3.	For character frequency analysis:
//      a.	Iterate through the code character by character.
//      b.	For each character, increment the corresponding counter in the character frequency data structure.
// 4.	For reserved word frequency analysis:
//      a.	Identify a list of reserved words used in C.
//      b.	Search for each reserved word in the code.
// c.	When a reserved word is found, increment the corresponding counter in the reserved word frequency list.
// 5.	After processing the entire code, create an output report.
// 6.	In the report, present the character frequency analysis, followed by the reserved word frequency analysis.

#include <stdio.h>     // For Input/Output
#include <stdlib.h>    // For FileHandling
#include <string.h>    // For String
#include <ctype.h>     // For Characters
#include <sys/stat.h>  // For MKDIR
#include <sys/types.h> // For MKDIR
#define MAX_WORD_LEN 30
#define MAX_FILENAME_LENGTH 100
#define MAX_OUTPUTFILENAME_LENGTH 100
#define MAX_FILEPATH_LENGTH 200

// Structure to store information about reserved words
typedef struct
{
    char word[MAX_WORD_LEN];
    int frequency;
} ReservedWordInfo;

// Global declaration of keywords array
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
    "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short",
    "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while", "#define", "printf", "scanf", "#include", "bool"};

// Function to check if a character is a valid part of a word
int isValidChar(char ch)
{
    return isalnum(ch) || ch == '_';
}

// Function to convert a string to lowercase
void toLowercase(char *str)
{
    while (*str)
    {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

// Function to perform frequency analysis on characters
void analyzeCharacters(FILE *file, int charFrequency[])
{
    int ch;
    while ((ch = fgetc(file)) != EOF)
    {
        // Increment the corresponding counter for all characters, including spaces
        charFrequency[ch]++;
    }
}

// Function to compare ReservedWordInfo structs for sorting
int compareReservedWordInfo(const void *a, const void *b)
{
    return ((ReservedWordInfo *)b)->frequency - ((ReservedWordInfo *)a)->frequency;
}

// Function to perform frequency analysis on reserved words
void analyzeReservedWords(FILE *file, ReservedWordInfo reservedWords[], int *totalReservedWords)
{
    char word[MAX_WORD_LEN];
    int ch;
    int index;

    while ((ch = fgetc(file)) != EOF)
    {
        if (isValidChar(ch) || ch == '#')
        {
            int i = 0;

            // Handle preprocessor directives
            if (ch == '#')
            {
                i = 0;
                word[i++] = ch;

                while ((ch = fgetc(file)) != EOF && isalnum(ch))
                {
                    word[i++] = ch;
                }

                word[i] = '\0';

                // Check if the word is #include or #define
                if (strcasecmp(word, "#include") == 0 || strcasecmp(word, "#define") == 0)
                {
                    // Update the frequency of the reserved word
                    int found = 0;
                    for (int j = 0; j < *totalReservedWords; j++)
                    {
                        if (strcasecmp(word, reservedWords[j].word) == 0)
                        {
                            reservedWords[j].frequency++;
                            found = 1;
                            break;
                        }
                    }

                    // If the word is not in the array, add it
                    if (!found)
                    {
                        strcpy(reservedWords[*totalReservedWords].word, word);
                        reservedWords[*totalReservedWords].frequency = 1;
                        (*totalReservedWords)++;
                    }
                }

                // Skip the rest of the line
                while (ch != '\n' && ch != EOF)
                {
                    ch = fgetc(file);
                }

                continue; // Move to the next iteration of the loop
            }

            // Process regular words
            while (isValidChar(ch) && i < MAX_WORD_LEN - 1)
            {
                word[i++] = ch;
                ch = fgetc(file);
            }
            word[i] = '\0';

            // Check if the word is a reserved word
            for (index = 0; index < sizeof(keywords) / sizeof(keywords[0]); index++)
            {
                if (strcasecmp(word, keywords[index]) == 0)
                {
                    // Update the frequency of the reserved word
                    int found = 0;
                    for (int j = 0; j < *totalReservedWords; j++)
                    {
                        if (strcasecmp(word, reservedWords[j].word) == 0)
                        {
                            reservedWords[j].frequency++;
                            found = 1;
                            break;
                        }
                    }

                    // If the word is not in the array, add it
                    if (!found)
                    {
                        strcpy(reservedWords[*totalReservedWords].word, word);
                        reservedWords[*totalReservedWords].frequency = 1;
                        (*totalReservedWords)++;
                    }

                    break;
                }
            }
        }
    }
}

// Function to analyze and count comments
void analyzeComments(FILE *file, int *singleLineComments, int *multiLineComments)
{
    int ch;
    int insideComment = 0; // Flag to track whether currently inside a multi-line comment

    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '/')
        {
            ch = fgetc(file);
            if (ch == '/') // Single-line comment
            {
                (*singleLineComments)++;
                while ((ch = fgetc(file)) != '\n' && ch != EOF)
                {
                    // Move to the end of the line
                }
            }
            else if (ch == '*') // Multi-line comment
            {
                (*multiLineComments)++;
                insideComment = 1;
                while (insideComment)
                {
                    while ((ch = fgetc(file)) != '*')
                    {
                        if (ch == EOF)
                        {
                            insideComment = 0;
                            break;
                        }
                    }
                    ch = fgetc(file);
                    if (ch == '/')
                    {
                        insideComment = 0;
                    }
                }
            }
            else
            {
                // Not a comment, revert one character back
                ungetc(ch, file);
            }
        }
    }
}

// Function to save analysis results to a file
void saveToFile(char filename[], int charFrequency[], ReservedWordInfo reservedWords[], int totalReservedWords, int singleLineComments, int multiLineComments)
{
    const char *folder_name = "FrequenciesFiles";
    char outputFilename[MAX_FILENAME_LENGTH];
    // Create a new folder
    mkdir(folder_name);
    snprintf(outputFilename, sizeof(outputFilename), "%s/%s_freq.txt", folder_name, filename);
    FILE *outputFile = fopen(outputFilename, "w");

    if (!outputFile)
    {
        printf("Error opening output file!\n");
        return;
    }

    fprintf(outputFile, "Frequency Analysis of the %s program :\n\n", filename);
    // Save character frequency analysis to the file
    fprintf(outputFile, "Character Frequency Analysis:\n");
    for (int i = 32; i < 127; i++)
    {
        if (charFrequency[i] > 0)
        {
            fprintf(outputFile, "'%c': %d\n", i, charFrequency[i]);
        }
    }

    // Save reserved word frequency analysis to the file
    fprintf(outputFile, "\nReserved Word Frequency Analysis:\n");
    for (int i = 0; i < totalReservedWords; i++)
    {
        fprintf(outputFile, "%s: %d\n", reservedWords[i].word, reservedWords[i].frequency);
    }

    // Save comment analysis to the file
    fprintf(outputFile, "\nComment Analysis:\n");
    fprintf(outputFile, "Single-line comments: %d\n", singleLineComments);
    fprintf(outputFile, "Multi-line comments: %d\n", multiLineComments);

    fclose(outputFile);
}
int main()
{
    printf("*** Characters, Keywords, and Comments Frequency Analyzer ***\n\n");
    char filename[MAX_FILENAME_LENGTH];
    char filepath[MAX_FILEPATH_LENGTH];
    long unsigned int length;
    printf("Enter the Name of the File with its Extension = ");
    scanf("%s", filename);
    length = strlen(filename);
    if (((filename[length - 1]) != 'c') && ((filename[length - 1]) != 'C'))
    {
        printf("Only Files with Extension '.c' are Allowed!\n ");
        exit(1);
    }
    int choice;
    printf("Where does the File Exist ?\n");
    printf("1. In the same folder.\n");
    printf("2. I want to specify the filepath.\n");
    printf("Enter your choice = ");
    scanf("%d", &choice);
    FILE *file;
    switch (choice)
    {
    case 1:
        // Open the C file for reading
        file = fopen(filename, "r");
        break;
    case 2:
        printf("Enter the Path of the File with its Name = ");
        scanf("%s", filepath);
        // Open the C file for reading
        file = fopen(filepath, "r");
        break;
    default:
        printf("Invalid Choice !!!\n");
        file = NULL;
        exit(1);
        break;
    }

    if (!file)
    {
        printf("Error Opening File!\n");
        printf("Or\n");
        printf("Can't Found the File %s .\n", filename);
        exit(1);
    }

    // Initialize character frequency array
    int charFrequency[256] = {0};

    // Analyze characters in the C program
    analyzeCharacters(file, charFrequency);

    // Close and reopen the file to reset the file pointer
    fclose(file);
    file = fopen(filename, "r");

    // Initialize reserved word frequency array
    ReservedWordInfo reservedWords[sizeof(keywords) / sizeof(keywords[0])] = {0};
    int totalReservedWords = 0;

    // Analyze reserved words in the C program
    analyzeReservedWords(file, reservedWords, &totalReservedWords);

    // Close and reopen the file to reset the file pointer
    fclose(file);
    file = fopen(filename, "r");

    int singleLineComments = 0;
    int multiLineComments = 0;

    // Analyze comments in the C program
    analyzeComments(file, &singleLineComments, &multiLineComments);

    fclose(file);

    // Sort reserved words by frequency in descending order
    qsort(reservedWords, sizeof(reservedWords) / sizeof(reservedWords[0]), sizeof(reservedWords[0]), compareReservedWordInfo);

    // Display results for character frequency
    printf("Character Frequency Analysis:\n");
    for (int i = 32; i < 127; i++)
    {
        if (charFrequency[i] > 0)
        {
            printf("'%c': %d\n", i, charFrequency[i]);
        }
    }
    // Display results for reserved word frequency
    printf("\nReserved Word Frequency Analysis:\n");
    for (int i = 0; i < totalReservedWords; i++)
    {
        printf("%s: %d\n", reservedWords[i].word, reservedWords[i].frequency);
    }

    // Display results for comments
    printf("\nComment Analysis:\n");
    printf("Single-line comments: %d\n", singleLineComments);
    printf("Multi-line comments: %d\n\n", multiLineComments);
    // Prompt the user to save the information to a file
    char saveToFileChoice[3];
    printf("\nDo you want to save the information to a file? (y/n) or (yes/no): ");
    scanf("%s", saveToFileChoice);
    // Convert the user's input to lowercase
    toLowercase(saveToFileChoice);
    if (strcmp(saveToFileChoice, "y") == 0 || strcmp(saveToFileChoice, "yes") == 0)
    {
        // Save the information to a file
        saveToFile(filename, charFrequency, reservedWords, totalReservedWords, singleLineComments, multiLineComments);
        printf("\nInformation saved to FrequenciesFiles/%s_freq.txt\n\n", filename);
    }
    else if (strcmp(saveToFileChoice, "n") == 0 || strcmp(saveToFileChoice, "no") == 0)
    {
        printf("\nOk! Closing without saving in file.\n\n");
    }
    else
    {
        printf("\nInvalid Answer!!!\n\n");
    }
    return 0;
}
