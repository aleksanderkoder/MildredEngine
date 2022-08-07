#pragma once

#include "Mildred.h"
#include "Elements.h"
#include <tuple>

class GUI
{
	public:
		// Public methods 
		static void SetRenderTarget(SDL_Renderer* renderer);
		static Label* CreateLabel(std::string text, int x, int y, SDL_Color color, int fontSize = 12, std::string fontPath = "fonts/CascadiaCode.ttf");
		static Button* CreateButton(std::string label, int width, int height, int x, int y, int fontSize = 12, std::string fontPath = "fonts/CascadiaCode.ttf");
		static Textbox* CreateTextbox(std::string placeholder, int width, int height, int x, int y, int fontSize = 12, int limit = 25, std::string fontPath = "fonts/CascadiaCode.ttf");
		static Checkbox* CreateCheckbox(int x, int y, int size, bool defaultState = false);
		static void RenderLabel(std::string text, int x, int y, SDL_Color color, TTF_Font* font, int fontSize = 12);
		static void Render();
		static void Init();
		static void DrawCircle(int32_t centreX, int32_t centreY, int32_t radius); 
		
	private:
		// General library data 
		static SDL_Renderer* targetRenderer;
		static bool leftMouseButtonPressedState, leftMouseButtonPressedLastState, rerender; 

		//	BUTTON - Related data 
		static std::vector<Button*>* buttons;

		// TEXTBOX - Related data  
		static std::vector<Textbox*>* textboxes;
		static Textbox* activeTextbox;
		static Uint32 textboxCursorDelta, delta;
		static char lastPressedKey; 
		static bool drawTextBoxCursor, capsLockEnabled;

		// LABEL - Related data 
		static std::vector<Label*>* labels;

		// CHECKBOX - Related data 
		static std::vector<Checkbox*>* checkboxes;

		// Private methods  
		static TTF_Font* OpenFont(std::string fontUrl, int size);
		static std::tuple<int, int> GetTextDimensions(std::string text, TTF_Font* font); 
		static bool OnMouseHover(int x, int y, int width, int height);
		static void UpdateMouseButtonState(); 
		static bool ValidKey(int key); 
		static void CaptureInputText();
		static void RenderButtons();
		static void RenderTextboxes();
		static void RenderLabels();
		static void RenderCheckboxes(); 
};

