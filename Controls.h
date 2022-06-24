#pragma once
#include <string>
#include "SDL.h"

class Controls
{
	protected:
		int x, y, fontSize;
		SDL_Color color;

	public:
		// GET functions 
		int GetX();
		int GetY();
		SDL_Color GetColor();
		int GetFontSize();

		// SET functions 
		void SetPosition(int x, int y);
		void SetColor(SDL_Color* color);

};

class Button : public Controls {
	public:
		Button(std::string label, int width, int height, int x, int y, int fontSize = 12);

		// GET functions 
		std::string GetLabel();
		SDL_Color GetHoverColor(); 
		int GetWidth();
		int GetHeight();

		// SET functions 
		void SetLabel(std::string label);
		void SetHoverColor(SDL_Color* color);
		void SetWidth(int width);
		void SetHeight(int height);
		void SetDimensions(int width, int height);

		void Bind(void (*fn)()); 
		void Invoke(); 

	private:
		std::string label;
		SDL_Color hoverColor;
		int width, height;
		void (*onClickCallback)();
};

class Textbox : public Controls {
	public:
		Textbox(std::string placeholder, int width, int height, int x, int y, int fontSize = 12, int limit = 25);

		// GET functions 
		std::string GetPlaceholder();
		std::string GetValue();
		int GetWidth();
		int GetHeight();
		int GetCharLimit(); 
		SDL_Color GetHoverColor(); 

		// SET functions 
		void SetPlaceholder(std::string placeholder);
		void SetValue(std::string value);
		void SetWidth(int width);
		void SetHeight(int height);
		void SetDimensions(int width, int height);
		void SetCharLimit(int limit); 
		void SetHoverColor(SDL_Color* color);

	private:
		std::string placeholder, value;
		int width, height, charLimit; 
		SDL_Color hoverColor;

};

class Label : public Controls {
	public:
		Label(std::string text, int x, int y, SDL_Color color, int fontSize = 12);

		// GET functions 
		std::string GetText();

		// SET functions 
		void SetText(std::string text);

	private:
		std::string text;
};

