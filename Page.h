#pragma once
#include "elements.h"
#include <vector>

class Page
{
	private: 
		std::vector<Button*>* buttons; 
		std::vector<Label*>* labels;
		std::vector<Checkbox*>* checkboxes;
		std::vector<Textbox*>* textboxes;

	public: 
		Page(); 

		void Add(Button* button); 
		void Add(Label* label);
		void Add(Checkbox* checkbox);
		void Add(Textbox* textbox);

		void Remove(Button* button);
		void Remove(Label* label);
		void Remove(Checkbox* checkbox);
		void Remove(Textbox* textbox);

		std::vector<Button*>* GetButtons(); 
		std::vector<Label*>* GetLabels();
		std::vector<Checkbox*>* GetCheckboxes();
		std::vector<Textbox*>* GetTextboxes();

};

