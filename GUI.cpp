#include "GUI.h"

SDL_Renderer* GUI::targetRenderer = NULL;
Uint32 GUI::delta, GUI::textboxCursorDelta;
Textbox* GUI::activeTextbox = NULL; 
char GUI::lastPressedKey;
bool GUI::leftMouseButtonPressedState = false, GUI::leftMouseButtonPressedLastState = false,
GUI::drawTextBoxCursor = true, GUI::capsLockEnabled = false, GUI::rerender = false;
int GUI::viewWidth = 0, GUI::viewHeight = 0; 
SDL_Texture* GUI::snapshotFrame = NULL;
Page* GUI::currentPage = NULL; 

// LIBRARY SETUP METHODS

void GUI::Setup(int viewWidth, int viewHeight, SDL_Renderer* renderer) {
	TTF_Init();	// Initializes the SDL font library
	targetRenderer = renderer;

	// To be used for creating frame snapshots
	viewWidth = viewWidth; 
	viewHeight = viewHeight;

	delta = SDL_GetTicks(); // Init milliseconds to be used for textbox input 
	textboxCursorDelta = SDL_GetTicks(); // Init milliseconds to be used for textbox cursor blinking 
}

void GUI::SetRenderTarget(SDL_Renderer* renderer) {
	targetRenderer = renderer; 
}

// ELEMENT CREATION METHODS 

Label* GUI::CreateLabel(std::string text, int x, int y, SDL_Color color, int fontSize, std::string fontPath) {
	Label* lbl = new Label(text, x, y, color, fontSize, fontPath);
	return lbl;
}

Textbox* GUI::CreateTextbox(std::string placeholder, int width, int height, int x, int y, int fontSize, int limit, std::string fontPath) {
	Textbox* tb = new Textbox(placeholder, width, height, x, y, fontSize, limit, fontPath);
	return tb;
}

Checkbox* GUI::CreateCheckbox(int x, int y, int size, bool defaultState) {
	Checkbox* cb = new Checkbox(x, y, size, defaultState);
	return cb;
}

Button* GUI::CreateButton(std::string label, int width, int height, int x, int y, int fontSize, std::string fontPath) {
	Button* b = new Button(label, width, height, x, y, fontSize, fontPath);
	return b;
}

// ELEMENT RENDERING METHODS 
	// TODO: Make this render elements taken from pages!

void GUI::RenderLabels() {
	auto labels = currentPage->GetLabels();
	// Loop through all labels
	for (int i = 0; i < labels->size(); i++) {
		Label* curr = (*labels)[i];

		if (!curr->GetDisplayState()) continue;
			
		RenderLabel(curr->GetText(), curr->GetX(), curr->GetY(), curr->GetColor(), curr->GetFont(), curr->GetFontSize());
	}
}	

