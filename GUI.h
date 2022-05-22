#pragma once

#include "Mildred.h"
#include "Controls.h"
#include <SDL_ttf.h>

class GUI
{
	public:
		static SDL_Renderer* targetRenderer;
		static string currentFont;

		// Data related to buttons 
		static vector<Button*>* buttons;

		// Data related to textboxes 
		static vector<Textbox*>* textboxes;
		static Textbox* activeTextbox;

		static void SetRenderTarget(SDL_Renderer*);
		static void CreateLabel(string msg, int xpos, int ypos, SDL_Color color, int fontSize = 12);
		static Button* CreateButton(string label, int width, int height, int x, int y, int fontSize = 12);
		static void RenderButtons();
		static void RenderTextboxes(); 
		static void CaptureInputText();
		static void Render(); 
		static bool OnButtonHover(Button* b);
		static void SetFont(string fontPath); 
		static void Init(); 
		static Textbox* CreateTextbox(string placeholder, int width, int height, int x, int y, int fontSize = 12);
		static bool OnTextboxHover(Textbox* tb); 

	private:
		// Contains a bitmask for the mouse buttons, which can be tested using SDL_BUTTON(x)
		// Needs seperate variables for each control to avoid overlapping issues on button press
		static Uint32 mouseButtonsForButtons, mouseButtonsForTextboxes;
		static Uint32 delta;
		static char lastPressed; 

		static TTF_Font* OpenFont(string fontUrl, int size);
		static int* GetTextDimensions(string text, TTF_Font* font);
		static bool DeltaTimeHasPassed(int ms); 
		static void UpdateDelta(Uint32 now); 
};

