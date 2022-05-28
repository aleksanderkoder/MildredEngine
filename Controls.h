#pragma once
#include <string>
#include "SDL.h"

using namespace std; 

class Controls
{
public:
	int x, y, fontSize;
	SDL_Color color;

};

class Button : public Controls {
	public:
		string label;
		SDL_Color hoverColor;
		int width, height;
		Button(string label, int width, int height, int x, int y, int fontSize); 
		void Bind(void (*fn)()); 
		void Invoke(); 

	private:
		void (*onClickCallback)();
};

class Textbox : public Controls {
	public:
		string placeholder, value;
		int width, height;
		SDL_Color hoverColor; 
		Textbox(string placeholder, int width, int height, int x, int y, int fontSize);
};

class Label : public Controls {
	public:
		string text;
		SDL_Color color;
		Label(string text, int x, int y, SDL_Color color, int fontSize);
};

