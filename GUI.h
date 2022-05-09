#pragma once

#include "Mildred.h"
#include "Controls.h"
#include <SDL_ttf.h>

class GUI
{
	public:
		static vector<Button*>* buttons;
		static SDL_Renderer* targetRenderer;
		// Contains a bitmask for the mouse buttons, which can be tested using SDL_BUTTON(x)
		static Uint32 mouseButtons;

		static void SetRenderTarget(SDL_Renderer*);
		static void DisplayText(string msg, int fontSize, int xpos, int ypos, SDL_Color color);
		static int* GetTextDimensions(string text, int fontSize);
		static Button* CreateButton(string label, int width, int height, int x, int y);
		static void Render(); 
		static bool OnButtonHover(Button* b);
};

