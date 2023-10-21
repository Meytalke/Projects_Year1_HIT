// Course: Advanced C programming
// exercise 1, question 1
// file name: ex1_q1.c
#define _CRT_SECURE_NO_WARNINGS
// --------------------------- //
// include package section:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// function declarations section:
int* scanArray(int*);
void printArray(int*, int);
int arrangeArray(int**, int);

// --------------------------- //

// main section:
// DO NOT CHANGE the following function:
int main()
{
	int* arr, n, k;

	// Start Program:
	printf("Start Program\n");

	// call functions:
	arr = scanArray(&n);
	k = arrangeArray(&arr, n);

	// write output:
	printf("Output:\n");
	printf("Size of k: %d\n", k);
	printf("Sorted array:\n");
	printArray(arr, n);
	free(arr);

	return 0;
}
// --------------------------- //


// DO NOT CHANGE the following function:
int* scanArray(int* n)
{
	int i;
	int* arr;

	printf("Enter array size: ");
	scanf("%d", n);

	arr = (int*)malloc(sizeof(int) * (*n));
	for (i = 0; i < *n; ++i)
	{
		printf("Enter value #%d: ", i + 1);
		scanf("%d", arr + i);

	}

	return arr;
}
// --------------------------- //


// DO NOT CHANGE the following function:
void printArray(int* arr, int n)
{
	int i;
	printf("{");
	for (i = 0; i < n; ++i)
		printf("%d%s", arr[i], i == n - 1 ? "" : ", ");
	printf("}\n");
}
// --------------------------- //

/// <summary>
/// Combine the two groups using realloc and memcpy only. 
/// </summary>
/// <param>int **arr - Address of the array pointer</param>
/// <param>int n - Size of the array</param>
/// <returns>Size of the first group</returns>
int arrangeArray(int** arr, int n)
{
	int i, loc = 0;
	int* newarr = NULL;
	for (i = 1; i < n; i++)
	{
		if ((*arr)[i] < (*arr)[0])
		{
			// found start of second array
			loc = i;
			break;
		}
	}
	newarr = (int*)realloc((*arr), (n + loc) * sizeof(int)); // allocates array of size n + size of first array
	if (newarr) 
	{
		*arr = newarr;
		newarr = NULL;
		memcpy(*arr + n, *arr, loc * sizeof(int)); // copy first array to end of original array
		memcpy(*arr, *arr + loc, n * sizeof(int)); // copy correct array to start
		newarr = (int*)realloc((*arr), n * sizeof(int)); // resizes array to correct (smaller) size
		if (newarr == NULL)
		{
			printf("Memory allocation failed\n");
			return -1;
		}
		else
		{
			*arr = newarr;
			newarr = NULL;
		}
	}
	else
	{
		printf("Memory allocation failed\n");
		return -1;
	}
	return loc;
}
// --------------------------- //
