#include "Controls.h"

Button::Button(string label, int width, int height, int x, int y) {
	this->type = "button"; 
	this->label = label; 
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y; 
}