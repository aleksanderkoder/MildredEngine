#include "Calc.h"
#include <cmath>

double Calc::ToRadians(int deg) {
	return (deg * (atan(1.0) * 4)) / 180;
}

int* Calc::LineToLineCollision(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    // calculate the distance to intersection point
    double uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
    double uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

    // if uA and uB are between 0-1, lines are colliding
    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {

        // optionally, draw a circle where the lines meet
        double intersectionX = x1 + (uA * (x2 - x1));
        double intersectionY = y1 + (uA * (y2 - y1));
        /*ctxUI.beginPath();
        ctxUI.strokeStyle = "orange";
        ctxUI.arc(intersectionX, intersectionY, 2, 0, 2 * Math.PI);
        ctxUI.stroke();
        ctxUI.closePath();*/

        // Use these values to determine projection slice height
        int arr[2];
        int* arrayPointer = arr;
        arr[0] = intersectionX;
        arr[1] = intersectionY;
        return arrayPointer;
    }
    return NULL; 
}

int Calc::GetDistance(int x1, int y1, int x2, int y2) {
    int y = x2 - x1;
    int x = y2 - y1;
    return sqrt(x * x + y * y);
}
		
		
		