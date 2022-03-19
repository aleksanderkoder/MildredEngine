#pragma once
#include <string>

using namespace std; 

class MapBoundary
{
public:
	int startX, startY, endX, endY;
	string textureName; 
	MapBoundary(int x, int y, int endX, int endY, string textureName);
};

