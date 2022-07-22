#pragma once
#include <string>
#include "SDL.h"
#include <SDL_ttf.h>

class Controls
{
	protected:
		int x, y, fontSize;
		SDL_Color color;
		TTF_Font* font; 
		bool display; 

	public:
		// GET methods 
		int GetX();
		int GetY();
		SDL_Color GetColor();
		int GetFontSize();
		TTF_Font* GetFont(); 

		// SET methods 
		void SetPosition(int x, int y);
		void SetColor(SDL_Color* color);
		void SetFont(std::string fontPath); 

		// Utility methods
		void Show(); 
		void Hide(); 

};

class Button : public Controls {
	public:
		Button(std::string label, int width, int height, int x, int y, int fontSize, std::string fontPath);

		// GET methods 
		std::string GetLabel();
		SDL_Color GetHoverColor(); 
		int GetWidth();
		int GetHeight();

		// SET methods 
		void SetLabel(std::string label);
		void SetHoverColor(SDL_Color* color);
		void SetWidth(int width);
		void SetHeight(int height);
		void SetDimensions(int width, int height);

		void Bind(void (*fn)()); 
		void Invoke(); 

	private:
		std::string label;
		SDL_Color hoverColor;	// TODO: Add these: labelColor, labelHoverColor
		int width, height;
		void (*onClickCallback)();
};

class Textbox : public Controls {
	public:
		Textbox(std::string placeholder, int width, int height, int x, int y, int fontSize, int limit, std::string fontPath);

		// GET methods 
		std::string GetPlaceholder();
		std::string GetValue();
		int GetWidth();
		int GetHeight();
		int GetCharLimit(); 
		SDL_Color GetHoverColor(); 

		// SET methods 
		void SetPlaceholder(std::string placeholder);
		void SetValue(std::string value);
		void SetWidth(int width);
		void SetHeight(int height);
		void SetDimensions(int width, int height);
		void SetCharLimit(int limit); 
		void SetHoverColor(SDL_Color* color);

	private:
		std::string placeholder, value;
		int width, height, charLimit; 
		SDL_Color hoverColor; // TODO: Add these: labelColor, labelHoverColor

};

class Label : public Controls {
	public:
		Label(std::string text, int x, int y, SDL_Color color, int fontSize, std::string fontPath);

		// GET methods 
		std::string GetText();

		// SET methods 
		void SetText(std::string text);

	private:
		std::string text;
};

class Checkbox : public Controls {
	public:
		Checkbox(std::string label, int x, int y, int width, int height, int fontSize, std::string fontPath);

		// GET methods  
		std::string GetLabel();
		SDL_Color GetHoverColor();
		SDL_Color GetCheckmarkColor(); 
		SDL_Color GetLabelColor(); 
		int GetWidth();
		int GetHeight();

		// SET methods 
		void SetLabel(std::string label);
		void SetHoverColor(SDL_Color* color);
		void SetCheckmarkColor(SDL_Color* color); 
		void SetLabelColor(SDL_Color* color);
		void SetWidth(int width);
		void SetHeight(int height);
		void SetState(bool state);

		// Utility methods 
		bool IsChecked(); 

	private:
		int width, height; 
		bool checked; 
		std::string label; 
		SDL_Color checkmarkColor, labelColor, hoverColor; 
};

class Slider : public Controls {
	public:
		Slider(std::string label, int x, int y, int width, int height, int thumbWidth, int thumbHeight, int fontSize, std::string fontPath);

		// GET methods  
		std::string GetLabel();
		SDL_Color GetHoverColor();
		SDL_Color GetLabelColor();
		SDL_Color GetThumbColor();
		int GetWidth();
		int GetHeight();
		int GetThumbWidth();
		int GetThumbHeight();
		int Getvalue();	// Should return a value from 0 to 100 based on slider thumb position relative to slider bar length

		// SET methods 
		void SetLabel(std::string label);
		void SetHoverColor(SDL_Color* color);
		void SetLabelColor(SDL_Color* color); 
		void SetThumbColor(SDL_Color* color);
		void SetWidth(int width);
		void SetHeight(int height);
		int SetThumbWidth(int width);
		int SetThumbHeight(int height);
		void SetValue(int value); 
	
	private:
		int width, height, value, thumbWidth, thumbHeight;
		std::string label;
		SDL_Color labelColor, hoverColor, thumbColor;
};

