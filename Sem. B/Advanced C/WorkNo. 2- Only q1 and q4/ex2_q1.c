// Course: Advanced C programming
// exercise 2, question 1
// file name: ex2_q1.c

// --------------------------- //
//
//	Assigned by:
//		Student1_Full_Name #ID
//		Student2_Full_Name #ID
//
// --------------------------- //

// --------------------------------------- //
// Include and definition package section:
// --------------------------------------- //
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define scanf_s scanf
#define ROWS 4
#define COLS 4
// --------------------------------------- //
// Types declration section:
// --------------------------------------- //
typedef struct fraction
{
	int num, numerator, denominator;
} fraction;
// --------------------------------------- //
// Functions declration section:
// --------------------------------------- //

fraction** createMatrix(int rows, int cols);
fraction** matrixAverageNeighbor(int A[][COLS], int rows, int cols);
fraction neighborFractionAverage(int A[][COLS], int i, int j, int rows, int cols);
void printMatrix(fraction** B, int rows, int cols);
void freeMatrix(fraction** B, int rows);
/** DECLARE HERE ONE FUNCTION ACCORDING TO YOUR NEEDS **/
// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
	fraction** B;
	int A[ROWS][COLS] = {
		{5, 12, 6, 8},
		{4, 7, 0, 9},
		{13, 20, 8, 2},
		{18, 0, 2, 6}
	};

	// Start Program:
	printf("Start Program\n");

	// call functions:
	B = matrixAverageNeighbor(A, ROWS, COLS);

	// write output:
	printf("Output:\n");
	printMatrix(B, ROWS, COLS);

	// free matrix:
	freeMatrix(B, ROWS);

	return 0;
}
// --------------------------- //

/// <summary>
/// This code required one extra important function.
/// Think hard about what it should be.
/// </summary>
/// <params>You decide</params>
/// <returns>You decide</returns>

	// your code:

// --------------------------- //

/// <summary>
/// This function allocate a dynamic matrix from type fraction.
/// </summary>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>allocated empty matrix B from type fraction</returns>
fraction** createMatrix(int rows, int cols)
{
	int i;
	fraction** res = (fraction**)malloc(rows * sizeof(fraction*));
	if (res)
	{
		for (i = 0; i < rows; i++)
		{
			res[i] = (fraction*)malloc(cols * sizeof(fraction));
		}
	}
	return res;
}
// --------------------------- //

/// <summary>
/// The function receives a static matrix 
/// and for each cell in the matrix calculates 
/// the average of its neighbors.  
/// </summary>
/// <param>int A[][COLS] - the static matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>matrix B from type fraction</returns>
fraction** matrixAverageNeighbor(int A[][COLS], int rows, int cols)
{
	int i, j;
	fraction** res = createMatrix(rows, cols);

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			res[i][j] = neighborFractionAverage(A, i, j, rows, cols);
		}
	}
	return res;
}
// --------------------------- //

/// <summary>
/// The function receives a static matrix, and a cell value,
/// and calculates the average of its neighbors.  
/// </summary>
/// <param>int A[][COLS] - the static matrix</param>
/// <param>int i - the cell row number in matrix</param>
/// <param>int j - the cell colum number in the matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>value from type fraction</returns>
fraction neighborFractionAverage(int A[][COLS], int i, int j, int rows, int cols)
{
	int numNeighbors = 0;
	int sumNumerator = 0;
	int sumDenominator = 0;
	int gcd = 1;
	int counter = 1;
	double num;
	fraction result = { 0, 0, 1 }; // Initialize result to 0

	// Check for a neighbor above
	if (i - 1 >= 0)
	{
		sumNumerator += A[i - 1][j];
		sumDenominator++;
	}
	// Check for neighbor below
	if (i + 1 < rows)
	{
		sumNumerator += A[i + 1][j];
		sumDenominator += 1; 
	}
	// Check for neighbor to the left
	if (j - 1 >= 0)
	{
		sumNumerator += A[i][j - 1];
		sumDenominator++;
	}
	// Check for neighbor to the right
	if (j + 1 < cols) {
		sumNumerator += A[i][j + 1];
		sumDenominator += 1; 
	}

	// Check for upper-right neighbor
	if (i - 1 >= 0 && j + 1 < cols) // Fixed typo
	{
		sumNumerator += A[i - 1][j + 1];
		sumDenominator++;
	}
	// Check for upper-left neighbor
	if (i - 1 >= 0 && j - 1 >= 0)
	{
		sumNumerator += A[i - 1][j - 1];
		sumDenominator++;
	}
	// Check for bottom-right neighbor
	if (i + 1 < rows && j + 1 < cols)
	{
		sumNumerator += A[i + 1][j + 1];
		sumDenominator++;
	}
	// Check for bottom-left neighbor
	if (i + 1 < rows && j - 1 >= 0)
	{
		sumNumerator += A[i + 1][j - 1];
		sumDenominator++;
	}
	// Find GCD to reduce fraction
	for (int i = 2; i <= sumNumerator && i <= sumDenominator; i++)
	{
		if (sumNumerator % i == 0 && sumDenominator % i == 0)
		{
			counter = 1; // Reset counter to 1
			gcd = i;
			while (sumDenominator% sumNumerator==0)
			{
				counter++;
				sumNumerator /= i;
				sumDenominator /= i;
			}
		}
	}

	// Assign numerator, denominator and result values
	if (sumDenominator == 1)
	{
		result.num = sumNumerator-1;
		result.denominator = 1;
		result.numerator = 0;// according to the requirement
	}
	else
	{
		result.num = (sumNumerator / gcd) / (sumDenominator / gcd);
		result.denominator = sumDenominator / gcd;
		result.numerator = (sumNumerator / gcd) - (result.num * result.denominator);
	}
	

	return result;

}
// --------------------------- //


/// <summary>
/// The function receives a dynamic matrix from type fraction,
/// and print the matrix as double varibles.  
/// </summary>
/// <param>fraction** B - the dynamic matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>None</returns>
void printMatrix(fraction** B, int rows, int cols)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) 
		{
			printf("%.2lf\t", (double)((B[i][j].num * B[i][j].denominator) + B[i][j].numerator) / B[i][j].denominator);
		}
		printf("\n");
	}
}
// --------------------------- //


/// <summary>
/// The function receives a dynamic matrix from type fraction,
/// and free all allocated memory.  
/// </summary>
/// <param>fraction** B - the dynamic matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <returns>None</returns>
void freeMatrix(fraction** B, int rows)
{
	for (int i = 0; i < rows; i++) {
		free(B[i]);
	}
	free(B);
	printf("free Matrix");
}
// --------------------------- //
