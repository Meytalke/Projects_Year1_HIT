// Course: Advanced C programming
// exercise 1, question 2
// file name: ex1_q2.c
#define _CRT_SECURE_NO_WARNINGS
// --------------------------- //
// include package section:
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// --------------------------- //
//
//	Assigned by:
//		Noam_Seifer_300406964
//		Meytal_Keren _322710534
//
// --------------------------- //

// structs and function declarations section:
typedef struct point
{
	int x, y;
}point;

typedef struct polygon
{
	int n;
	point* points;
	double scope;
}polygon;

void scanPoint(point* p);
polygon* createPolygon();
double distance(point* p1, point* p2);
double calculateScope(point* points, int n);
int addPoint(polygon* poly);
int removePoint(polygon* poly, int idx);
void freeMemory(polygon* poly);

// --------------------------- //

int main()
{
	int i, n, idx;
	polygon* poly;

	// Start Program:
	printf("Start Program\n");

	// call functions:
	poly = createPolygon();
	printf("How many points to add: ");
	scanf("%d", &n);

	for (i = 0; i < n; i++)
	{
		printf("Point #%d: \n", i + 1);
		addPoint(poly);
	}

	printf("Enter index value to remove, invalid index to stop: ");
	do
	{
		scanf("%d", &idx);
	} while (removePoint(poly, idx));

	// write output:
	printf("Output: Scope of polygon: %.2lf\n", poly->scope);
	freeMemory(poly);

	return 0;
}
// --------------------------- //


/// <summary>
/// Function scan a point in the plane,
/// Used as auxiliary function for createPolygon.
/// </summary>
/// <param>point* p - pointer to p</param>
/// <returns>None</returns>
void scanPoint(point* p)
{
	printf("Please enter x and y coordinates of point: \n");
	scanf("%d", &(p->x));
	scanf("%d", &(p->y));
}
// --------------------------- //


/// <summary>
/// Function allocate an empty polygon.
/// </summary>
/// <returns>New allocated polygon</returns>
polygon* createPolygon()
{
	polygon* p = (polygon*)malloc(sizeof(polygon));
	if (p)
	{
		p->n = 0;
		p->scope = 0;
		p->points = NULL;
		return p;
	}
	else
	{
		printf("Memory allocation failed\n");
		return NULL;
	}
}
// --------------------------- //


/// <summary>
/// Function calculates distance between 2 adjacent points  
/// </summary>
/// <param>point* p1 - pointer to the first point</param>
/// <param>point* p2 - pointer to the second point</param>
/// <returns>The Euclidean distance between p1 and p2</returns>
double distance(point* p1, point* p2)
{
	double dist_x = (p1->x - p2->x);
	double dist_y = (p1->y - p2->y);
	return sqrt(dist_x * dist_x + dist_y * dist_y);
}
// --------------------------- //


/// <summary>
/// Function calculates and returns the Scope of a polygon.
/// </summary>
/// <param>point* points - array of points</param>
/// <param>int n - size of the array</param>
/// <returns>The Scope of a polygon</returns>
double calculateScope(point* points, int n)
{
	int i;
	double sum = distance(&points[0], &points[n - 1]); // distance between last and first points of array (closes the polygon)
	if (n < 3)
	{
		return 0;
	}
	for (i = 1; i < n; i++)
	{
		sum += distance(&points[i - 1], &points[i]); // adds distance of two adjacent points
	}
	return sum;
}
// --------------------------- //


/// <summary>
/// Function add a new point at the end of the polygon,
/// and update the scope falue.
/// </summary>
/// <param>polygon* poly - pointer to polygon</param>
/// <returns>1- success, 0- failure</returns>
int addPoint(polygon* poly)
{
	point* newArr = NULL;
	newArr = (point*)realloc(poly->points, (poly->n +1)* sizeof(point));
	if (newArr==NULL)
	{
		printf("Memory allocation failed\n");
		return 0;
	}
	else
	{
		poly->n++; // increase point counter by 1
		poly->points = newArr; 
		newArr = NULL;
		scanPoint(&(poly->points)[poly->n - 1]);
		poly->scope = calculateScope(poly->points, poly->n);
		return 1;
	}
}
// --------------------------- //


/// <summary>
/// Function remove a point from the polygon,
/// at spesific index.
/// </summary>
/// <param>polygon* poly - pointer to polygon</param>
/// <param>int idx - the index to remove</param>
/// <returns>1- success, 0- failure</returns>
int removePoint(polygon* poly, int idx)
{
	point* newArr = NULL;
	int i;
	if (idx<0 || idx>= poly->n)
	{
		return 0;
	}
	for (i = idx; i < poly->n-1; i++)
	{
		poly->points[i] = poly->points[i + 1]; 
	}
	newArr = (point*)realloc(poly->points, (poly->n-1) * sizeof(point));
	if (newArr)
	{
		poly->n--;
		poly->points = newArr;
		newArr = NULL;
		poly->scope = calculateScope(poly->points, poly->n);
		return 1;
		
	}
	else
	{
		printf("Memory allocation failed\n");
		return 0;
	}
}
// --------------------------- //


/// <summary>
/// Function free alocated memory. 
/// </summary>
/// <param>polygon* poly - pointer to polygon</param>
/// <returns>None</returns>
void freeMemory(polygon* poly)
{
	free(poly->points);
	poly->points = NULL;
	free(poly);
	poly = NULL;
}
// --------------------------- //