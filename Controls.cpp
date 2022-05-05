#include "Controls.h"

Button::Button(string label, int width, int height, int x, int y) {
	this->type = "button"; 
	this->label = label; 
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y; 
	SDL_Color c = { 0, 0, 0, 175 };
	SDL_Color hc = { 255, 255, 255, 175 };
	this->renderColor = c;
	this->originalColor = c; 
	this->hoverColor = hc; 
}