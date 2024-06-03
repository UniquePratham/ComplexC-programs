// Name - Pratham Agarwal
// Date - 11/12/2023
// 1d. Take a sufficiently long arithmetic expression with +,-,/,^ operators including parenthesis. Evaluate the expression
// Program Name - Simplifier_14.c
// gcc (tdm64-1) 10.3.0

// Algorithm:
// 1.	Retrieve the arithmetic expression from the input text file.
// 2.	Analyse the expression to identify its key components, which include numbers, operators, and parenthesis. This step breaks down the expression into manageable parts for accurate evaluation.
// 3.	Follow the order of operations strictly. This means we prioritize operations within parenthesis, ensuring they are calculated first, followed by exponentiation, then multiplication and division (from left to right), and finally, addition and subtraction (from left to right). Adhering to this order maintains the correct sequence of calculations.
// 4.	Methodically evaluate the expression step by step, focusing on one operation at a time. By taking this meticulous approach, we ensure that each mathematical operation is executed accurately and in the proper sequence, leaving no room for computational errors.
// 5.	Repeat the above steps for each expression in the input file, ensuring a consistent and precise evaluation process for all expressions.
// 6.	Document both the input expression and its corresponding result in the output text file, preserving the original order, providing a clear and systematic record of the calculations performed.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Function to perform basic arithmetic operations
double operate(double operand1, char operator, double operand2)
{
    switch (operator)
    {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        if (operand2 != 0)
        {
            return operand1 / operand2;
        }
        else
        {
            printf("Error: Division by zero\n");
            exit(EXIT_FAILURE);
        }
    case '^':
        return pow(operand1, operand2);
    default:
        printf("Error: Invalid operator\n");
        exit(EXIT_FAILURE);
    }
}

// Function to check if a character is an operator
int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

double evaluateExpression(const char *expression)
{
    int len = strlen(expression);
    double stackOperand[len];
    char stackOperator[len];
    int stackOperandIndex = -1;  // Stack index for operand initialization
    int stackOperatorIndex = -1; // Stack index for operator initialization
    int parenthesisCount = 0;
    for (int i = 0; i < len; ++i)
    {
        // If the current character is a digit or decimal point
        if (isdigit(expression[i]) || (expression[i] == '.' && isdigit(expression[i + 1])))
        {
            if (stackOperator[stackOperatorIndex] == '*' || stackOperator[stackOperatorIndex] == '/' || stackOperator[stackOperatorIndex] == '^')
            {
                stackOperand[++stackOperandIndex] = strtod(expression + i, NULL);
                while (isdigit(expression[i]) || expression[i] == '.')
                {
                    ++i;
                }
                --i;
                // Perform the operation and push the result back to the stackOperand
                double operand2 = stackOperand[stackOperandIndex--];
                double operand1 = stackOperand[stackOperandIndex--];
                char operator= stackOperator[stackOperatorIndex--];
                stackOperand[++stackOperandIndex] = operate(operand1, operator, operand2);
            }
            else
            {
                stackOperand[++stackOperandIndex] = strtod(expression + i, NULL);
                while (isdigit(expression[i]) || expression[i] == '.')
                {
                    ++i;
                }
                --i;
            }
        }
        else if (isOperator(expression[i]))
        {
            // If the current character is an operator
            if (stackOperandIndex < 0)
            {
                printf("Error: Invalid expression - 1\n");
                exit(EXIT_FAILURE);
            }
            else
            {
                stackOperator[++stackOperatorIndex] = expression[i];
            }
        }
        else if (expression[i] == '(')
        {
            stackOperator[++stackOperatorIndex] = expression[i];
            // If the current character is an opening parenthesis
            parenthesisCount++;
        }
        else if (expression[i] == ')')
        {
            // If the current character is a closing parenthesis
            if (parenthesisCount == 0)
            {
                printf("Error: Mismatched parenthesis\n");
                exit(EXIT_FAILURE);
            }
            else if (stackOperator[stackOperatorIndex] == '(' && stackOperandIndex == 0 && isdigit(stackOperand[stackOperandIndex]))
            {
                stackOperatorIndex--;
                parenthesisCount--;
            }
            else
            {
            repeat:
                if (stackOperator[stackOperatorIndex] == '(')
                {
                    // Discard the opening parenthesis from the stackOperator
                    stackOperatorIndex--;
                    parenthesisCount--;
                    if ((stackOperator[stackOperatorIndex] == '*' || stackOperator[stackOperatorIndex] == '/' || stackOperator[stackOperatorIndex] == '^') && expression[0] != '(')
                    {
                        // Perform the operation and push the result back to the stackOperand
                        double operand2 = stackOperand[stackOperandIndex--];
                        double operand1 = stackOperand[stackOperandIndex--];
                        char operator= stackOperator[stackOperatorIndex--];
                        stackOperand[++stackOperandIndex] = operate(operand1, operator, operand2);
                    }
                }

                else
                {
                    // Perform the operation inside the parenthesis
                    double operand2 = stackOperand[stackOperandIndex--];
                    char operator= stackOperator[stackOperatorIndex--];
                    double operand1 = stackOperand[stackOperandIndex--];
                    stackOperand[++stackOperandIndex] = operate(operand1, operator, operand2);
                    goto repeat;
                }
            }
        }
    }

    // Perform any remaining operations
    while (stackOperatorIndex != -1 && stackOperandIndex >= 1 && parenthesisCount == 0)
    {
        double operand2 = stackOperand[stackOperandIndex--];
        char operator=(char) stackOperator[stackOperatorIndex--];
        double operand1 = stackOperand[stackOperandIndex--];
        stackOperand[++stackOperandIndex] = operate(operand1, operator, operand2);
    }

    if (stackOperandIndex != 0)
    {
        printf("Error: Invalid expression - 2\n");
        exit(EXIT_FAILURE);
    }
    return stackOperand[0];
}

int main()
{
    FILE *inputFile, *outputFile;
    char expression[100];

    // Open input and output files
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL)
    {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL)
    {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    printf("*** Simplifier ***\n\n");

    fprintf(outputFile, "Simplified Expression by Simplifier: \n\n");
    // Process each expression in the input file
    while (fscanf(inputFile, "%99[^\n]\n", expression) == 1)
    {
        // Evaluate the expression
        double result = evaluateExpression(expression);

        // Display the expression and result and also print it to the output file
        printf("%s = %.2f\n", expression, result);
        fprintf(outputFile, "%s = %.2f\n", expression, result);
    }
    printf("\nExpressions has been saved to output file...\n\n");
    // Close files
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
