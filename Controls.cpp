#include "Controls.h"


Button::Button(string label, int width, int height, int x, int y) {
	this->label = label; 
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y; 
	SDL_Color c = { 0, 0, 0, 175 };
	SDL_Color hc = { 255, 0, 0, 175 };
	this->color = c;
	this->hoverColor = hc; 
}


void Button::Bind(void (*fn)()) {
	this->onClickCallback = fn;
}
void Button::Invoke() {
	if (this->onClickCallback)
		this->onClickCallback();
}