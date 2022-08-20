#pragma once

#include "Mildred.h"
#include "Elements.h"
#include "Page.h"
#include <tuple>
#include "SDL_ttf.h"
 
class GUI
{
	public:
		// Library setup methods 
		static void Setup(int viewWidth, int viewHeight);
		static void SetRenderTarget(SDL_Renderer* renderer);

		// Element creation methods 
		static Label* CreateLabel(std::string text, int x, int y, SDL_Color color, int fontSize = 12, std::string fontPath = "fonts/CascadiaCode.ttf");
		static Button* CreateButton(std::string label, int width, int height, int x, int y, int fontSize = 12, std::string fontPath = "fonts/CascadiaCode.ttf");
		static Textbox* CreateTextbox(std::string placeholder, int width, int height, int x, int y, int fontSize = 12, int limit = 25, std::string fontPath = "fonts/CascadiaCode.ttf");
		static Checkbox* CreateCheckbox(int x, int y, int size, bool defaultState = false);
		
		// Page related methods 
		static Page* CreatePage(); 
		static void DeletePage(Page* page);
		static void SetPage(Page* page);	// TODO: Make rendering respect current page 
		
		// Library utility methods 
		static void RenderLabel(std::string text, int x, int y, SDL_Color color, TTF_Font* font, int fontSize = 12);
		static void DrawCircle(int32_t centreX, int32_t centreY, int32_t radius); 
		static void Render();
		static void Rerender(); // TODO: Only render new frame texture when rerender bool is true!
		
	private:
		// General library data 
		static SDL_Renderer* targetRenderer;
		static bool leftMouseButtonPressedState, leftMouseButtonPressedLastState, rerender; 
		static int viewWidth, viewHeight; 
		static SDL_Texture* snapshotFrame; 
		

		// PAGES - Related data 
		static Page* currentPage; 

		// TEXTBOX - Related data  
		static Textbox* activeTextbox;
		static Uint32 textboxCursorDelta, delta;
		static char lastPressedKey; 
		static bool drawTextBoxCursor, capsLockEnabled;

		// Private methods  
		static void prepareNewSnapshotFrame(); 
		static void finalizeNewSnapshotFrame(); 
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

