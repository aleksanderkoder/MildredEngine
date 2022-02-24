// IMPLEMENTATION FILE
// Contains method implementations 

#include "Mildred.h"

SDL_Renderer* Mildred::renderer;
SDL_Window* Mildred::window;
int Mildred::screenWidth, Mildred::screenHeight, Mildred::fieldOfView = 60, Mildred::sightDistance = 450, Mildred::frameCount;
vector<MapLine>* Mildred::mapLines = new vector<MapLine>();
AssetManager* Mildred::assetManager = new AssetManager();
bool Mildred::isRunning;
Player* Mildred::player = new Player(250, 250, 30, 270, 3);
Uint64 Mildred::ticks, Mildred::oldFps;
int test = 0;

void Mildred::Init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "There was an error initilizing SDL: " << SDL_GetError() << endl;
	}
	ticks = SDL_GetTicks64();	// Get store ticks since start for FPS counting
}
void Mildred::CreateWindow(string title, int width, int height) {
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height, SDL_WINDOW_SHOWN);

	CreateRenderer();

	// Check what graphics backend is used 
	SDL_RendererInfo info;
	SDL_GetRendererInfo(renderer, &info);
	cout << "Graphics API: " << info.name << endl;

	// Captures mouse to window
	SDL_SetRelativeMouseMode(SDL_TRUE);
	screenWidth = width;
	screenHeight = height;
	isRunning = true;
}

void Mildred::CreateRenderer() {
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

}

void Mildred::SetRenderDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Mildred::RenderPresent() {
	SDL_RenderPresent(renderer);
}

void Mildred::RenderClear() {
	SDL_RenderClear(renderer);
}

void Mildred::DrawRect(int width, int height, int x, int y) {
	SDL_Rect rect;
	rect.w = width;
	rect.h = height;
	rect.x = x;
	rect.y = y;
	SDL_RenderFillRect(renderer, &rect);
}

void Mildred::CreateMapLine(int x, int y, int endX, int endY, string textureName) {
	MapLine ml(x, y, endX, endY, textureName);
	mapLines->push_back(ml);
}
void Mildred::DrawMapLines() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int i = 0; i < mapLines->size(); i++) {
		SDL_RenderDrawLine(renderer, (*mapLines)[i].startX, (*mapLines)[i].startY, (*mapLines)[i].endX, (*mapLines)[i].endY);
	}
}

SDL_Renderer* Mildred::GetRenderer() {
	return renderer;
}

void Mildred::HandleUserInput() {
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_W]) {
		player->MoveForward();
	}
	else if (state[SDL_SCANCODE_S]) {
		player->MoveBackward();
	}
	else if (state[SDL_SCANCODE_A]) {
		player->MoveLeft();
	}
	else if (state[SDL_SCANCODE_D]) {
		player->MoveRight();
	}
	else if (state[SDL_SCANCODE_ESCAPE]) {
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}

	int mX, mY;
	SDL_GetRelativeMouseState(&mX, &mY);
	player->AdjustAngle(&mX, &mY);
}

bool Mildred::RenderWallSlice(double* lineCollisionPointer, int drawPoint, int lineLength, int lineStartX, int lineStartY, string textureName) {
	// If the ray has hit a wall
	if (lineCollisionPointer) {
		double collisionDistance = Calc::GetDistance(player->positionX + player->size / 2, player->positionY + player->size / 2, lineCollisionPointer[0], lineCollisionPointer[1]);
		int distanceBetweenCollisionAndLineStart = Calc::GetDistance(lineCollisionPointer[0], lineCollisionPointer[1], lineStartX, lineStartY); 
		//cout << "Length: " << lineLength << endl;
		//cout << distanceBetweenCollisionAndLineStart << "\n";
		//double colorShade = 255 - collisionDistance / 2.5;
		double sliceHeight = screenHeight - collisionDistance * 2;
		double sliceVerticalOffset = (screenHeight - sliceHeight) / 2;

		//double angle = Calc::NormalizeAngleRad(player->viewAngle - (Calc::ToRadians(fieldOfView / 2) + Calc::ToRadians(stepInterval * drawPoint))); 
		//double adjacent = cos(angle) * hypotenuse; 
		//cout << " New angle: " << angle << endl;
		//cout << "Fishbowl dist: " << hypotenuse << endl;
		//cout << "Correct dist: " << adjacent << endl;

		SDL_Texture* currentTexture = assetManager->GetTextureByName(textureName);
		if (currentTexture) {
			int textureHeight;
			int textureWidth;
			SDL_QueryTexture(currentTexture, NULL, NULL, &textureWidth, &textureHeight);
			// Determines the shape and position of the texture 
			SDL_Rect dst;
			dst.x = drawPoint;
			dst.y = sliceVerticalOffset;
			dst.w = 1; 
			dst.h = sliceHeight;
			// Determines what part of texture to render 
			SDL_Rect texturePart;
			// old: drawPoint % textureWidth; 
			texturePart.x = drawPoint % textureWidth; // Doesn't texture map correctly
			texturePart.y = 1;
			texturePart.w = 1;
			texturePart.h = textureHeight;

			SDL_RenderCopy(renderer, currentTexture, &texturePart, &dst);
		}
		else {
			SetRenderDrawColor(255, 0, 255, 255);
			DrawRect(1, screenHeight - collisionDistance * 2, drawPoint, sliceVerticalOffset);
		}
		return true;
	}
	return false;
}

