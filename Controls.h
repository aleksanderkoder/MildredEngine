#pragma once
#include <string>
#include "SDL.h"

using namespace std; 

typedef void (*ActionFunction)();

class Controls
{
	public:
		string type; 
		int width, height, x, y;
};

class Button: public Controls {
	public:
		string label;
		SDL_Color color;  
		SDL_Color hoverColor; 
		ActionFunction af;
		Button(string label, int width, int height, int x, int y); 
		void AttachAction(ActionFunction& func);
		void InvokeAction(); 
};

