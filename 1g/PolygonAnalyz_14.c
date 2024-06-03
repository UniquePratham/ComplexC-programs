// Name - Pratham Agarwal
// Date - 11/12/2023
// 1g. From a given set of points with (x,y) coordinates in either clockwise or anti-clockwise order. Find the maximum polygon (convex polygon)/ Intersection/ Union/ Inside or Outside?
// Program Name - PolygonAnalyz_14.c
// gcc (tdm64-1) 10.3.0

// Algorithm:
// 1.	Read the coordinates of points from input files and determine the order of points.
// 2.	Create polygons based on the order of points.
// 3.	Analyse the points to find the convex hull of each polygon, identifying the maximum polygon.
// 4.	Compare points of two polygons to find intersection points and construct a new polygon.
// 5.	Identify common boundary points between two polygons to create a new polygon that combines both.
// 6.	Determine whether one polygon is fully contained within the other or if any points lie outside.
// 7.	Generate output specific to the task (maximum polygon, intersection, union, or inside/outside analysis).
// 8.	Save the results in an output text file with the specified format.
// 9.	Terminate the program.
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>  // For MKDIR
#include <sys/types.h> // For MKDIR
#define MAX_FILENAME_LENGTH 100

struct Point
{
    int x, y;
};

struct Polygon
{
    struct Point *points;
    int numPoints;
};

struct Polygon globalConvexHull; // Global variable with a different name

int orientation(struct Point p, struct Point q, struct Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0)
        return 0;
    return (val > 0) ? 1 : 2;
}

int comparePoints(const void *a, const void *b)
{
    struct Point p1 = *(struct Point *)a;
    struct Point p2 = *(struct Point *)b;
    int o = orientation(p1, globalConvexHull.points[0], p2);
    if (o == 0)
        return ((p2.x - globalConvexHull.points[0].x) * (p2.x - globalConvexHull.points[0].x) + (p2.y - globalConvexHull.points[0].y) * (p2.y - globalConvexHull.points[0].y) >= (p1.x - globalConvexHull.points[0].x) * (p1.x - globalConvexHull.points[0].x) + (p1.y - globalConvexHull.points[0].y) * (p1.y - globalConvexHull.points[0].y)) ? -1 : 1;
    return (o == 2) ? -1 : 1;
}

void convexHull(struct Point points[], int n, struct Polygon *resultConvexHull)
{
    resultConvexHull->points = (struct Point *)malloc(n * sizeof(struct Point));
    resultConvexHull->numPoints = 0;

    resultConvexHull->points[resultConvexHull->numPoints++] = points[0];
    resultConvexHull->points[resultConvexHull->numPoints++] = points[1];

    for (int i = 2; i < n; i++)
    {
        while (resultConvexHull->numPoints > 1 && orientation(resultConvexHull->points[resultConvexHull->numPoints - 2],
                                                              resultConvexHull->points[resultConvexHull->numPoints - 1], points[i]) != 2)
        {
            resultConvexHull->numPoints--;
        }
        resultConvexHull->points[resultConvexHull->numPoints++] = points[i];
    }
}

// Rest of the code remains unchanged

void findIntersection(struct Polygon *poly1, struct Polygon *poly2, struct Polygon *intersection)
{
    // Assuming simple intersection by finding common points
    int i, j;
    intersection->points = (struct Point *)malloc(poly1->numPoints * sizeof(struct Point));
    intersection->numPoints = 0;

    for (i = 0; i < poly1->numPoints; i++)
    {
        for (j = 0; j < poly2->numPoints; j++)
        {
            if (poly1->points[i].x == poly2->points[j].x && poly1->points[i].y == poly2->points[j].y)
            {
                intersection->points[intersection->numPoints++] = poly1->points[i];
                break; // Break inner loop to avoid duplicate points in intersection
            }
        }
    }
}

void findUnion(struct Polygon *poly1, struct Polygon *poly2, struct Polygon *unionPoly)
{
    // Simple union by combining points from both polygons
    unionPoly->points = (struct Point *)malloc((poly1->numPoints + poly2->numPoints) * sizeof(struct Point));
    unionPoly->numPoints = 0;

    for (int i = 0; i < poly1->numPoints; i++)
    {
        unionPoly->points[unionPoly->numPoints++] = poly1->points[i];
    }

    for (int i = 0; i < poly2->numPoints; i++)
    {
        unionPoly->points[unionPoly->numPoints++] = poly2->points[i];
    }
}

