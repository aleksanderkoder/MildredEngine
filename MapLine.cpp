#include "MapLine.h"

MapLine::MapLine(int x, int y, int endX, int endY, string textureName) {
	MapLine::startX = x;
	MapLine::startY = y;
	MapLine::endX = endX;
	MapLine::endY = endY;
	MapLine::textureName = textureName; 
}