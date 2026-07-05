/*
 * Matrix Operations Calculator
 * A console-based C program for performing matrix addition, multiplication,
 * and transpose on user-defined matrices.
 *
 * Compile: gcc MatrixOperations.c -o MatrixOperations
 * Run:     ./MatrixOperations
 */

#include <stdio.h>

#define MAX 10

void inputMatrix(int mat[MAX][MAX], int rows, int cols, const char *label) {
    printf("Enter elements for matrix %s (%d x %d):\n", label, rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("  [%d][%d]: ", i, j);
            scanf("%d", &mat[i][j]);
        }
    }
}

void printMatrix(int mat[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%6d", mat[i][j]);
        }
        printf("\n");
    }
}

void addMatrices(int a[MAX][MAX], int b[MAX][MAX], int result[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[i][j] = a[i][j] + b[i][j];
}

void multiplyMatrices(int a[MAX][MAX], int b[MAX][MAX], int result[MAX][MAX],
                       int rowsA, int colsA, int colsB) {
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0;
            for (int k = 0; k < colsA; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void transposeMatrix(int mat[MAX][MAX], int result[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[j][i] = mat[i][j];
}

int main() {
    int choice;
    int a[MAX][MAX], b[MAX][MAX], result[MAX][MAX];
    int rowsA, colsA, rowsB, colsB;

    printf("===== MATRIX OPERATIONS CALCULATOR =====\n");
    printf("1. Add two matrices\n");
    printf("2. Multiply two matrices\n");
    printf("3. Transpose a matrix\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter rows and columns (both matrices must match): ");
            scanf("%d %d", &rowsA, &colsA);
            inputMatrix(a, rowsA, colsA, "A");
            inputMatrix(b, rowsA, colsA, "B");
            addMatrices(a, b, result, rowsA, colsA);
            printf("\nResult (A + B):\n");
            printMatrix(result, rowsA, colsA);
            break;

        case 2:
            printf("Enter rows and columns of matrix A: ");
            scanf("%d %d", &rowsA, &colsA);
            printf("Enter rows and columns of matrix B: ");
            scanf("%d %d", &rowsB, &colsB);

            if (colsA != rowsB) {
                printf("Error: columns of A must equal rows of B for multiplication.\n");
                return 1;
            }

            inputMatrix(a, rowsA, colsA, "A");
            inputMatrix(b, rowsB, colsB, "B");
            multiplyMatrices(a, b, result, rowsA, colsA, colsB);
            printf("\nResult (A x B):\n");
            printMatrix(result, rowsA, colsB);
            break;

        case 3:
            printf("Enter rows and columns of the matrix: ");
            scanf("%d %d", &rowsA, &colsA);
            inputMatrix(a, rowsA, colsA, "A");
            transposeMatrix(a, result, rowsA, colsA);
            printf("\nTransposed Matrix:\n");
            printMatrix(result, colsA, rowsA);
            break;

        default:
            printf("Invalid option.\n");
            return 1;
    }

    return 0;
}