int isPolygonInside(struct Polygon *innerPoly, struct Polygon *outerPoly)
{
    // Assuming simple check by comparing points
    for (int i = 0; i < innerPoly->numPoints; i++)
    {
        int isInside = 0;
        for (int j = 0; j < outerPoly->numPoints; j++)
        {
            if (innerPoly->points[i].x == outerPoly->points[j].x && innerPoly->points[i].y == outerPoly->points[j].y)
            {
                isInside = 1;
                break;
            }
        }
        if (!isInside)
        {
            // If any point of innerPoly is not found in outerPoly, then it's not fully inside
            return 0;
        }
    }
    // All points of innerPoly are found in outerPoly, so it's fully inside
    return 1;
}

void readPointsFromFile(char *filename, struct Point points[], int *n)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", n);
    for (int i = 0; i < *n; i++)
    {
        fscanf(file, "%d %d", &points[i].x, &points[i].y);
    }

    fclose(file);
}

void writePointsToFile(char *filename, struct Point points[], int n, char *word)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    if (n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            fprintf(file, "%d %d\n", points[i].x, points[i].y);
        }
    }
    else
    {
        fprintf(file, "No %s points found.", word);
    }

    fclose(file);
}

int main()
{
    printf("*** Polygon Analyzer ***\n\n\n");
    struct Point points1[100], points2[100];
    int n1, n2;
    const char *folder_name = "PolygonsDetails";
    char outputFilename[MAX_FILENAME_LENGTH];
    const char *operations[] = {"union", "intersection", "output1", "output2"};
    mkdir(folder_name);
    // Step 1: Read coordinates of points from input files
    printf("Read Points of Polygon1\n");
    readPointsFromFile("input1.txt", points1, &n1);
    printf("Read Points of Polygon2\n");
    readPointsFromFile("input2.txt", points2, &n2);

    // Step 2: Create polygons based on the order of points
    struct Polygon polygon1, polygon2;
    convexHull(points1, n1, &polygon1);
    convexHull(points2, n2, &polygon2);

    // Step 3: Analyze points to find the convex hull of each polygon, identifying the maximum polygon
    // (Already done in the convexHull function)

    // Step 4: Compare points of two polygons to find intersection points and construct a new polygon
    struct Polygon intersectionPoly;
    findIntersection(&polygon1, &polygon2, &intersectionPoly);

    // Step 5: Identify common boundary points between two polygons to create a new polygon that combines both
    struct Polygon unionPoly;
    findUnion(&polygon1, &polygon2, &unionPoly);

    // Step 6: Determine whether one polygon is fully contained within the other or if any points lie outside
    int isPoly1Inside2 = isPolygonInside(&polygon1, &polygon2);
    int isPoly2Inside1 = isPolygonInside(&polygon2, &polygon1);

    // Step 7: Generate output specific to the task (maximum polygon, intersection, union, or inside/outside analysis)
    // Writing the results to output files
    printf("Intersecting Points between Polygon 2 and Polygon 1 are saved in intersection.txt\n");
    snprintf(outputFilename, sizeof(outputFilename), "%s/%s.txt", folder_name, operations[1]);
    writePointsToFile(outputFilename, intersectionPoly.points, intersectionPoly.numPoints, "intersection");
    printf("Union Points between Polygon 2 and Polygon 1 are saved in union.txt\n");
    snprintf(outputFilename, sizeof(outputFilename), "%s/%s.txt", folder_name, operations[0]);
    writePointsToFile(outputFilename, unionPoly.points, unionPoly.numPoints, "union");

    // Additional analysis outputs based on the inside/outside checks
    if (isPoly1Inside2)
    {
        printf("Polygon 1 is fully inside Polygon 2.\n");
    }
    else
    {
        printf("Polygon 1 is not fully inside Polygon 2.\n");
    }

    if (isPoly2Inside1)
    {
        printf("Polygon 2 is fully inside Polygon 1.\n");
    }
    else
    {
        printf("Polygon 2 is not fully inside Polygon 1.\n");
    }

    // Step 8: Save the results in an output text file with the specified format
    printf("Convex Hull Points of Polygon 1 is saved in output1.txt\n");
    snprintf(outputFilename, sizeof(outputFilename), "%s/%s.txt", folder_name, operations[2]);
    writePointsToFile(outputFilename, polygon1.points, polygon1.numPoints, "convex hull");
    printf("Convex Hull Points of Polygon 2 is saved in output2.txt\n");
    snprintf(outputFilename, sizeof(outputFilename), "%s/%s.txt", folder_name, operations[3]);
    writePointsToFile(outputFilename, polygon2.points, polygon2.numPoints, "convex hull");
    printf("Details saved in %s folder.\n\n", outputFilename);
    // Step 9: Terminate the program

    return 0;
}
