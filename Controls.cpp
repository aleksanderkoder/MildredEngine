#include "Controls.h"

// CONTROLS - Common methods for every control type

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

TTF_Font* Controls::GetFont() {
	return this->font;
}

void Controls::SetPosition(int x, int y) {
	this->x = x;
	this->y = y; 
}

void Controls::SetColor(SDL_Color* color) {
	this->color = *color; 
}

void Controls::SetFont(std::string fontPath) {
	this->font = TTF_OpenFont(fontPath.c_str(), this->fontSize);
}

void Controls::Show() {
	this->display = true; 
}

void Controls::Hide() {
	this->display = false; 
}

// BUTTON

Button::Button(std::string label, int width, int height, int x, int y, int fontSize, std::string fontPath) {
	this->label = label; 
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y; 
	this->display = true; 
	this->fontSize = fontSize;
	SDL_Color c = { 0, 0, 0, 175 };
	SDL_Color hc = { 25, 25, 25, 175 };
	this->color = c;
	this->hoverColor = hc; 

	if (!(this->font = TTF_OpenFont(fontPath.c_str(), fontSize))) {
		char t[] = "Font error";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, t, TTF_GetError(), NULL);
		exit(0);
	}
}

std::string Button::GetLabel() {
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

void Button::SetLabel(std::string label) {
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

void Button::SetDimensions(int width, int height) {
	this->width = width;
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

Textbox::Textbox(std::string placeholder, int width, int height, int x, int y, int fontSize, int limit, std::string fontPath) {
	this->placeholder = placeholder;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->display = true;
	this->fontSize = fontSize; 
	SDL_Color c = { 0, 0, 0, 175 };
	SDL_Color hc = { 25, 25, 25, 175 };
	this->color = c;
	this->charLimit = limit; 
	this->hoverColor = hc;

	if (!(this->font = TTF_OpenFont(fontPath.c_str(), fontSize))) {
		char t[] = "Font error";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, t, TTF_GetError(), NULL);
		exit(0);
	}
}

std::string Textbox::GetPlaceholder() {
	return this->placeholder; 
}

std::string Textbox::GetValue() {
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

int Textbox::GetCharLimit() {
	return this->charLimit; 
}

void Textbox::SetPlaceholder(std::string placeholder) {
	this->placeholder = placeholder; 
}

void Textbox::SetValue(std::string value) {
	this->value = value; 
}

void Textbox::SetWidth(int width) {
	this->width = width; 
}

void Textbox::SetHeight(int height) {
	this->height = height; 
}

void Textbox::SetDimensions(int width, int height) {
	this->width = width; 
	this->height = height; 
}

void Textbox::SetHoverColor(SDL_Color* color) {
	this->hoverColor = *color; 
}

void Textbox::SetCharLimit(int limit) {
	this->charLimit = limit; 
}

// LABEL

Label::Label(std::string text, int x, int y, SDL_Color color, int fontSize, std::string fontPath) {
	this->text = text; 
	this->x = x;
	this->y = y;
	this->color = color; 
	this->display = true;
	this->fontSize = fontSize; 

	if (!(this->font = TTF_OpenFont(fontPath.c_str(), fontSize))) {
		char t[] = "Font error";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, t, TTF_GetError(), NULL);
		exit(0);
	}
}

std::string Label::GetText() {
	return this->text; 
}

void Label::SetText(std::string text) {
	this->text = text; 
}

// Checkbox

Checkbox::Checkbox(std::string label, int x, int y, int width, int height, int fontSize, std::string fontPath) {
	this->label = label;
	this->x = x;
	this->y = y;
	this->width = width; 
	this->height = height; 
	this->display = true;
	this->fontSize = fontSize;
	this->checked = false; 
	SDL_Color c = { 0, 0, 0, 175 };
	SDL_Color hc = { 25, 25, 25, 175 }; 
	SDL_Color lc = { 255, 255, 255, 255 };
	SDL_Color cC = { 3, 75, 3, 255 };
	this->color = c; 
	this->hoverColor = hc;
	this->labelColor = lc; 
	this->checkmarkColor = cC; 

	if (!(this->font = TTF_OpenFont(fontPath.c_str(), fontSize))) {
		char t[] = "Font error";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, t, TTF_GetError(), NULL);
		exit(0);
	}
}

std::string Checkbox::GetLabel() {
	return this->label; 
}

SDL_Color Checkbox::GetHoverColor() {
	return this->hoverColor;
}

SDL_Color Checkbox::GetCheckmarkColor() {
	return this->checkmarkColor;
}

SDL_Color Checkbox::GetLabelColor() {
	return this->labelColor;
}

std::string Checkbox::GetLabel() {
	return this->label;
}

int Checkbox::GetWidth() {
	return this->width;
}

int Checkbox::GetHeight() {
	return this->height;
}

void Checkbox::SetLabel(std::string label) {
	this->label = label; 
}

void Checkbox::SetHoverColor(SDL_Color* color) {
	this->hoverColor = *color;
}

void Checkbox::SetCheckmarkColor(SDL_Color* color) {
	this->checkmarkColor = *color;
}

void Checkbox::SetLabelColor(SDL_Color* color) {
	this->labelColor = *color;
}

void Checkbox::SetWidth(int width) {
	this->width = width;
}

void Checkbox::SetHeight(int height) {
	this->height = height;
}

void Checkbox::SetState(bool state) {
	this->checked = state;
}

bool Checkbox::IsChecked() {
	return this->checked; 
}

// Slider

Slider::Slider(std::string label, int x, int y, int width, int height, int thumbWidth, int thumbHeight, int fontSize, std::string fontPath) {
	this->label = label;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->thumbWidth = thumbWidth; 
	this->thumbHeight = thumbHeight; 
	this->display = true;
	this->value = 50; 
	this->fontSize = fontSize;
	SDL_Color c = { 0, 0, 0, 175 };
	SDL_Color hc = { 25, 25, 25, 175 };
	SDL_Color lc = { 255, 255, 255, 255 };
	SDL_Color tC = { 25, 25, 25, 175 };
	this->color = c;
	this->hoverColor = hc;
	this->labelColor = lc;
	this->thumbColor = tC;

	if (!(this->font = TTF_OpenFont(fontPath.c_str(), fontSize))) {
		char t[] = "Font error";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, t, TTF_GetError(), NULL);
		exit(0);
	}
}

// TODO: Continue class implementation

std::string Slider::GetLabel() {
	return this->label; 
}

int Slider::GetThumbWidth() {
	return this->thumbWidth;
}

int Slider::GetThumbHeight() {
	return this->thumbHeight;
}