#include "GUI.h"

vector<Button*>* GUI::buttons = new vector<Button*>(); 
SDL_Renderer* GUI::targetRenderer;
Uint32 GUI::mouseButtons = NULL; 
TTF_Font* GUI::currentFont;
int GUI::fontSize = 12; 

void GUI::SetRenderTarget(SDL_Renderer* r) {
	targetRenderer = r; 
	TTF_Init(); // Initilize SDL_ttf
}

void GUI::DisplayText(string msg, int xpos, int ypos, SDL_Color color, int fontSize) {

	// Create surface to render text on
	SDL_Surface* surfaceMessage =
		TTF_RenderText_Blended(currentFont, msg.c_str(), color);

	// Convert to texture
	SDL_Texture* Message = SDL_CreateTextureFromSurface(targetRenderer, surfaceMessage);

	// Create a rectangle/shape of the message texture
	SDL_Rect Message_rect;
	Message_rect.x = xpos;
	Message_rect.y = ypos;
	Message_rect.w = surfaceMessage->w;
	Message_rect.h = surfaceMessage->h;

	SDL_RenderCopy(targetRenderer, Message, NULL, &Message_rect);

	// Frees resources 
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

int* GUI::GetTextDimensions(string text, int fontSize) {
	// Text color
	SDL_Color color = { 0, 0, 0 };

	// Create surface to render text on
	SDL_Surface* surfaceMessage =
		TTF_RenderText_Blended(currentFont, text.c_str(), color);

	int dim[2];
	dim[0] = surfaceMessage->w;
	dim[1] = surfaceMessage->h;

	SDL_FreeSurface(surfaceMessage);
	return dim; 
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

		int* mesDim = GetTextDimensions(curr->label, 12); 

		// Display button label
		DisplayText(curr->label, curr->x + curr->width / 2 - mesDim[0] / 2, curr->y + curr->height / 2 - mesDim[1] / 2, c);
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

void GUI::SetFont(string fontUrl, int size) {
	currentFont = TTF_OpenFont(fontUrl.c_str(), size);
	if (!currentFont) {
		string t = "Font error"; 
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, t.c_str(), TTF_GetError(), NULL);
		exit(0);
	}
	fontSize = size; 
}

void GUI::Init() {
	TTF_Init(); 
}