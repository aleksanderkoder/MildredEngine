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
	CheckForHover(); 
	for (int i = 0; i < buttons->size(); i++) {
		Button* curr = (*buttons)[i];
		SDL_Rect rect;
		rect.w = curr->width;
		rect.h = curr->height;
		rect.x = curr->x;
		rect.y = curr->y;

		SDL_SetRenderDrawColor(targetRenderer, curr->renderColor.r, curr->renderColor.g, curr->renderColor.b, curr->renderColor.a);
		SDL_RenderFillRect(targetRenderer, &rect);

		SDL_Color c = { 255, 255, 255 };
		Mildred::DisplayText(curr->label, 12, curr->x + curr->width / 2 - 3 * curr->label.length(), curr->y + curr->height / 2 - 12, c);
	}
}

void GUI::CheckForHover() {
	int mX, mY;
	SDL_GetMouseState(&mX, &mY);

	for (int i = 0; i < buttons->size(); i++) {
		Button* curr = (*buttons)[i];

		// If mouse hovers over button
		if (mX >= curr->x && mX <= curr->x + curr->width && mY >= curr->y && mY <= curr->y + curr->height) {
			SDL_Color c = { 255, 0, 0, 175 }; 
			curr->renderColor = c;
		}
		else {
			SDL_Color c = { 255, 0, 0, 175 };
			curr->renderColor = curr->originalColor;
		}
		
	}
}