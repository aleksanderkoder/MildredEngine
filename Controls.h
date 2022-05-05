#pragma once
#include <string>
#include "SDL.h"

using namespace std; 

class Controls
{
	public:
		string type; 
		int width, height, x, y;
};

class Button: public Controls {
	public:
		string label;
		SDL_Color renderColor; 
		SDL_Color originalColor; 
		SDL_Color hoverColor; 
		Button(string label, int width, int height, int x, int y); 
};

