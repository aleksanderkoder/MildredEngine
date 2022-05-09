#pragma once
#include <string>
#include "SDL.h"

using namespace std; 

class Controls
{
	public:
		int width, height, x, y;
};

class Button: public Controls {
	public:
		string label;
		SDL_Color color;  
		SDL_Color hoverColor; 
		Button(string label, int width, int height, int x, int y); 
		void Bind(void (*fn)()); 
		void Invoke(); 

	private:
		void (*onClickCallback)();
};

