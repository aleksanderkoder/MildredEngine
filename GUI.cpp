#include "GUI.h"

vector<Button*>* GUI::buttons = new vector<Button*>(); 
vector<Textbox*>* GUI::textboxes = new vector<Textbox*>();
SDL_Renderer* GUI::targetRenderer;
Uint32 GUI::delta; 
string GUI::currentFont;
Textbox* GUI::activeTextbox = NULL; 
char GUI::lastPressedKey;
bool GUI::leftMouseButtonPressedState = false, GUI::leftMouseButtonPressedLastState = false;

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

		bool mHover = OnMouseHover(curr->x, curr->y, curr->width, curr->height);

		// If mouse doesn't hover over button, default idle state
		SDL_SetRenderDrawColor(targetRenderer, curr->color.r, curr->color.g, curr->color.b, curr->color.a);

		// If mouse hovers over button and activates
		if (mHover && leftMouseButtonPressedState) {
			SDL_SetRenderDrawColor(targetRenderer, curr->hoverColor.r, curr->hoverColor.g, curr->hoverColor.b, curr->hoverColor.a - 75);
			curr->Invoke();
			activeTextbox = NULL;
		}
		// If mouse hovers over
		else if (mHover) {
			if (!leftMouseButtonPressedLastState)
				SDL_SetRenderDrawColor(targetRenderer, curr->hoverColor.r, curr->hoverColor.g, curr->hoverColor.b, curr->hoverColor.a);
			else 
				SDL_SetRenderDrawColor(targetRenderer, curr->hoverColor.r, curr->hoverColor.g, curr->hoverColor.b, curr->hoverColor.a - 75);
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

		bool mHover = OnMouseHover(curr->x, curr->y, curr->width, curr->height);

		// If mouse doesn't hover over textbox, default idle state
		SDL_SetRenderDrawColor(targetRenderer, curr->color.r, curr->color.g, curr->color.b, curr->color.a);

		// If mouse hovers over textbox and activates
		if (mHover && leftMouseButtonPressedState) {
			SDL_SetRenderDrawColor(targetRenderer, curr->hoverColor.r, curr->hoverColor.g, curr->hoverColor.b, curr->hoverColor.a - 75);
			activeTextbox = curr; 
		}
		// If mouse hovers over
		else if (mHover) {
			if (!leftMouseButtonPressedLastState)
				SDL_SetRenderDrawColor(targetRenderer, curr->hoverColor.r, curr->hoverColor.g, curr->hoverColor.b, curr->hoverColor.a);
			else
				SDL_SetRenderDrawColor(targetRenderer, curr->hoverColor.r, curr->hoverColor.g, curr->hoverColor.b, curr->hoverColor.a - 75);
		}
		// If mouse clicks outside textbox area
		//else if (!OnTextboxHover(curr) && mouseButtonsForTextboxes == SDL_BUTTON(1)) {
		//	//activeTextbox = NULL; 
		//}
		
		// Draw textbox rectangle
		SDL_RenderFillRect(targetRenderer, &rect);
		
		SDL_Color c = { 255, 255, 255 };
		TTF_Font* font = OpenFont(currentFont, curr->fontSize);

		// If textbox has a user entered value, show that value in textbox
		if (curr->value.empty()) {
			int* mesDim = GetTextDimensions(curr->placeholder, font);
			
			// Display textbox label
			CreateLabel(curr->placeholder, curr->x + curr->width / 2 - mesDim[0] / 2, curr->y + curr->height / 2 - mesDim[1] / 2, c, curr->fontSize);
			TTF_CloseFont(font);
		}
		// If no value, show placeholder
		else {
			int* mesDim = GetTextDimensions(curr->value, font);

			// Display textbox label
			CreateLabel(curr->value, curr->x + curr->width / 2 - mesDim[0] / 2, curr->y + curr->height / 2 - mesDim[1] / 2, c, curr->fontSize);
			TTF_CloseFont(font);
		}

		
	} 
	CaptureInputText(); 
}

void GUI::CaptureInputText() {
	if (!activeTextbox) return; 

	int nk;
	char key = NULL; 
	Uint32 now = SDL_GetTicks(); 
	const Uint8* keys = SDL_GetKeyboardState(&nk);

	if (keys[SDL_SCANCODE_BACKSPACE] && DeltaTimeHasPassed(120)) {
		activeTextbox->value = activeTextbox->value.substr(0, activeTextbox->value.size() - 1);
		UpdateDelta(now);
		return; 
	}

	for (int i = 0; i < nk; i++) {
		if (keys[i]) {
			if (i >= 4 && i <= 39 || i == 44) {
				if (keys[SDL_SCANCODE_LSHIFT]) {
					key = toupper(SDL_GetKeyFromScancode(SDL_Scancode(i)));
				}
				else {
					key = SDL_GetKeyFromScancode(SDL_Scancode(i));
				}
			}
		}
	}
	// If pressed key is not the same as last key, then just print immediately 
	if (key != lastPressedKey && key) {
		activeTextbox->value += key; 
		lastPressedKey = key;
		UpdateDelta(now);
	}
	// If same key, check if enough time has passed since last key press. 
	// If enough time has passed, print pressed key
	else if (DeltaTimeHasPassed(200) && key) {
		activeTextbox->value += key;
		lastPressedKey = key;
		UpdateDelta(now);
	}
}

void GUI::Render() {
	UpdateMouseButtonState(); 
	RenderTextboxes(); 
	RenderButtons();
}

bool GUI::OnMouseHover(int x, int y, int width, int height) {
	int mX = 0, mY = 0;
	SDL_GetMouseState(&mX, &mY);

	// If mouse hovers over button
	if (mX >= x && mX <= x + width && mY >= y && mY <= y + height) {
		return true;
	}
	return false;
}

void GUI::UpdateMouseButtonState() {
	Uint32 mb = SDL_GetMouseState(NULL, NULL);
	if (mb == SDL_BUTTON(1) && !leftMouseButtonPressedLastState) {
		leftMouseButtonPressedLastState = true; 
		leftMouseButtonPressedState = true; 
	}
	else if (mb == SDL_BUTTON(1) && leftMouseButtonPressedLastState) {
		leftMouseButtonPressedState = false; 
	}
	else if (mb != SDL_BUTTON(1)) {
		leftMouseButtonPressedLastState = false; 
		leftMouseButtonPressedState = false;
	}
	
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
	
	delta = SDL_GetTicks(); // Init milliseconds to be used for textbox input 

	// Sets default font
	currentFont = "fonts/arial.ttf";
}

Textbox* GUI::CreateTextbox(string placeholder, int width, int height, int x, int y, int fontSize) {
	Textbox* tb = new Textbox(placeholder, width, height, x, y, fontSize);
	textboxes->push_back(tb); 
	return tb; 
}

bool GUI::DeltaTimeHasPassed(int ms) {
	Uint32 now = SDL_GetTicks();
	if (now - delta >= ms) {
		return true;
	}
	return false; 
}

void GUI::UpdateDelta(Uint32 now) {
	delta = now; 
}