#include "MapBoundary.h"

MapBoundary::MapBoundary(int x, int y, int endX, int endY, string textureName) {
	this->startX = x;
	this->startY = y;
	this->endX = endX;
	this->endY = endY;
	this->textureName = textureName;
}