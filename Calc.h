#pragma once

struct Calc
{
	static double ToRadians(int deg); 
	static int* LineToLineCollision(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
	static int GetDistance(int x1, int y1, int x2, int y2);
};

