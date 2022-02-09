#pragma once

struct Calc
{
	static double ToRadians(int deg); 
	static int* LineToLineCollision(int* arr, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
	static int GetDistance(int x1, int y1, int x2, int y2);
};

