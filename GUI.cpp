#include "GUI.h"

vector<Button*>* GUI::buttons = new vector<Button*>(); 
vector<Textbox*>* GUI::textboxes = new vector<Textbox*>();
SDL_Renderer* GUI::targetRenderer;
Uint32 GUI::mouseButtonsForButtons = NULL, GUI::mouseButtonsForTextboxes = NULL;
string GUI::currentFont;
Textbox* GUI::activeTextbox = NULL; 

void GUI::SetRenderTarget(SDL_Renderer* r) {
	targetRenderer = r; 
}

void GUI::CreateLabel(string msg, int xpos, int ypos, SDL_Color color, int fontSize) {

	TTF_Font* font = OpenFont(currentFont, fontSize);

	// Create surface to render text on
	SDL_Surface* surfaceMessage =
		TTF_RenderText_Blended(font, msg.c_str(), color);

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
	TTF_CloseFont(font); 
}

int* GUI::GetTextDimensions(string text, TTF_Font* font) {
	// Text color
	SDL_Color color = { 0, 0, 0 };

	// Create surface to render text on
	SDL_Surface* surfaceMessage =
		TTF_RenderText_Blended(font, text.c_str(), color);

	static int dim[2];
	dim[0] = surfaceMessage->w;
	dim[1] = surfaceMessage->h;

	SDL_FreeSurface(surfaceMessage);
	return dim; 
}

Button* GUI::CreateButton(string label, int width, int height, int x, int y, int fontSize) {
	Button* b = new Button(label, width, height, x, y, fontSize);
	buttons->push_back(b);
	return b; 
}

void GUI::RenderButtons() {
	// Loop through all buttons
	for (int i = 0; i < buttons->size(); i++) {
		Button* curr = (*buttons)[i];

		// Create button rectangle data
		SDL_Rect rect;
		rect.w = curr->width;
		rect.h = curr->height;
		rect.x = curr->x;
		rect.y = curr->y;

		// If mouse doesn't hover over button, default idle state
		SDL_SetRenderDrawColor(targetRenderer, curr->color.r, curr->color.g, curr->color.b, curr->color.a);

		// If mouse hovers over button and activates
		if (OnButtonHover(curr) && mouseButtonsForButtons == SDL_BUTTON(1)) {
			SDL_SetRenderDrawColor(targetRenderer, curr->hoverColor.r, curr->hoverColor.g, curr->hoverColor.b, curr->hoverColor.a - 75);
			curr->Invoke();
			activeTextbox = NULL;
		}
		// If mouse hovers over
		else if (OnButtonHover(curr)) {
			SDL_SetRenderDrawColor(targetRenderer, curr->hoverColor.r, curr->hoverColor.g, curr->hoverColor.b, curr->hoverColor.a);
		}

		// Draw button rectangle
		SDL_RenderFillRect(targetRenderer, &rect);

		SDL_Color c = { 255, 255, 255 };

		TTF_Font* font = OpenFont(currentFont, curr->fontSize); 
		int* mesDim = GetTextDimensions(curr->label, font); 

		// Display button label
		CreateLabel(curr->label, curr->x + curr->width / 2 - mesDim[0] / 2, curr->y + curr->height / 2 - mesDim[1] / 2, c, curr->fontSize);
		TTF_CloseFont(font);
	}
}

