// Course: Advanced C programming
// exercise 1, question 3
// file name: ex1_q3.c
#define _CRT_SECURE_NO_WARNINGS
// --------------------------- //
// include package section:
#include <stdio.h>
#include <stdlib.h>


// structs and function declarations section:
typedef struct rectangle {
	int xTopSmall;
	int yTopSmall;
	int xButtomRight;
	int yButtomRight;
}rectangle;

typedef struct recElement {
	rectangle Rect;
	struct recElement* next;
}recElement;

int validateRectangle(rectangle* rec);
rectangle scanRectangle();
recElement* createElement();
recElement* createRectList();
rectangle findSmallest(recElement* head);
void printRectangle(rectangle* rec);
void printList(recElement* head);
void freeList(recElement* head);

// --------------------------- //

int main()
{
	rectangle rec;
	recElement* head = NULL;

	// Start Program:
	printf("Start Program\n");

	// call functions:
	head = createRectList();

	printf("\n\nRectangle list:\n");
	printList(head);

	rec = findSmallest(head);

	printf("\n\nFilling rectangle:\n");
	printRectangle(&rec);

	freeList(head);
	head = NULL;

	printf("\n\n");

	return 0;
}
// --------------------------- //


/// <summary>
/// Function gets an address of a rectangle and check validity.
/// </summary>
/// <param>Address of rectangle</param>
/// <returns>0- if rectangle is not valid, 1-if rectangle is a valid, 2-if rectangle is a point</returns>
int validateRectangle(rectangle* rec)
{
	if (rec->xTopSmall == rec->xButtomRight && rec->yTopSmall == rec->yButtomRight) //detects point input
	{
		return 2;
	}
	if (rec->xTopSmall < rec->xButtomRight && rec->yTopSmall > rec->yButtomRight) // correct input
	{
		return 1;
	}
	else
	{
		// incorrect input - prints messages accordingly
		printf("%s", rec->xButtomRight < rec->xTopSmall ? "\n**Bottom right has a smaller x value then top left**" : "");
		printf("%s", rec->yButtomRight > rec->yTopSmall ? "\n**Top left has a smaller y value then bottom right**" : "");
		if ((rec->xTopSmall == rec->xButtomRight && rec->yTopSmall != rec->yButtomRight)
			|| (rec->xTopSmall != rec->xButtomRight && rec->yTopSmall == rec->yButtomRight))
		{
			printf("\n**You entered a line**\n");
		}
		printf("\nplease enter correct coordinates, or a point to end input requests:\n");
		return 0;
	}
}
// --------------------------- //



/// <summary>
/// Function scan a rectangle in the plane,
/// Used as auxiliary function for createElement.
/// </summary>
/// <param>None</param>
/// <returns>a newly scanned rectangle</returns>
rectangle scanRectangle()
{
	// your code:
	rectangle rec;
	printf("New rectangle: \n");
	do {
		printf("please enter the x top small: ");
		scanf("%d", &rec.xTopSmall);
		printf("please enter the y top small: ");
		scanf("%d", &rec.yTopSmall);
		printf("please enter the x Buttom Right: ");
		scanf("%d", &rec.xButtomRight);
		printf("please enter the y Buttom Right: ");
		scanf("%d", &rec.yButtomRight);
	} while (validateRectangle(&rec) == 0);
	return rec;
}
// --------------------------- //


/// <summary>
/// Function allocate a new recElement.
/// Calls scanRectangle during the process. 
/// if the scanned rectangle is a point, returns NULL.
/// </summary>
/// <returns>New allocated recElement or NULL if rectangle is a point</returns>
recElement* createElement()
{
	rectangle rec = scanRectangle();
	if (validateRectangle(&rec) == 2) 
	{
		return NULL;
	}

	recElement* recPtr = (recElement*)malloc(sizeof(recElement));
	recPtr->Rect = rec;
	recPtr->next = NULL;

	return recPtr;
}
// --------------------------- //


/// <summary>
/// Function creates a list of rectangles.
/// Calls function createElement in a loop.
/// Scan stops when createElement returns null.
/// </summary>
/// <param>None</param>
/// <returns>The Euclidean distance between p1 and p2</returns>
recElement* createRectList()
{
	// your code:
	recElement* head = createElement();
	if (head == NULL)
	{
		return NULL;
	}

	recElement* prev = head, * curr = NULL;
	do {
		curr = createElement();
		prev->next = curr;
		prev = curr;
	} while (curr != NULL); 

	return head;
}
// --------------------------- //


/// <summary>
/// Function gets a list and returns the filling rectangle
/// </summary>
/// <param>recElement* head - the list of rectangles</param>
/// <returns>The filling rectangle. if the list is empty return rectangle with (0,0,0,0)</returns>
rectangle findSmallest(recElement* head)
{
	// your code:
	rectangle result;
	int minxTopSmall, maxyTopSmall, maxxButtonRight, minyButtonRight;
	recElement* pRec = head;
	if (head == NULL)
	{
		rectangle rec = { 0,0,0,0 };
		return rec;
	}
	minxTopSmall = head->Rect.xTopSmall;
	maxyTopSmall = head->Rect.yTopSmall;
	maxxButtonRight = head->Rect.xButtomRight;
	minyButtonRight = head->Rect.yButtomRight;
	pRec = pRec->next;
	while (pRec != NULL)
	{
		// finds correct coordinates for filling rectangle
		if (pRec->Rect.xTopSmall < minxTopSmall)
		{
			minxTopSmall = pRec->Rect.xTopSmall;
		}
		if (pRec->Rect.yTopSmall > maxyTopSmall)
		{
			maxyTopSmall = pRec->Rect.yTopSmall;
		}
		if (pRec->Rect.xButtomRight > maxxButtonRight)
		{
			maxxButtonRight = pRec->Rect.xButtomRight;
		}
		if (pRec->Rect.yButtomRight < minyButtonRight)
		{
			minyButtonRight = pRec->Rect.yButtomRight;
		}
		pRec = pRec->next;
	}
	result.xTopSmall = minxTopSmall;
	result.yTopSmall = maxyTopSmall;
	result.xButtomRight = maxxButtonRight;
	result.yButtomRight = minyButtonRight;
	return result;
}
// --------------------------- //


/// <summary>
/// Function print rectangle cordinates on screen. (not drawing the rectangle!)
/// </summary>
/// <param>rectangle* rec - pointer to rectangle</param>
/// <returns>None</returns>
void printRectangle(rectangle* rec)
{
	printf("[(%d,%d)(%d,%d)]", rec->xTopSmall, rec->yTopSmall, rec->xButtomRight, rec->yButtomRight);
}
// --------------------------- //


/// <summary>
/// Function print list on screen.
/// </summary>
/// <param>recElement* head - list address</param>
/// <returns>None</returns>
void printList(recElement* head)
{
	// your code:
	recElement* curr = head;
	while (curr != NULL) 
	{
		printRectangle(&(curr->Rect));
		printf("-->");
		curr = curr->next;
	}
	printf("NULL");
}
// --------------------------- //


/// <summary>
/// Function free alocated memory of list 
/// </summary>
/// <param>recElement* head - pointer to head of the list</param>
/// <returns>None</returns>
void freeList(recElement* head)
{
	// your code:
	recElement* prev, * curr = head;
	while (curr != NULL) 
	{
		prev = curr;
		curr = curr->next;
		free(prev);
		prev = NULL;
	}
}
// --------------------------- //
