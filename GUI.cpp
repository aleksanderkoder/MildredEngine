#include "GUI.h"

vector<Button*>* GUI::buttons = new vector<Button*>(); 
SDL_Renderer* GUI::targetRenderer;

void GUI::SetRenderTarget(SDL_Renderer* r) {
	targetRenderer = r; 
}

void GUI::CreateButton(string label, int width, int height, int x, int y) {
	Button* b = new Button(label, width, height, x, y);
	buttons->push_back(b);

}

void GUI::Render() {
	for (int i = 0; i < buttons->size(); i++) {
		SDL_Rect rect;
		rect.w = (*buttons)[i]->width;
		rect.h = (*buttons)[i]->height;
		rect.x = (*buttons)[i]->x;
		rect.y = (*buttons)[i]->y;
		SDL_SetRenderDrawColor(targetRenderer, 255, 255, 255, 255); 
		SDL_RenderFillRect(targetRenderer, &rect);
		SDL_Color c = { 0, 0, 0 };
		Mildred::DisplayText((*buttons)[i]->label, 12, (*buttons)[i]->x, (*buttons)[i]->y, c); 
	}
}