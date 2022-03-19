#include "MapBoundary.h"

MapBoundary::MapBoundary(int x, int y, int endX, int endY, string textureName) {
	MapBoundary::startX = x;
	MapBoundary::startY = y;
	MapBoundary::endX = endX;
	MapBoundary::endY = endY;
	MapBoundary::textureName = textureName;
}