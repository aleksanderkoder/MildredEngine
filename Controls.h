#pragma once
#include <string>
#include "SDL.h"

using namespace std; 

class Controls
{
public:
	int width, height, x, y, fontSize;
	SDL_Color color, hoverColor;

};

class Button : public Controls {
	public:
		string label;
		Button(string label, int width, int height, int x, int y, int fontSize); 
		void Bind(void (*fn)()); 
		void Invoke(); 

	private:
		void (*onClickCallback)();
};

class Textbox : public Controls {
	public:
		string placeholder, value;
		Textbox(string placeholder, int width, int height, int x, int y, int fontSize);
};

