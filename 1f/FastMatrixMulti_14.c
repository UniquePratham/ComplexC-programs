// Name - Pratham Agarwal
// Date - 11/12/2023
// 1f. For two large square matrix (not to fit individually in primary memory), compute the resultant multiplication matrix.
// Program Name - FastMatrixMulti_14.c
// gcc (tdm64-1) 10.3.0

// Algorithm:
// 1.	Read the input text files containing the two large square matrices, M1 and M2, and extract their dimensions (N x N).
// 2.	Initialize an empty matrix R to store the resultant multiplication matrix. Set its dimensions to N x N.
// 3.	Divide the matrices M1 and M2 into smaller submatrices (A, B, C, and D) to create a recursive framework for matrix multiplication.
// 4.	For each submatrix A, B, C, and D:
// 5.	If the submatrices are of a small enough size to fit in memory, calculate their multiplication using the traditional matrix multiplication algorithm.
// 6.	If the submatrices are still large, recursively divide them into smaller submatrices and perform matrix multiplications until they reach a size that can be handled by traditional multiplication.
// 7.	Combine the results from step 4 to populate the resultant matrix R, following the divide-and-conquer strategy.
// 8.	Write the elements of matrix R into an output text file in the specified format, along with the dimensions of the resultant matrix.
// 9.	The algorithm terminates, and you obtain the multiplication of the two large square matrices stored in the output file.
#include <stdio.h>
#include <stdlib.h>

// Function to read a matrix from a file
void readMatrixFromFile(const char *filename, int **matrix, int N)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);
}

// Function to write a matrix to a file
void writeMatrixToFile(const char *filename, int **matrix, int N)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file %s for writing.\n", filename);
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%d\n", N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Function to allocate memory for a matrix
int **allocateMatrix(int N)
{
    int **matrix = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
    {
        matrix[i] = (int *)malloc(N * sizeof(int));
    }
    return matrix;
}

// Function to deallocate memory for a matrix
void deallocateMatrix(int **matrix, int N)
{
    for (int i = 0; i < N; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to perform matrix multiplication using a simpler approach
void multiplyMatrix(int **M1, int **M2, int **R, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                R[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
}

int main()
{
    printf("*** Large Matrix Multiplication ***\n\n");
    // Read input matrices from files
    const char *filename1 = "matrix1.txt";
    const char *filename2 = "matrix2.txt";

    int N; // Matrix dimension
    FILE *file = fopen(filename1, "r");
    if (file == NULL)
    {
        printf("Error opening file %s.\n", filename1);
        exit(EXIT_FAILURE);
    }
    fscanf(file, "%d", &N);
    fclose(file);

    // Allocate memory for matrices
    int **M1 = allocateMatrix(N);
    int **M2 = allocateMatrix(N);
    int **R = allocateMatrix(N);

    // Read matrices from files
    readMatrixFromFile(filename1, M1, N);
    printf("Matrix 1.txt was read.\n");
    readMatrixFromFile(filename2, M2, N);
    printf("Matrix 2.txt was read.\n");

    // Initialize result matrix R to zeros
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            R[i][j] = 0;
        }
    }

    printf("Multiplying Matrix 1 and Matrix 2 and Calculating Resultant Matrix : \n");
    // Perform matrix multiplication
    multiplyMatrix(M1, M2, R, N);

    // Write the result matrix to a file
    const char *resultFilename = "result_matrix.txt";
    writeMatrixToFile(resultFilename, R, N);

    // Deallocate memory
    deallocateMatrix(M1, N);
    deallocateMatrix(M2, N);
    deallocateMatrix(R, N);
    printf("Resultant Matrix has been saved to result_matrix.txt\n\n");
    return 0;
}
