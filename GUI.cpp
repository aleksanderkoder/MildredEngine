#include "GUI.h"

std::vector<Button*>* GUI::buttons = new std::vector<Button*>();
std::vector<Textbox*>* GUI::textboxes = new std::vector<Textbox*>();
std::vector<Label*>* GUI::labels = new std::vector<Label*>();
SDL_Renderer* GUI::targetRenderer;
Uint32 GUI::delta, GUI::textboxCursorDelta;
std::string GUI::currentFont;
Textbox* GUI::activeTextbox = NULL; 
char GUI::lastPressedKey;
bool GUI::leftMouseButtonPressedState = false, GUI::leftMouseButtonPressedLastState = false,
GUI::drawTextBoxCursor = true, GUI::capsLockEnabled = false;

void GUI::SetRenderTarget(SDL_Renderer* r) {
	targetRenderer = r; 
}

Label* GUI::CreateLabel(std::string text, int x, int y, SDL_Color color, int fontSize) {
	Label* lbl = new Label(text, x, y, color, fontSize);
	labels->push_back(lbl);
	return lbl;
}

void GUI::RenderLabels() {
	for (int i = 0; i < labels->size(); i++) {
		Label* curr = (*labels)[i];
			
		RenderLabel(curr->GetText(), curr->GetX(), curr->GetY(), curr->GetColor(), curr->GetFontSize());
	}
}

void GUI::RenderLabel(std::string text, int x, int y, SDL_Color color, int fontSize) {

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

std::tuple<int, int> GUI::GetTextDimensions(std::string text, TTF_Font* font) {
	// Text color
	SDL_Color color = { 0, 0, 0 };

	// Create surface to render text on
	SDL_Surface* surfaceMessage =
		TTF_RenderText_Blended(font, text.c_str(), color);

	std::tuple<int, int> dim(surfaceMessage->w, surfaceMessage->h);

	SDL_FreeSurface(surfaceMessage);
	return dim; 
}

Button* GUI::CreateButton(std::string label, int width, int height, int x, int y, int fontSize) {
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
		rect.w = curr->GetWidth();
		rect.h = curr->GetHeight();
		rect.x = curr->GetX();
		rect.y = curr->GetY();

		bool mHover = OnMouseHover(curr->GetX(), curr->GetY(), curr->GetWidth(), curr->GetHeight());

		// If mouse doesn't hover over button, default idle state
		SDL_SetRenderDrawColor(targetRenderer, curr->GetColor().r, curr->GetColor().g, curr->GetColor().b, curr->GetColor().a);

		// If mouse hovers over button and activates
		if (mHover && leftMouseButtonPressedState) {
			curr->Invoke();
			SDL_SetRenderDrawColor(targetRenderer, curr->GetHoverColor().r, curr->GetHoverColor().g, curr->GetHoverColor().b, curr->GetHoverColor().a - 75);
			activeTextbox = NULL;
		}
		// If mouse hovers over
		else if (mHover) {
			if (!leftMouseButtonPressedLastState)
				SDL_SetRenderDrawColor(targetRenderer, curr->GetHoverColor().r, curr->GetHoverColor().g, curr->GetHoverColor().b, curr->GetHoverColor().a);
			else 
				SDL_SetRenderDrawColor(targetRenderer, curr->GetHoverColor().r, curr->GetHoverColor().g, curr->GetHoverColor().b, curr->GetHoverColor().a - 75);
		}

		// Draw button rectangle
		SDL_RenderFillRect(targetRenderer, &rect);

		SDL_Color c = { 255, 255, 255 };
		TTF_Font* font = OpenFont(currentFont, curr->GetFontSize()); 
		std::tuple<int, int> mesDim = GetTextDimensions(curr->GetLabel(), font);

		// Display button label
		RenderLabel(curr->GetLabel(), curr->GetX() + curr->GetWidth() / 2 - std::get<0>(mesDim) / 2, curr->GetY() + curr->GetHeight() / 2 - std::get<1>(mesDim) / 2, c, curr->GetFontSize());
		TTF_CloseFont(font);
	}
}

