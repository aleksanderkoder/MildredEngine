#pragma once
#include "SDL.h"
#include <string>
#include "SDL_ttf.h"

class Elements
{
	protected:
		int x, y;
		SDL_Color color;
		bool display; 

	public:
		// GET methods 
		int GetX();
		int GetY();
		SDL_Color GetColor();
		bool GetDisplayState(); 

		// SET methods 
		void SetPosition(int x, int y);
		void SetColor(SDL_Color* color); 

		// Utility methods
		void Show(); 
		void Hide(); 

};

class Button : public Elements {
	public:
		Button(std::string label, int width, int height, int x, int y, int fontSize, std::string fontPath);

		// GET methods 
		std::string GetLabel();
		SDL_Color GetHoverColor(); 
		int GetWidth();
		int GetHeight();
		int GetFontSize();
		TTF_Font* GetFont();

		// SET methods 
		void SetLabel(std::string label);
		void SetHoverColor(SDL_Color* color);
		void SetWidth(int width);
		void SetHeight(int height);
		void SetDimensions(int width, int height);
		void SetFont(std::string fontPath);

		// Utility methods
		void SetPressedState(bool state);
		bool IsPressed(); 

	private:
		std::string label;
		TTF_Font* font; 
		SDL_Color hoverColor;	// TODO: Add these: labelColor, labelHoverColor
		int width, height, fontSize;
		bool pressed; 
};

class Textbox : public Elements {
	public:
		Textbox(std::string placeholder, int width, int height, int x, int y, int fontSize, int limit, std::string fontPath);

		// GET methods 
		std::string GetPlaceholder();
		std::string GetValue();
		int GetWidth();
		int GetHeight();
		int GetCharLimit(); 
		SDL_Color GetHoverColor(); 
		int GetFontSize();
		TTF_Font* GetFont();

		// SET methods 
		void SetPlaceholder(std::string placeholder);
		void SetValue(std::string value);
		void SetWidth(int width);
		void SetHeight(int height);
		void SetDimensions(int width, int height);
		void SetCharLimit(int limit); 
		void SetHoverColor(SDL_Color* color);
		void SetFont(std::string fontPath);

	private:
		std::string placeholder, value;
		TTF_Font* font; 
		int width, height, charLimit, fontSize; 
		SDL_Color hoverColor; // TODO: Add these: labelColor, labelHoverColor and methods for these

};

class Label : public Elements {
	public:
		Label(std::string text, int x, int y, SDL_Color color, int fontSize, std::string fontPath);

		// GET methods 
		std::string GetText();
		int GetFontSize();
		TTF_Font* GetFont();

		// SET methods 
		void SetText(std::string text);
		void SetFont(std::string fontPath);

	private:
		std::string text;
		TTF_Font* font;
		int fontSize; 
};

class Checkbox : public Elements {
	public:
		Checkbox(int x, int y, int size, bool defaultState);

		// GET methods  
		SDL_Color GetHoverColor();
		SDL_Color GetCheckmarkColor(); 
		int GetSize(); 

		// SET methods 
		void SetHoverColor(SDL_Color* color);
		void SetCheckmarkColor(SDL_Color* color); 
		void SetState(bool state);
		void SetSize(int size); 

		// Utility methods 
		bool IsChecked(); 

	private:
		int size; 
		bool checked; 
		SDL_Color checkmarkColor, hoverColor; 
};

class Slider : public Elements {
	public:
		Slider(int x, int y, int width, int height, int thumbWidth, int thumbHeight);

		// GET methods  
		SDL_Color GetHoverColor();
		SDL_Color GetThumbColor();
		int GetWidth();
		int GetHeight();
		int GetThumbWidth();
		int GetThumbHeight();
		int GetValue();	

		// SET methods 
		void SetHoverColor(SDL_Color* color);
		void SetThumbColor(SDL_Color* color);
		void SetWidth(int width);
		void SetHeight(int height);
		void SetThumbWidth(int width);
		void SetThumbHeight(int height);
		void SetValue(int value); 
	
	private:
		int width, height, value, thumbWidth, thumbHeight;
		SDL_Color hoverColor, thumbColor;
};