void GUI::RenderTextboxes() {
	// Loop through all textboxes
	for (int i = 0; i < textboxes->size(); i++) {
		Textbox* curr = (*textboxes)[i];

		// Create textbox rectangle data
		SDL_Rect rect;
		rect.w = curr->width;
		rect.h = curr->height;
		rect.x = curr->x;
		rect.y = curr->y;

		// If mouse doesn't hover over textbox, default idle state
		SDL_SetRenderDrawColor(targetRenderer, curr->color.r, curr->color.g, curr->color.b, curr->color.a);

		// If mouse hovers over textbox and activates
		if (OnTextboxHover(curr) && mouseButtonsForTextboxes == SDL_BUTTON(1)) {
			SDL_SetRenderDrawColor(targetRenderer, curr->hoverColor.r, curr->hoverColor.g, curr->hoverColor.b, curr->hoverColor.a - 75);
			activeTextbox = curr; 
		}
		// If mouse hovers over
		else if (OnTextboxHover(curr)) {
			SDL_SetRenderDrawColor(targetRenderer, curr->hoverColor.r, curr->hoverColor.g, curr->hoverColor.b, curr->hoverColor.a);
		}
		// If mouse clicks outside textbox area
		else if (!OnTextboxHover(curr) && mouseButtonsForTextboxes == SDL_BUTTON(1)) {
			//activeTextbox = NULL; 
		}
		
		// Draw textbox rectangle
		SDL_RenderFillRect(targetRenderer, &rect);

		SDL_Color c = { 255, 255, 255 };

		TTF_Font* font = OpenFont(currentFont, curr->fontSize);
		int* mesDim = GetTextDimensions(curr->placeholder, font);

		// Display textbox label
		CreateLabel(curr->placeholder, curr->x + curr->width / 2 - mesDim[0] / 2, curr->y + curr->height / 2 - mesDim[1] / 2, c, curr->fontSize);
		TTF_CloseFont(font);
	} 
	CaptureInputText(); 
}

void GUI::CaptureInputText() {
	if (!activeTextbox) return; 

	int nk;
	const Uint8* keys = SDL_GetKeyboardState(&nk);
	for (int i = 0; i < nk; i++) {
		if (keys[i])
			activeTextbox->value += SDL_GetKeyFromScancode(SDL_Scancode(i));
	}
	//SDL_Event e;
	//while (SDL_PollEvent(&e))
	//{
	//	if (SDL_KEYDOWN) {
	//		activeTextbox->value += e.key; 
	//	}
	//	/*if (e.type == SDL_TEXTINPUT || e.type == SDL_KEYDOWN) {
	//		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && activeTextbox->value.length() > 0)
	//			activeTextbox->value = activeTextbox->value.substr(0, activeTextbox->value.length() - 1);
	//		else if (e.type == SDL_TEXTINPUT)
	//			activeTextbox->value += e.text.text; 
	//	}*/
	//}
	//cout << activeTextbox->value << endl;
}

void GUI::Render() {
	RenderTextboxes(); 
	RenderButtons();
}

bool GUI::OnButtonHover(Button* b) {
	int mX = 0, mY = 0;
	if (mouseButtonsForButtons == NULL) {
		mouseButtonsForButtons = SDL_GetMouseState(&mX, &mY);
	}
	else {
		mouseButtonsForButtons = NULL;
	}

	// If mouse hovers over button
	if (mX >= b->x && mX <= b->x + b->width && mY >= b->y && mY <= b->y + b->height) {
		return true; 
	}
	return false; 
}

bool GUI::OnTextboxHover(Textbox* tb) {
	int mX = 0, mY = 0;
	if (mouseButtonsForTextboxes == NULL) {
		mouseButtonsForTextboxes = SDL_GetMouseState(&mX, &mY);
	}
	else {
		mouseButtonsForTextboxes = NULL;
	}

	// If mouse hovers over button
	if (mX >= tb->x && mX <= tb->x + tb->width && mY >= tb->y && mY <= tb->y + tb->height) {
		return true;
	}
	return false;
}

TTF_Font* GUI::OpenFont(string fontUrl, int size) {
	TTF_Font* font = TTF_OpenFont(fontUrl.c_str(), size);
	if (!font) {
		char t[] = "Font error";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, t, TTF_GetError(), NULL);
		exit(0);
	}
	return font; 
}

void GUI::SetFont(string fontPath) {
	currentFont = fontPath; 
}

void GUI::Init() {
	TTF_Init();	// Initializes the SDL font library

	// Sets default font
	currentFont = "fonts/arial.ttf";
}

Textbox* GUI::CreateTextbox(string placeholder, int width, int height, int x, int y, int fontSize) {
	Textbox* tb = new Textbox(placeholder, width, height, x, y, fontSize);
	textboxes->push_back(tb); 
	return tb; 
}