void GUI::RenderTextboxes() {
	// Loop through all textboxes
	for (int i = 0; i < textboxes->size(); i++) {
		Textbox* curr = (*textboxes)[i];

		// Create textbox rectangle data
		SDL_Rect rect;
		rect.w = curr->GetWidth();
		rect.h = curr->GetHeight();
		rect.x = curr->GetX();
		rect.y = curr->GetY();

		bool mHover = OnMouseHover(curr->GetX(), curr->GetY(), curr->GetWidth(), curr->GetHeight());

		// If mouse doesn't hover over textbox, default idle state
		SDL_SetRenderDrawColor(targetRenderer, curr->GetColor().r, curr->GetColor().g, curr->GetColor().b, curr->GetColor().a);

		// If mouse hovers over textbox and activates
		if (mHover && leftMouseButtonPressedState) {
			SDL_SetRenderDrawColor(targetRenderer, curr->GetHoverColor().r, curr->GetHoverColor().g, curr->GetHoverColor().b, curr->GetHoverColor().a);
			activeTextbox = curr; 
		}
		// If mouse hovers over
		else if (mHover) {
			SDL_SetRenderDrawColor(targetRenderer, curr->GetHoverColor().r, curr->GetHoverColor().g, curr->GetHoverColor().b, curr->GetHoverColor().a);
		}
		
		// Draw textbox rectangle
		SDL_RenderFillRect(targetRenderer, &rect);
		
		TTF_Font* font = OpenFont(currentFont, curr->GetFontSize());
		std::tuple<int, int> txtDim;
		int lblX, lblY; 

		// If no value, show placeholder
		if (curr->GetValue().empty()) {
			SDL_Color c = { 255, 255, 255, 150 };
			txtDim = GetTextDimensions(curr->GetPlaceholder(), font);
			lblX = curr->GetX() + curr->GetWidth() / 2 - std::get<0>(txtDim) / 2;
			lblY = curr->GetY() + curr->GetHeight() / 2 - std::get<1>(txtDim) / 2;
			
			// Display textbox label
			RenderLabel(curr->GetPlaceholder(), lblX, lblY, c, curr->GetFontSize());
			TTF_CloseFont(font);
		}
		// If textbox has a user entered value, show that value in textbox
		else {
			SDL_Color c = { 255, 255, 255 };
			txtDim = GetTextDimensions(curr->GetValue(), font);
			lblX = curr->GetX() + curr->GetWidth() / 2 - std::get<0>(txtDim) / 2;
			lblY = curr->GetY() + curr->GetHeight() / 2 - std::get<1>(txtDim) / 2;

			// Display textbox label
			RenderLabel(curr->GetValue(), lblX, lblY, c, curr->GetFontSize());
			TTF_CloseFont(font);
		}

		// If there's an active textbox, toggle textbox cursor every 750 millisecond
		if (activeTextbox) {
			Uint32 now = SDL_GetTicks();
			Uint32 cursorDelta = now - textboxCursorDelta;
			if (cursorDelta > 750) {
				drawTextBoxCursor = !drawTextBoxCursor; 
				textboxCursorDelta = now;
			}
		}
		// If active textbox is the current textbox and timing is right, draw cursor on textbox
		if (activeTextbox == curr && drawTextBoxCursor)
		{
			SDL_Rect cursorRect;
			cursorRect.w = 2;
			cursorRect.h = curr->GetFontSize();
			cursorRect.x = lblX + std::get<0>(txtDim);
			cursorRect.y = lblY + curr->GetFontSize() / 4;
			SDL_SetRenderDrawColor(targetRenderer, 255, 255, 255, 255);
			SDL_RenderFillRect(targetRenderer, &cursorRect);
		}
		CaptureInputText(); 
	} 
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
		activeTextbox->SetValue(activeTextbox->GetValue().substr(0, activeTextbox->GetValue().size() - 1));
		UpdateDelta(now);
		return; 
	}

	// If character limit has been reached, jump out 
	if (activeTextbox->GetValue().length() >= activeTextbox->GetCharLimit()) return;

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
		activeTextbox->SetValue(activeTextbox->GetValue() += key);
		lastPressedKey = key;
		UpdateDelta(now);
	}
	// If same key, check if enough time has passed since last key press. 
	// If enough time has passed, print pressed key
	else if (DeltaTimeHasPassed(200) && key) {
		activeTextbox->SetValue(activeTextbox->GetValue() += key);
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

TTF_Font* GUI::OpenFont(std::string fontUrl, int size) {
	TTF_Font* font = TTF_OpenFont(fontUrl.c_str(), size);
	if (!font) {
		char t[] = "Font error";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, t, TTF_GetError(), NULL);
		exit(0);
	}
	return font; 
}

void GUI::SetFont(std::string fontPath) {
	currentFont = fontPath; 
}

void GUI::Init() {
	TTF_Init();	// Initializes the SDL font library
	
	delta = SDL_GetTicks(); // Init milliseconds to be used for textbox input 
	textboxCursorDelta = SDL_GetTicks(); // Init milliseconds to be used for textbox cursor blinking 

	// Sets default font
	currentFont = "fonts/arial.ttf";
}

Textbox* GUI::CreateTextbox(std::string placeholder, int width, int height, int x, int y, int fontSize, int limit) {
	Textbox* tb = new Textbox(placeholder, width, height, x, y, fontSize, limit);
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