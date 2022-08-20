#include "Page.h"

Page::Page() {
	this->buttons = new std::vector<Button*>(); 
	this->labels = new std::vector<Label*>();
	this->checkboxes = new std::vector<Checkbox*>();
	this->textboxes = new std::vector<Textbox*>();
}

void Page::AddElement(Button* button) {
	this->buttons->push_back(button); 
}

void Page::AddElement(Label* label) {
	this->labels->push_back(label);
}

void Page::AddElement(Checkbox* checkbox) {
	this->checkboxes->push_back(checkbox);
}

void Page::AddElement(Textbox* textbox) {
	this->textboxes->push_back(textbox); 
}

void Page::RemoveElement(Button* button) {	// TODO: Implement these!

}
void Page::RemoveElement(Label* label) {

}
void Page::RemoveElement(Checkbox* checkbox) {

}

void Page::RemoveElement(Textbox* textbox) {

}

std::vector<Button*>* Page::GetButtons() {
	return this->buttons; 
}

std::vector<Label*>* Page::GetLabels() {
	return this->labels; 
}

std::vector<Checkbox*>* Page::GetCheckboxes() {
	return this->checkboxes; 
}

std::vector<Textbox*>* Page::GetTextboxes() {
	return this->textboxes; 
}