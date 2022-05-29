#include "Controls.h"

// CONTROLS - Common for every control type

int Controls::GetX() {
	return this->x; 
}

int Controls::GetY() {
	return this->y;
}

SDL_Color Controls::GetColor() {
	return this->color;
}

int Controls::GetFontSize() {
	return this->fontSize; 
}

void Controls::SetPosition(int x, int y) {
	this->x = x;
	this->y = y; 
}

void Controls::SetColor(SDL_Color* color) {
	this->color = *color; 
}

// BUTTON

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

string Button::GetLabel() {
	return this->label; 
}

SDL_Color Button::GetHoverColor() {
	return this->hoverColor; 
}

int Button::GetWidth() {
	return this->width;
}

int Button::GetHeight() {
	return this->height; 
}

void Button::SetLabel(string label) {
	this->label = label;
}

void Button::SetHoverColor(SDL_Color* color) {
	this->hoverColor = *color; 
}

void Button::SetWidth(int width) {
	this->width = width; 
}

void Button::SetHeight(int height) {
	this->height = height; 
}

void Button::Bind(void (*fn)()) {
	this->onClickCallback = fn;
}

void Button::Invoke() {
	if (this->onClickCallback)
		this->onClickCallback();
}

// TEXTBOX

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

string Textbox::GetPlaceholder() {
	return this->placeholder; 
}

string Textbox::GetValue() {
	return this->value; 
}

int Textbox::GetWidth() {
	return this->width;
}

int Textbox::GetHeight() {
	return this->height; 
}

SDL_Color Textbox::GetHoverColor() {
	return this->hoverColor;
}

void Textbox::SetPlaceholder(string placeholder) {
	this->placeholder = placeholder; 
}

void Textbox::SetValue(string value) {
	this->value = value; 
}

void Textbox::SetWidth(int width) {
	this->width = width; 
}

void Textbox::SetHeight(int height) {
	this->height = height; 
}

void Textbox::SetHoverColor(SDL_Color* color) {
	this->hoverColor = *color; 
}

// LABEL

Label::Label(string text, int x, int y, SDL_Color color, int fontSize) {
	this->text = text; 
	this->x = x;
	this->y = y;
	this->color = color; 
	this->fontSize = fontSize; 
}

string Label::GetText() {
	return this->text; 
}

void Label::SetText(string text) {
	this->text = text; 
}