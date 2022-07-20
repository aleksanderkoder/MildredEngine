// IMPLEMENTATION FILE
// Contains method implementations 

#include "Mildred.h"

SDL_Renderer* Mildred::renderer;
SDL_Window* Mildred::window;
int Mildred::screenWidth, Mildred::screenHeight, Mildred::fieldOfView = 60, Mildred::viewDistance = 500, 
Mildred::frameCount; 
std::vector<MapBoundary>* Mildred::mapBoundaries = new std::vector<MapBoundary>();
AssetManager* Mildred::assetManager = new AssetManager();
bool Mildred::isRunning;
Player* Mildred::player = new Player(250, 250, 30, 270, 3);
Uint64 Mildred::ticks, Mildred::prevFps;
int test = 0;

void Mildred::Init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "There was an error initilizing SDL: " << SDL_GetError() << std::endl;
	}
	ticks = SDL_GetTicks64();	// Get store ticks since start for FPS counting
}
void Mildred::CreateWindow(std::string title, int width, int height) {
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_SHOWN);

	// Check what graphics backend is used 
	SDL_RendererInfo info = {};

	// Graphics device index to create renderer using correct graphics API, -1 is default
	int deviceIndex = -1;

	for (int i = 0; i < SDL_GetNumRenderDrivers(); i++) {
		SDL_GetRenderDriverInfo(i, &info);
		if (info.name == std::string("direct3d11")) {
			deviceIndex = i; 
			break; 
		}
	}

	CreateRenderer(deviceIndex);
	std::cout << "Using graphics API: " << info.name << std::endl; 

	// Captures mouse to window
	//SDL_SetRelativeMouseMode(SDL_TRUE);
	screenWidth = width;
	screenHeight = height;
	isRunning = true;
}

void Mildred::CreateRenderer(int graphicsDeviceIndex) {
	// NOTE: Remove SDL_RENDERER_PRESENTVSYNC flag to turn off v-sync
	//  | SDL_RENDERER_PRESENTVSYNC
	renderer = SDL_CreateRenderer(window, graphicsDeviceIndex, SDL_RENDERER_ACCELERATED);
	// To enable aplha channel on draw calls
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "BEST"); 
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

void Mildred::CreateMapBoundary(int x, int y, int endX, int endY, std::string textureName) {
	MapBoundary ml(x, y, endX, endY, textureName);
	mapBoundaries->push_back(ml);
}
void Mildred::DrawMapBoundaries() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int i = 0; i < mapBoundaries->size(); i++) {
		MapBoundary mb = (*mapBoundaries)[i]; 
		SDL_RenderDrawLine(renderer, mb.startX, mb.startY, mb.endX, mb.endY);
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
	if (state[SDL_SCANCODE_S]) {
		player->MoveBackward();
	}
	if (state[SDL_SCANCODE_A]) {
		player->MoveLeft();
	}
	if (state[SDL_SCANCODE_D]) {
		player->MoveRight();
	}
	if (state[SDL_SCANCODE_ESCAPE]) {
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}

	int mX, mY;
	SDL_GetRelativeMouseState(&mX, &mY);
	player->AdjustAngle(&mX, &mY);
}

