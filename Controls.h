#pragma once
#include <string>
#include "SDL.h"

using namespace std; 

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
		Button(string label, int width, int height, int x, int y, int fontSize = 12); 

		// GET functions 
		string GetLabel();
		SDL_Color GetHoverColor(); 
		int GetWidth();
		int GetHeight();

		// SET functions 
		void SetLabel(string label);
		void SetHoverColor(SDL_Color* color);
		void SetWidth(int width);
		void SetHeight(int height);

		void Bind(void (*fn)()); 
		void Invoke(); 

	private:
		string label;
		SDL_Color hoverColor;
		int width, height;
		void (*onClickCallback)();
};

class Textbox : public Controls {
	public:
		Textbox(string placeholder, int width, int height, int x, int y, int fontSize = 12);

		// GET functions 
		string GetPlaceholder();
		string GetValue(); 
		int GetWidth();
		int GetHeight();
		SDL_Color GetHoverColor(); 

		// SET functions 
		void SetPlaceholder(string placeholder);
		void SetValue(string value); 
		void SetWidth(int width);
		void SetHeight(int height);
		void SetHoverColor(SDL_Color* color);

	private:
		string placeholder, value;
		int width, height;
		SDL_Color hoverColor;

};

class Label : public Controls {
	public:
		Label(string text, int x, int y, SDL_Color color, int fontSize = 12);

		// GET functions 
		string GetText();

		// SET functions 
		void SetText(string text); 

	private:
		string text;
		SDL_Color color;

};

