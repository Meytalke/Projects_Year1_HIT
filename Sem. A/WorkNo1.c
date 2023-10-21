#define _CRT_SECURE_NO_WARNINGS
#define N 3

/*Libraries*/
#include <stdio.h>
#include <math.h>

/*
	Assigned by:
*/

/* Function declarations */

void Ex1();
void Ex2();
void Ex3();

/* Declarations of other sub-functions */

int sumDigits(int);
int checkID(int);
int sumLongestArithmeticList(int);
int numberLength(int);
int rotateNumber(int, int);

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
				printf("please select 0-%d : ", N);
				scanf("%d", &select);
			} while ((select < 0) || (select > N));
			switch (select)
			{
			case 1: Ex1(); break;
			case 2: Ex2(); break;
			case 3: Ex3(); break;
			}
		} while (all_Ex_in_loop && select);
		return 0;
}


/* Function definitions */

void Ex1() {
	int id = 0, answer = 0;
	printf("please enter your id: ");
	scanf("%d", &id);
	answer = checkID(id);
	if (answer) {
		printf("Your id is a correct id.\n");
	}
	else {
		printf("Your id is incorrent.\n");
	}

}

void Ex2() {
	int size = 0, answer = 0;
	printf("please enter the arithmetic list size: ");
	scanf("%d", &size);
	answer = sumLongestArithmeticList(size);
	printf("The sum of the longest sequence arithmetic list is: %d.\n", answer);
}

void Ex3() {
	int number = 0, spins = 0, answer = 0;
	printf("please enter the number and the amount of spins: ");
	scanf("%d%d", &number, &spins);
	answer = rotateNumber(number, spins);
	printf("The number %d after %d spins is: %d.\n", number, spins, answer);
}

/* Sub-Function definitions */

int sumDigits(int num)
	{
		int sum = 0;
		while (num > 0)
		{
			sum += num % 10;
			num = num / 10; //Sgorten the number
		}
		return sum;
	}



int checkID(int id)
{
	int sum = 0;
	if (id == 0 && id <= 9) //For ID between 0 to 9 the cuse return 0
	{
		return 0;
	}
	else
	{
		while (id > 0)
		{
			sum += sumDigits(id % 10);//Summing the multiplying a number by 1
			id = id / 10;//Shorten the ID
			sum += sumDigits(id % 10 * 2);//Summing the multiplying a number by 2
			id = id / 10;
		}
		if (sum % 10 == 0)//Check for valid ID
		{
			return 1;
		}
		else if (sum % 10 != 0)//Check for Invalid ID
		{
			return 0;
		}
	}
}

int sumLongestArithmeticList(int n) 
{
	int num1, num2, num3, maxQtyOnsequence = 2, currQtyOnsequence = 1, currsum = 0, maxSum = 0;
	if (n == 0)
	{
		return maxSum;
	}
	printf("Enter a number 1: ");
	scanf("%d", &num1);
	currsum += num1;
	maxSum += num1;
	if (n == 1)//For case of n==1
	{
		return maxSum;
	}
	printf("Enter a number 2: ");
	scanf("%d", &num2);
	maxSum += num2;
	currsum += num2;
	if (n == 2)//For case of n==2
	{
		return maxSum;
	}
	int d = num2 - num1;//difference
	currQtyOnsequence++;
	for (int pos = 3; pos <= n; pos++)
	{
		printf("Enter a number %d: ", pos);
		scanf("%d", &num3);
		if (num3 - num2 == d)
		{
			currsum += num3;
			currQtyOnsequence++;
		}
		else if (num3 - num2 != d)//When the d is not like what was before
		{
			currQtyOnsequence = 2;
			currsum = num2 + num3;
			d = num3 - num2;
		}
		if (currQtyOnsequence >= maxQtyOnsequence)//Onlt to cases of the currQtyOnsequence is bigger from the maxQtyOnsequence or the currQtyOnsequence is equals to the maxQtyOnsequence or the 
		{
			if (currQtyOnsequence > maxQtyOnsequence || (currQtyOnsequence == maxQtyOnsequence && currsum > maxSum))//if the currQtyOnsequence is bigger from the maxQtyOnsequence or currQtyOnsequence is equals to maxQtyOnsequence and currsum bigger maxSum so maxSum equals to currsum
				maxSum = currsum;
			maxQtyOnsequence = currQtyOnsequence;
		}
		num2 = num3;
	}

	return maxSum;
}
int numberLength(int num)
{
	int count = 0;
	while (num > 0)
	{
		count++;
		num = num / 10;
	}
	return count;
}
int rotateNumber(int num, int spins)
{
	int numberLength1 = numberLength(num);//Using with numberLength to know what the number Length of the num
	int n = num, m, m1 = numberLength1 - 1;
	if (spins % numberLength1 == 0)//if the spins % numberLength1 ==0 its mean that the number repeats itself
	{
		return num;
	}
	else
	{
		while (spins != 0)
		{
			m = (num % 10) * pow(10, m1);// remainder of a number * 10^(numberLength1-1)
			num = m + (num / 10);
			spins--;
		}
		return num;
	}
}

/* ------------------- */