#include "GUI.h"

vector<Button*>* GUI::buttons = new vector<Button*>(); 
vector<Textbox*>* GUI::textboxes = new vector<Textbox*>();
vector<Label*>* GUI::labels = new vector<Label*>();
SDL_Renderer* GUI::targetRenderer;
Uint32 GUI::delta, GUI::textboxCursorDelta;
string GUI::currentFont;
Textbox* GUI::activeTextbox = NULL; 
char GUI::lastPressedKey;
bool GUI::leftMouseButtonPressedState = false, GUI::leftMouseButtonPressedLastState = false,
GUI::drawTextBoxCursor = true, GUI::capsLockEnabled = false;

void GUI::SetRenderTarget(SDL_Renderer* r) {
	targetRenderer = r; 
}

Label* GUI::CreateLabel(string text, int x, int y, SDL_Color color, int fontSize) {
	Label* lbl = new Label(text, x, y, color, fontSize);
	labels->push_back(lbl);
	return lbl;
}

void GUI::RenderLabels() {
	for (int i = 0; i < labels->size(); i++) {
		Label* curr = (*labels)[i];
			
		RenderLabel(curr->text, curr->x, curr->y, curr->color, curr->fontSize);
	}
}

void GUI::RenderLabel(string text, int x, int y, SDL_Color color, int fontSize) {

	TTF_Font* font = OpenFont(currentFont, fontSize);

	// Create surface to render text on
	SDL_Surface* surfaceMessage =
		TTF_RenderText_Blended(font, text.c_str(), color);

	// Convert to texture
	SDL_Texture* Message = SDL_CreateTextureFromSurface(targetRenderer, surfaceMessage);

	// Create a rectangle/shape of the message texture
	SDL_Rect Message_rect;
	Message_rect.x = x;
	Message_rect.y = y;
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
		RenderLabel(curr->label, curr->x + curr->width / 2 - mesDim[0] / 2, curr->y + curr->height / 2 - mesDim[1] / 2, c, curr->fontSize);
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
			SDL_SetRenderDrawColor(targetRenderer, curr->hoverColor.r, curr->hoverColor.g, curr->hoverColor.b, curr->hoverColor.a);
			activeTextbox = curr; 
		}
		// If mouse hovers over
		else if (mHover) {
			SDL_SetRenderDrawColor(targetRenderer, curr->hoverColor.r, curr->hoverColor.g, curr->hoverColor.b, curr->hoverColor.a);
		}
		
		// Draw textbox rectangle
		SDL_RenderFillRect(targetRenderer, &rect);
		
		TTF_Font* font = OpenFont(currentFont, curr->fontSize);
		int* txtDim; 
		int lblX, lblY; 

		// If no value, show placeholder
		if (curr->value.empty()) {
			SDL_Color c = { 255, 255, 255, 150 };
			txtDim = GetTextDimensions(curr->placeholder, font);
			lblX = curr->x + curr->width / 2 - txtDim[0] / 2;
			lblY = curr->y + curr->height / 2 - txtDim[1] / 2;
			
			// Display textbox label
			RenderLabel(curr->placeholder, lblX, lblY, c, curr->fontSize);
			TTF_CloseFont(font);
		}
		// If textbox has a user entered value, show that value in textbox
		else {
			SDL_Color c = { 255, 255, 255 };
			txtDim = GetTextDimensions(curr->value, font);
			lblX = curr->x + curr->width / 2 - txtDim[0] / 2;
			lblY = curr->y + curr->height / 2 - txtDim[1] / 2; 

			// Display textbox label
			RenderLabel(curr->value, lblX, lblY, c, curr->fontSize);
			TTF_CloseFont(font);
		}

		// If there's an active textbox, toggle textbox cursor every second
		if (activeTextbox) {
			Uint32 now = SDL_GetTicks();
			Uint32 cursorDelta = now - textboxCursorDelta;
			if (cursorDelta > 1000) {
				if (drawTextBoxCursor) {
					drawTextBoxCursor = false;
				}
				else {
					drawTextBoxCursor = true; 
				}
				textboxCursorDelta = now;
			}
		}

		if (activeTextbox == curr && drawTextBoxCursor)
		{
			SDL_Rect rect;
			rect.w = 2;
			rect.h = curr->fontSize;
			rect.x = lblX + txtDim[0];
			rect.y = lblY + curr->fontSize / 4;
			SDL_SetRenderDrawColor(targetRenderer, 255, 255, 255, 255);
			SDL_RenderFillRect(targetRenderer, &rect);
		}
	} 
	CaptureInputText(); 
}

void GUI::CaptureInputText() {
	if (!activeTextbox) return; 

	int nK;
	char key = NULL; 
	Uint32 now = SDL_GetTicks(); 
	const Uint8* keys = SDL_GetKeyboardState(&nK);

	// Enable capital letters if capslock is pressed
	if (keys[SDL_SCANCODE_CAPSLOCK] && DeltaTimeHasPassed(300)) {
		if (capsLockEnabled)
			capsLockEnabled = false;
		else
			capsLockEnabled = true;
		UpdateDelta(now); 
	}

	// Delete last character from input string if backspace is pressed
	if (keys[SDL_SCANCODE_BACKSPACE] && DeltaTimeHasPassed(110)) {
		activeTextbox->value = activeTextbox->value.substr(0, activeTextbox->value.size() - 1);
		UpdateDelta(now);
		return; 
	}

	for (int i = 0; i < nK; i++) {
		if (keys[i]) {
			if (ValidKey(i)) {
				if (keys[SDL_SCANCODE_LSHIFT] || capsLockEnabled) {
					key = toupper(SDL_GetKeyFromScancode(SDL_Scancode(i)));
				}
				else {
					key = SDL_GetKeyFromScancode(SDL_Scancode(i));
				}
				// Reset textbox cursor on key input
				textboxCursorDelta = now;
				drawTextBoxCursor = true; 
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

bool GUI::ValidKey(int key) {
	// Determines what keys are considered valid (valid as in printable)
	if (key >= 4 && key <= 39 || key >= 44 && key <= 49 || key >= 54 && key <= 56) {
		return true;
	}
	return false;
}

void GUI::Render() {
	UpdateMouseButtonState(); 
	RenderTextboxes(); 
	RenderButtons();
	RenderLabels();
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
	textboxCursorDelta = SDL_GetTicks(); // Init milliseconds to be used for textbox cursor blinking 

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