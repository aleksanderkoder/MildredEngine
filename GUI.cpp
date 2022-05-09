#include "GUI.h"

vector<Button*>* GUI::buttons = new vector<Button*>(); 
SDL_Renderer* GUI::targetRenderer;
Uint32 GUI::mouseButtons = NULL; 

void GUI::SetRenderTarget(SDL_Renderer* r) {
	targetRenderer = r; 
}

Button* GUI::CreateButton(string label, int width, int height, int x, int y) {
	Button* b = new Button(label, width, height, x, y);
	buttons->push_back(b);
	return b; 
}

void GUI::Render() {
	// Loop through all buttons
	for (int i = 0; i < buttons->size(); i++) {
		Button* curr = (*buttons)[i];

		// Create button rectangle data
		SDL_Rect rect;
		rect.w = curr->width;
		rect.h = curr->height;
		rect.x = curr->x;
		rect.y = curr->y;

		// If mouse hovers over button and activates
		if (OnButtonHover(curr) && mouseButtons == SDL_BUTTON(1)) {
			SDL_SetRenderDrawColor(targetRenderer, curr->hoverColor.r, curr->hoverColor.g, curr->hoverColor.b, curr->hoverColor.a - 75);
			curr->Invoke();
		}
		// If mouse hovers over
		else if (OnButtonHover(curr)) {
			SDL_SetRenderDrawColor(targetRenderer, curr->hoverColor.r, curr->hoverColor.g, curr->hoverColor.b, curr->hoverColor.a);
		}
		// If mouse doesn't hover over button
		else {
			SDL_SetRenderDrawColor(targetRenderer, curr->color.r, curr->color.g, curr->color.b, curr->color.a);
		}

		// Draw button rectangle
		SDL_RenderFillRect(targetRenderer, &rect);

		SDL_Color c = { 255, 255, 255 };

		// Display button label
		Mildred::DisplayText(curr->label, 12, curr->x + curr->width / 2 - 3 * curr->label.length(), curr->y + curr->height / 2 - 12, c);
	}
}

bool GUI::OnButtonHover(Button* b) {
	int mX = 0, mY = 0;
	if (mouseButtons == NULL) {
		mouseButtons = SDL_GetMouseState(&mX, &mY);
	}
	else {
		mouseButtons = NULL; 
	}

		// If mouse hovers over button
		if (mX >= b->x && mX <= b->x + b->width && mY >= b->y && mY <= b->y + b->height) {
			return true; 
		}
		return false; 
}
