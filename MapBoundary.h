#pragma once
#include <string>

class MapBoundary
{
public:
	int startX, startY, endX, endY;
	std::string textureName;
	MapBoundary(int x, int y, int endX, int endY, std::string textureName);
};

