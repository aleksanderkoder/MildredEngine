#include "Calc.h"
#define _USE_MATH_DEFINES
#include <cmath>

double Calc::ToRadians(int deg) {
	return deg * M_PI / 180;
}

double* Calc::LineToLineCollision(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
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
        double arr[2];
        //double* arrayPointer = arr;
        arr[0] = intersectionX;
        arr[1] = intersectionY;
        return arr;
    }
    return NULL; 
}

double Calc::GetDistance(double x1, double y1, double x2, double y2) {
    double y = x2 - x1;
    double x = y2 - y1;
    return sqrt(x * x + y * y);
}

double Calc::ToDegrees(double rad) {
    return rad * 180 / M_PI;
}
 
double Calc::NormalizeAngleRad(double angle) {
    double res = fmod(angle, 6.28319); 
    if (res < 0) res *= -1; 
    return res;
}
		
		
		