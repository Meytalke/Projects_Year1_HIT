#define _CRT_SECURE_NO_WARNINGS
#define N 4

/*Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/* Function declarations */

void Ex1();
void Ex2();
void Ex31();
void Ex32();
void Ex4();

/* Declarations of other sub-functions */
void swap(int* v, int* u)
{
	int temp = *v;
	*v = *u;
	*u = temp;
}
void merge(int* a, int p, int q, int r)
{
	int i = p, j = q + 1, k = 0;
	int* temp = (int*)malloc((r - p + 1) * sizeof(int));
	assert(temp);
	while ((i <= q) && (j <= r))
		if (a[i] < a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	while (j <= r)
		temp[k++] = a[j++];
	while (i <= q)
		temp[k++] = a[i++];
	/* copy temp[] to a[]   */
	for (i = p, k = 0; i <= r; i++, k++)
		a[i] = temp[k];
	free(temp);
}
void merge_sort(int* a, int first, int last)
{
	int middle;
	if (first < last) {
		middle = (first + last) / 2;
		merge_sort(a, first, middle);
		merge_sort(a, middle + 1, last);
		merge(a, first, middle, last);
	}
}
int* input_array(int);
int areReversed(int*, int*, int);
int findCommonDigit(unsigned long long, unsigned long long);
int moveDuplicatesV1(int*, int);
int moveDuplicatesV2(int*, int);
int validateArray(int*, int);

/* ------------------------------- */

int main()
{
	int select = 0, i, all_Ex_in_loop = 0;
	printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
	if (scanf("%d", &all_Ex_in_loop) == 1)
		do
		{
			for (i = 1; i <= N; i++)
				printf("Ex%d--->%d\n", i, i);
			printf("EXIT-->0\n");
			do {
				select = 0;
				printf("please select 0-%d : \n", N);
				scanf("%d", &select);
			} while ((select < 0) || (select > N));
			switch (select)
			{
			case 1: Ex1(); break;
			case 2: Ex2(); break;
			case 3: do {
				select = 0;
				printf("Ex31--->1\n");
				printf("Ex32--->2\n");
				printf("please select 1-2 : \n");
				scanf("%d", &select);
			} while ((select < 1) || (select > 2));
			switch (select)
			{
			case 1: Ex31(); break;
			case 2: Ex32(); break;
			};
			break;
			case 4: Ex4(); break;
			}
		} while (all_Ex_in_loop && select);
		return 0;
}


/* Function definitions */

void Ex1() {
	int n = 0;
	int* A, * B;
	printf("please enter the size of arrays: \n");
	scanf("%d", &n);
	printf("please enter elements of the first array: \n");
	A = input_array(n);
	printf("please enter elements of the second array: \n");
	B = input_array(n);
	areReversed(A, B, n) ? printf("Arrays are the opposite to one another.\n") : printf("Arrays are not the opposite to one another.\n");
	free(A); free(B);
}

void Ex2() {
	unsigned long long n1, n2;
	int answer = -2;
	printf("please enter two integers (64 bits) sorted in ascending order to find a common digit\n: ");
	scanf("%llu%llu", &n1, &n2);
	answer = findCommonDigit(n1, n2);
	switch (answer)
	{
	case -2: printf("Error in function.\n"); break;
	case -1: printf("%llu and %llu has no common digit.\n", n1, n2); break;
	default: printf("%llu and %llu common digit from right is: %d\n", n1, n2, answer); break;
	}
}

void Ex31() {
	int n = 0, i, answer = 0;
	int* A;
	printf("please enter the size of array: \n");
	scanf("%d", &n);
	printf("please enter elements of the array ranging from -%d to %d: \n", n, n);
	A = input_array(n);
	printf("Array before moving duplications: \n");
	for (i = 0; i < n; i++) { printf("%d ", A[i]); }
	printf("\nArray after moving duplications: \n");
	answer = moveDuplicatesV1(A, n);
	for (i = 0; i < n; i++) { printf("%d ", A[i]); }
	printf("\nThe number of different elements in array: %d.\n", answer);
	free(A);
}

void Ex32() {
	int n = 0, i, answer = 0;
	int* A;
	printf("please enter the size of array: \n");
	scanf("%d", &n);
	printf("please enter elements of the array: \n");
	A = input_array(n);
	printf("Array before moving duplications: \n");
	for (i = 0; i < n; i++) { printf("%d ", A[i]); }
	printf("\nArray after moving duplications: \n");
	answer = moveDuplicatesV2(A, n);
	for (i = 0; i < n; i++) { printf("%d ", A[i]); }
	printf("\nThe number of different elements in array: %d.\n", answer);
	free(A);

}

void Ex4() {
	int n = 0;
	int* A;
	printf("please enter the size of array: \n");
	scanf("%d", &n);
	printf("please enter elements of the array: \n");
	A = input_array(n);
	validateArray(A, n) ? printf("Array contains all numbers from 0 to %d.\n", n - 1) : printf("Array doesn't contain all numbers from 0 to %d.\n", n - 1);
	free(A);
}

/* Sub-Function definitions */

int* input_array(int n) {
	int i;
	int* A = (int*)malloc(n * sizeof(int));
	assert(A);
	printf("Enter %d integers\n", n);
	for (i = 0; i < n; i++) {
		scanf("%d", A + i);
	}
	return A;
}



int areReversed(int* A, int* B, int n) 
	{
		if (n == 0)
		{
			return 1;
		}
		if (A[0] != B[n - 1])
		{
			return 0;
		}
		return areReversed(A + 1, B, n - 1);
	}

int findCommonDigit(unsigned long long n1, unsigned long long n2) 
{
	if (n1 == 0 || n2 == 0)
	{
		return -1;
	}
	int DigitOfn1 = n1 % 10;
	int DigitOfn2 = n2 % 10;
	if (DigitOfn1 == DigitOfn2)
	{
		return DigitOfn1;
	}
	else if (DigitOfn1 < DigitOfn2) {
		return findCommonDigit(n1, n2 / 10);
	}
	else
		return findCommonDigit(n1 / 10, n2);
}

int moveDuplicatesV1(int* arr, int n) 
{
	int* monim = (int*)calloc((n + n + 1), sizeof(int));
	assert(monim);

	int cnt = 0, j = 0;

	for (int i = 0; i < n; i++)
	{
		if (monim[arr[i] + n] == 0) {
			monim[arr[i] + n]++;
			cnt++;
		}
		else {
			while (j < n) {
				if (monim[arr[j] + n] != 0) {
					j++;
				}
				else {
					monim[arr[j] + n]++;
					cnt++;
					// swap
					swap(&arr[i], &arr[j]);
					j++;
					break;
				}
			}
			if (j == n) {
				break;
			}

		}
	}
	free(monim);
	return cnt;
}
int abs(int n) {
	if (n < 0)
		return -1 * n;
	return n;
}

int absBin(int* a, int n, int key) {
	int l = 0, r = n - 1, mid;
	while (l <= r)
	{
		mid = (l + r) / 2;
		if (key == abs(a[mid]))
		{
			if (a[mid] <= 0) {
				return -1;
			}
			else {
				a[mid] *= -1;
				return 1;
			}
		}
		else if (key > abs(a[mid]))
		{
			l = mid + 1;
		}
		else if (key < abs(a[mid]))
		{
			r = mid - 1;
		}
	}
	return 0;
}

int moveDuplicatesV2(int* arr, int n) 
{
	int* aux = (int*)malloc(n * sizeof(int));
	assert(aux);
	for (int i = 0; i < n; i++) { aux[i] = arr[i]; }
	merge_sort(aux, 0, n - 1);

	int cnt = 0, j = 0;

	for (int i = 0; i < n; i++)
	{
		if (absBin(aux, n, arr[i]) > 0) {
			cnt++;
			continue;
		}
		else {
			while (j < n) {
				if (absBin(aux, n, arr[j]) < 0) {
					j++;
					continue;
				}
				else {
					cnt++;
					// swap
					swap(&arr[i], &arr[j]);
					j++;
					break;
				}
			}
			if (j == n) {
				break;
			}

		}
	}
	free(aux);
	return cnt;
}

int validateArray(int* arr, int n) 
{
	if (arr == NULL || n <= 0)
	{
		return 0;
	}
	int tmp;
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] < 0 || arr[i] >= n)
		{
			return 0;
		}
		if (arr[i] == i)
		{
			continue;
		}
		else {
			while (arr[i] != i) {
				tmp = arr[i];
				arr[i] = arr[tmp];
				arr[tmp] = tmp;
				cnt++;
				if (cnt > n)
					return 0;
			}
		}
	}
	return 1;
}

/* ------------------- */