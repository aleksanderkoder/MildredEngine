#pragma once
#include <string>
using namespace std; 

class MapLine
{
public:
	int startX, startY, endX, endY;
	string textureName; 
	MapLine(int x, int y, int endX, int endY, string textureName);
};

