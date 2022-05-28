#include "Controls.h"

Button::Button(string label, int width, int height, int x, int y, int fontSize) {
	this->label = label; 
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y; 
	this->fontSize = fontSize;
	SDL_Color c = { 0, 0, 0, 175 };
	SDL_Color hc = { 25, 25, 25, 175 };
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

Textbox::Textbox(string placeholder, int width, int height, int x, int y, int fontSize) {
	this->placeholder = placeholder;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->fontSize = fontSize; 
	SDL_Color c = { 0, 0, 0, 175 };
	SDL_Color hc = { 25, 25, 25, 175 };
	this->color = c;
	this->hoverColor = hc;
}

Label::Label(string text, int x, int y, SDL_Color color, int fontSize) {
	this->text = text; 
	this->x = x;
	this->y = y;
	this->color = color; 
	this->fontSize = fontSize; 
}