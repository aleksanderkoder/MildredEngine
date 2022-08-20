#include "Page.h"

Page::Page() {
	this->buttons = new std::vector<Button*>(); 
	this->labels = new std::vector<Label*>();
	this->checkboxes = new std::vector<Checkbox*>();
	this->textboxes = new std::vector<Textbox*>();
}

void Page::Add(Button* button) {
	this->buttons->push_back(button); 
}

void Page::Add(Label* label) {
	this->labels->push_back(label);
}

void Page::Add(Checkbox* checkbox) {
	this->checkboxes->push_back(checkbox);
}

void Page::Add(Textbox* textbox) {
	this->textboxes->push_back(textbox); 
}

void Page::Remove(Button* button) {	// TODO: Implement these!

}
void Page::Remove(Label* label) {

}
void Page::Remove(Checkbox* checkbox) {

}

void Page::Remove(Textbox* textbox) {

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