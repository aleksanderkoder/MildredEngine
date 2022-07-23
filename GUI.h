#pragma once

#include "Mildred.h"
#include "Elements.h"
#include <tuple>

class GUI
{
	public:
		static SDL_Renderer* targetRenderer;

		// Data related to buttons 
		static std::vector<Button*>* buttons;

		// Data related to textboxes 
		static std::vector<Textbox*>* textboxes;
		static Textbox* activeTextbox;

		// Data related to labels
		static std::vector<Label*>* labels;

		static void SetRenderTarget(SDL_Renderer* r);
		static Label* CreateLabel(std::string text, int x, int y, SDL_Color color, int fontSize = 12, std::string fontPath = "fonts/arial.ttf");
		static Button* CreateButton(std::string label, int width, int height, int x, int y, int fontSize = 12, std::string fontPath = "fonts/arial.ttf");
		static Textbox* CreateTextbox(std::string placeholder, int width, int height, int x, int y, int fontSize = 12, int limit = 25, std::string fontPath = "fonts/arial.ttf");
		static void RenderLabel(std::string text, int x, int y, SDL_Color color, TTF_Font* font, int fontSize = 12);
		static void Render();
		static void Init();

	private:
		static Uint32 delta, textboxCursorDelta;
		static char lastPressedKey; 
		static bool leftMouseButtonPressedState, leftMouseButtonPressedLastState,
			drawTextBoxCursor, capsLockEnabled, rerender; 
		static SDL_Texture* previousFrame; 

		static TTF_Font* OpenFont(std::string fontUrl, int size);
		static std::tuple<int, int> GetTextDimensions(std::string text, TTF_Font* font);
		// TODO: Get rid of the 2 funtions below, as they are kinda pointless and add to confusion
		static bool DeltaTimeHasPassed(int ms); 
		static void UpdateDelta(Uint32 now); 
		static bool OnMouseHover(int x, int y, int width, int height);
		static void UpdateMouseButtonState(); 
		static bool ValidKey(int key); 
		static void CaptureInputText();
		static void RenderButtons();
		static void RenderTextboxes();
		static void RenderLabels();
};