void GUI::RenderButtons() {
	auto buttons = currentPage->GetButtons(); 
	// Loop through all buttons
	for (int i = 0; i < buttons->size(); i++) {
		Button* curr = (*buttons)[i];

		if (!curr->GetDisplayState()) continue;

		// Get necessary data from current object
		int height = curr->GetHeight(); 
		int width = curr->GetWidth(); 
		int x = curr->GetX(); 
		int y = curr->GetY(); 
		SDL_Color color = curr->GetColor(); 
		SDL_Color hoverColor = curr->GetHoverColor(); 
		TTF_Font* font = curr->GetFont(); 
		std::string label = curr->GetLabel(); 

		// Create button rectangle data
		SDL_Rect rect;
		rect.w = width;
		rect.h = height; 
		rect.x = x;
		rect.y = y;

		bool mHover = OnMouseHover(x, y, width, height);

		// If mouse doesn't hover over button, default idle state
		SDL_SetRenderDrawColor(targetRenderer, color.r, color.g, color.b, color.a);
		curr->SetPressedState(false);

		// If mouse hovers over button and activates
		if (mHover && leftMouseButtonPressedState) {
			curr->SetPressedState(true); 
			SDL_SetRenderDrawColor(targetRenderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a - 75);
			activeTextbox = NULL;
		}
		// If mouse hovers over
		else if (mHover) {
			if (!leftMouseButtonPressedLastState)
				SDL_SetRenderDrawColor(targetRenderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
			else 
				SDL_SetRenderDrawColor(targetRenderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a - 75);
		}

		// Draw button rectangle
		SDL_RenderFillRect(targetRenderer, &rect);

		SDL_Color c = { 255, 255, 255 };
		std::tuple<int, int> mesDim = GetTextDimensions(label, font);

		// Display button label
		RenderLabel(label, x + width / 2 - std::get<0>(mesDim) / 2, y + height / 2 - std::get<1>(mesDim) / 2, c, font, curr->GetFontSize());
	}
}

void GUI::RenderTextboxes() {
	auto textboxes = currentPage->GetTextboxes(); 
	// Loop through all textboxes
	for (int i = 0; i < textboxes->size(); i++) {
		Textbox* curr = (*textboxes)[i];

		if (!curr->GetDisplayState()) continue;

		// Get necessary data from current object
		int height = curr->GetHeight();
		int width = curr->GetWidth();
		int x = curr->GetX();
		int y = curr->GetY();
		SDL_Color color = curr->GetColor();
		SDL_Color hoverColor = curr->GetHoverColor();
		TTF_Font* font = curr->GetFont();
		int fontSize = curr->GetFontSize(); 
		std::string value = curr->GetValue(); 
		std::string placeholder = curr->GetPlaceholder(); 

		// Create textbox rectangle data
		SDL_Rect rect;
		rect.w = width;
		rect.h = height;
		rect.x = x;
		rect.y = y; 

		bool mHover = OnMouseHover(x, y, width, height);

		// If mouse doesn't hover over textbox, default idle state
		SDL_SetRenderDrawColor(targetRenderer, color.r, color.g, color.b, color.a);

		// If mouse hovers over textbox and activates
		if (mHover && leftMouseButtonPressedState) {
			SDL_SetRenderDrawColor(targetRenderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
			activeTextbox = curr; 
		}
		// If mouse hovers over
		else if (mHover) {
			SDL_SetRenderDrawColor(targetRenderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
		}
		
		// Draw textbox rectangle
		SDL_RenderFillRect(targetRenderer, &rect);
		
		std::tuple<int, int> txtDim;
		int lblX, lblY; 

		// If no value, show placeholder
		if (value.empty()) {
			SDL_Color c = { 255, 255, 255, 150 };
			txtDim = GetTextDimensions(placeholder, font);
			lblX = x + width / 2 - std::get<0>(txtDim) / 2;
			lblY = y + height / 2 - std::get<1>(txtDim) / 2;
			
			// Display textbox placeholder text
			RenderLabel(placeholder, lblX, lblY, c, font, fontSize);
		}
		// If textbox has a user entered value, show that value in textbox
		else {
			SDL_Color c = { 255, 255, 255 };
			txtDim = GetTextDimensions(value, font);
			lblX = x + width / 2 - std::get<0>(txtDim) / 2;
			lblY = y + height / 2 - std::get<1>(txtDim) / 2;

			// Display textbox label
			RenderLabel(value, lblX, lblY, c, font, fontSize);
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
			rect;
			rect.w = 2;
			rect.h = fontSize;
			rect.x = lblX + std::get<0>(txtDim);
			rect.y = y + height / 2 - fontSize / 2;
			SDL_SetRenderDrawColor(targetRenderer, 255, 255, 255, 255);
			SDL_RenderFillRect(targetRenderer, &rect);
		}
		CaptureInputText(); 
	} 
}

void GUI::RenderCheckboxes() {	// TODO: Draw v-mark inside checkbox (if selected) to show its state
	auto checkboxes = currentPage->GetCheckboxes(); 
	// Loop through all checkboxes
	for (int i = 0; i < checkboxes->size(); i++) {
		Checkbox* curr = (*checkboxes)[i];

		if (!curr->GetDisplayState()) continue;

		// Get necessary data from current object
		int size = curr->GetSize();
		int x = curr->GetX(); 
		int y = curr->GetY(); 
		bool checked = curr->IsChecked(); 
		SDL_Color color = curr->GetColor(); 
		SDL_Color checkmarkColor = curr->GetCheckmarkColor();
		SDL_Color hoverColor = curr->GetHoverColor(); 

		// Create checkbox rectangle data
		SDL_Rect rect;
		rect.w = size; 
		rect.h = size; 
		rect.x = x;
		rect.y = y; 

		bool mHover = OnMouseHover(x, y, size, size);

		// If mouse doesn't hover over checkbox, default idle state
		SDL_SetRenderDrawColor(targetRenderer, color.r, color.g, color.b, color.a);

		// If mouse hovers over button and activates
		if (mHover && leftMouseButtonPressedState) {
			SDL_SetRenderDrawColor(targetRenderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a - 75);
			curr->SetState(!checked);
			activeTextbox = NULL;
		}
		// If mouse hovers over
		else if (mHover) {
			if (!leftMouseButtonPressedLastState)
				SDL_SetRenderDrawColor(targetRenderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
			else
				SDL_SetRenderDrawColor(targetRenderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a - 75);
		}

		// Draw checkbox rectangle
		SDL_RenderFillRect(targetRenderer, &rect);

		// Draw checkmark if checked 
		if (checked) {
			rect.w = size - size * 0.6f;
			rect.h = size - size * 0.6f;
			rect.x = x + size * 0.6f / 2;
			rect.y = y + size * 0.6f / 2;

			SDL_SetRenderDrawColor(targetRenderer, checkmarkColor.r, checkmarkColor.g, checkmarkColor.b, checkmarkColor.a);
			SDL_RenderFillRect(targetRenderer, &rect);
		}
	}
}

void GUI::RenderLabel(std::string text, int x, int y, SDL_Color color, TTF_Font* font, int fontSize) {

	// Create surface to render text on
	SDL_Surface* surfaceMessage =
		TTF_RenderText_Blended(font, text.c_str(), color);

	// Convert to texture
	SDL_Texture* message = SDL_CreateTextureFromSurface(targetRenderer, surfaceMessage);

	// Create a rectangle/shape of the message texture
	SDL_Rect message_rect;
	message_rect.x = x;
	message_rect.y = y;
	message_rect.w = surfaceMessage->w;
	message_rect.h = surfaceMessage->h;

	SDL_RenderCopy(targetRenderer, message, NULL, &message_rect);

	// Frees resources 
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

void GUI::Render() {
	UpdateMouseButtonState();
	RenderLabels();
	RenderButtons();
	RenderTextboxes();
	RenderCheckboxes();
}

// PAGES 

Page* GUI::CreatePage() {
	Page* page = new Page(); 
	return page; 
}

void GUI::DisplayPage(Page* page) {
	currentPage = page;
	rerender = true; 
}

// UTILITY METHODS 

void GUI::DrawCircle(int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	SDL_SetRenderDrawColor(targetRenderer, 0, 0, 0, 255); 

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(targetRenderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(targetRenderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(targetRenderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(targetRenderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(targetRenderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(targetRenderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(targetRenderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(targetRenderer, centreX - y, centreY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}

std::tuple<int, int> GUI::GetTextDimensions(std::string text, TTF_Font* font) {
	// Text color
	SDL_Color color = { 0, 0, 0 };

	// Create surface to render text onto
	SDL_Surface* surfaceMessage =
		TTF_RenderText_Blended(font, text.c_str(), color);

	std::tuple<int, int> dim(surfaceMessage->w, surfaceMessage->h);

	SDL_FreeSurface(surfaceMessage);
	return dim;
}

void GUI::CaptureInputText() {
	if (!activeTextbox) return; 


	int nK;
	char key = NULL; 
	Uint32 now = SDL_GetTicks(); 
	const Uint8* keys = SDL_GetKeyboardState(&nK);
	std::string value = activeTextbox->GetValue(); 

	// Enable capital letters if capslock is pressed
	if (keys[SDL_SCANCODE_CAPSLOCK] && now - delta >= 300) {
		capsLockEnabled = !capsLockEnabled;
		delta = now; 
	}

	// Delete last character from input string if backspace is pressed
	if (keys[SDL_SCANCODE_BACKSPACE] && now - delta >= 110) {
		activeTextbox->SetValue(value.substr(0, value.size() - 1));
		delta = now; 

		// Reset textbox cursor on key input
		textboxCursorDelta = now;
		drawTextBoxCursor = true;
		return; 
	}

	// If character limit has been reached, jump out 
	if (value.length() >= activeTextbox->GetCharLimit()) return;

	for (int i = 0; i < nK; i++) {
		if (keys[i] && ValidKey(i)) {
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

	// If pressed key is not the same as last key, then just print immediately 
	if (key != lastPressedKey && key) {
		activeTextbox->SetValue(value += key);
		lastPressedKey = key;
		delta = now; 
	}
	// If same key, check if enough time has passed since last key press. 
	// If enough time has passed, print pressed key
	else if (now - delta >= 200 && key) {
		activeTextbox->SetValue(value += key);
		lastPressedKey = key;
		delta = now; 
	}
}

bool GUI::ValidKey(int key) {
	// Determines what keys are considered valid (valid as in printable)
	if (key >= 4 && key <= 39 || key >= 44 && key <= 49 || key >= 54 && key <= 56) {
		return true;
	}
	return false;
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

void GUI::prepareNewSnapshotFrame() {
	// Destroy old snapshot frame
	/*SDL_DestroyTexture(snapshotFrame);*/

	// Create texture
	snapshotFrame = SDL_CreateTexture(targetRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, viewWidth, viewHeight);
	SDL_SetTextureBlendMode(snapshotFrame, SDL_BLENDMODE_BLEND);

	// Give drawing focus to texture
	SDL_SetRenderTarget(targetRenderer, snapshotFrame);

	// Clear texture
	SDL_SetRenderDrawColor(targetRenderer, 255, 255, 255, 0);
	SDL_RenderClear(targetRenderer);
}

void GUI::finalizeNewSnapshotFrame() {
	/*SDL_SetRenderDrawColor(Mildred::GetRenderer(), 0, 255, 0, 255);
	SDL_RenderDrawLine(Mildred::GetRenderer(), 20, 20, 100, 100);*/
	SDL_Rect rect;
	rect.w = viewWidth;
	rect.h = viewHeight;
	rect.x = 0;
	rect.y = 0;

	// Return drawing focus to screen 
	SDL_SetRenderTarget(targetRenderer, NULL);
	//Mildred::SetRenderDrawColor(255, 255, 255, 255);
	// Draw texture to screen
	SDL_RenderCopy(targetRenderer, snapshotFrame, NULL, &rect);

}

void GUI::Rerender() {
	rerender = true; 
}