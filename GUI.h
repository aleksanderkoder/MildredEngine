#pragma once

#include "Mildred.h"
#include "Controls.h"

class GUI
{
	public:
		static vector<Button*>* buttons;
		static SDL_Renderer* targetRenderer;
		// Contains a bitmask for the mouse buttons, which can be tested using SDL_BUTTON(x)
		static Uint32 mouseButtons;

		static void SetRenderTarget(SDL_Renderer*);
		static void CreateButton(string label, int width, int height, int x, int y);
		static void Render(); 
		static bool OnButtonHover(Button* b);
};