void Mildred::RenderWallSlice(double* lineCollisionPointer, int drawPoint, double angleRad, int lineLength, int lineStartX, int lineStartY, std::string textureName) {
	// If the ray has hit a wall
	if (lineCollisionPointer) {
		double collisionDistance = Calc::GetDistance(player->posXCentered, player->posYCentered, lineCollisionPointer[0], lineCollisionPointer[1]);
		int distanceBetweenCollisionAndLineStart = Calc::GetDistance(lineCollisionPointer[0], lineCollisionPointer[1], lineStartX, lineStartY); 
		double sliceHeight = 40000 / (collisionDistance * cos(angleRad - player->viewAngle));
		double sliceVerticalOffset = (screenHeight - sliceHeight) / 2;
		
		SDL_Texture* currentTexture = assetManager->GetTextureByName(textureName);
		if (currentTexture) {
			int textureHeight;
			int textureWidth;
			SDL_QueryTexture(currentTexture, NULL, NULL, &textureWidth, &textureHeight);

			// Determines the shape and position of the texture 
			SDL_FRect dst;
			dst.x = drawPoint;
			dst.y = sliceVerticalOffset;
			dst.w = 1; 
			dst.h = sliceHeight;

			// Determines what part of texture to render 
			SDL_Rect texturePart;
			texturePart.x = drawPoint % textureWidth; // Doesn't texture map correctly
			texturePart.y = 1;
			texturePart.w = 1;
			texturePart.h = textureHeight;

			SDL_RenderCopyF(renderer, currentTexture, &texturePart, &dst);
		}
		else {
			int colorShade = 255 - collisionDistance / 2.5;
			SetRenderDrawColor(colorShade, colorShade, colorShade, 255);
			DrawRect(1, sliceHeight, drawPoint, sliceVerticalOffset);
			//SDL_RenderDrawLine(renderer, drawPoint, sliceVerticalOffset, drawPoint, sliceHeight);
		}
	}
}

void Mildred::CastRays() {
	// Base ray angle step interval based on fov
	double stepInterval = (double)fieldOfView / (double)screenWidth;

	// Offset to be used by rays to calculate ray angle relative to the center of vision 
	double halfFov = Calc::ToRadians(fieldOfView / 2);

	// One iteration for each pixel column of the screen resolution 
	for (int i = 0; i < screenWidth; i++) {
		
		// Next step for ray angle to take
		double nextStep = Calc::ToRadians(stepInterval * i);

		// Calculate the angle of the new ray in radians
		double rayAngleRadian = player->viewAngle - halfFov + nextStep;

		// Calculate each ray's x and y point based on player view angle and iteration count
		double rayAngleX = player->posXCentered + cos(rayAngleRadian) * viewDistance;
		double rayAngleY = player->posYCentered + sin(rayAngleRadian) * viewDistance;


		// Only show every 50th angle line vision indicator
		//if (i % 50 == 0) {
			SetRenderDrawColor(0, 0, 255, 255);
			SDL_RenderDrawLine(renderer, player->posXCentered, player->posYCentered, rayAngleX, rayAngleY);
		//}

		// Check current angle line against existing walls to see if they collide
		for (int j = 0; j < mapBoundaries->size(); j++) {
			// Render wall slice if they collide
			MapBoundary mb = (*mapBoundaries)[j];
			RenderWallSlice(Calc::LineToLineCollision(player->posXCentered, player->posYCentered, rayAngleX, rayAngleY,
				mb.startX, mb.startY, mb.endX, mb.endY), i, rayAngleRadian, 
				Calc::GetDistance(mb.startX, mb.startY, mb.endX, mb.endY), mb.startX, mb.startY, mb.textureName);

		}
	}
}

void Mildred::HandleEvents() {
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_QUIT:
				Mildred::isRunning = false;
				std::cout << "Quitting";
				break;
		}
	}
}

//void Mildred::DisplayFPS() {
//	frameCount++;
//	Uint64 now = SDL_GetTicks64();
//	SDL_Color c = { 0, 255, 0 };
//	if (frameCount >= 12) {
//
//		Uint64 fps = 1000 / (now - ticks);
//		prevFps = fps;
//		GUI::RenderLabel("FPS: " + std::to_string(fps), screenWidth - 100, 25, c, 16);
//		frameCount = 0;
//	}
//	else {
//		GUI::RenderLabel("FPS: " + std::to_string(prevFps), screenWidth - 100, 25, c, 16);
//	}
//	ticks = now;
//}

void Mildred::DrawTempBackground() {
	SetRenderDrawColor(101, 67, 33, 255);
	DrawRect(screenWidth, screenHeight / 2, 1, screenHeight / 2);
	SetRenderDrawColor(0, 100, 255, 255);
	DrawRect(screenWidth, screenHeight / 2, 1, 1);
}