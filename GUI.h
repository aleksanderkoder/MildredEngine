#pragma once

#include "Mildred.h"
#include "Controls.h"

class GUI
{
	public:
		static vector<Button*>* buttons;
		static SDL_Renderer* targetRenderer;

		static void SetRenderTarget(SDL_Renderer*);
		static void CreateButton(string label, int width, int height, int x, int y);
		static void Render(); 
};