void Mildred::CastRays() {
	double stepInterval = (double)fieldOfView / (double)screenWidth;
	// One iteration for each pixel column of the screen resolution 
	for (int i = 1; i < screenWidth; i++) {
		
		// Calculate each ray's x and y point based on player view angle and iteration count
		double rayAngleX = player->positionX + player->size / 2 + cos(player->viewAngle - Calc::ToRadians(fieldOfView / 2) + Calc::ToRadians(stepInterval * i)) * sightDistance;
		double rayAngleY = player->positionY + player->size / 2 + sin(player->viewAngle - Calc::ToRadians(fieldOfView / 2) + Calc::ToRadians(stepInterval * i)) * sightDistance;


		// Only show every 50th angle line vision indicator
		//if (i % 50 == 0) {
			SetRenderDrawColor(0, 0, 255, 255);
			SDL_RenderDrawLine(renderer, player->positionX + player->size / 2, player->positionY + player->size / 2, rayAngleX, rayAngleY);
		//}

		// Check current angle line against existing walls to see if they collide
		for (int j = 0; j < mapLines->size(); j++) {
			// Render wall slice if they collide
			if (RenderWallSlice(Calc::LineToLineCollision(player->positionX + player->size / 2, player->positionY + player->size / 2, rayAngleX, rayAngleY, (*mapLines)[j].startX, (*mapLines)[j].startY, (*mapLines)[j].endX, (*mapLines)[j].endY), i, Calc::GetDistance((*mapLines)[j].startX, (*mapLines)[j].startY, (*mapLines)[j].endX, (*mapLines)[j].endY), (*mapLines)[j].startX, (*mapLines)[j].startY, (*mapLines)[j].textureName)) {
				break;	// Break loop to only draw one slice per column
			}

		}

	}
	/*cout << c << endl;
	cout << stepInterval << endl;*/
}

void Mildred::HandleEvents() {
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			Mildred::isRunning = false;
			cout << "Quitting";
			break;
		}
	}
}

void Mildred::DisplayText(string msg, int txtSize, int xpos, int ypos) {
	TTF_Font* font; // Declare a SDL_ttf font : font
	TTF_Init(); // Initilize SDL_ttf
	// This opens a font style and sets a size
	font = TTF_OpenFont("fonts/arial.ttf", txtSize);

	// Text color
	SDL_Color color = { 0, 255, 0 };

	// Create surface to render text on
	SDL_Surface* surfaceMessage =
		TTF_RenderText_Blended(font, msg.c_str(), color);

	// Convert to texture
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	// Create a rectangle/shape of the message texture
	SDL_Rect Message_rect;
	Message_rect.x = xpos;
	Message_rect.y = ypos;
	Message_rect.w = surfaceMessage->w;
	Message_rect.h = surfaceMessage->h;

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	// Frees surface and texture
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

void Mildred::DisplayFPS() {
	frameCount++;
	Uint64 now = SDL_GetTicks64();
	if (frameCount >= 15) {

		Uint64 fps = 1000 / (now - ticks);
		oldFps = fps;
		DisplayText("FPS: " + to_string(fps), 16, screenWidth - 100, 25);
		frameCount = 0;
	}
	else {
		DisplayText("FPS: " + to_string(oldFps), 16, screenWidth - 100, 25);
	}
	ticks = now;
}

void Mildred::DrawTempBackground() {
	SetRenderDrawColor(235, 221, 202, 255);
	DrawRect(screenWidth, screenHeight / 2, 1, screenHeight / 2);
	SetRenderDrawColor(0, 100, 255, 255);
	DrawRect(screenWidth, screenHeight / 2, 1, 1);
}