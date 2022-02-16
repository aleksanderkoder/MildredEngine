// IMPLEMENTATION FILE
// Contains method implementations 

#include "Mildred.h"
#include "Calc.h"

 SDL_Renderer* Mildred::renderer;
 SDL_Window* Mildred::window;
 int Mildred::screenWidth, Mildred::screenHeight, Mildred::fieldOfView = 60, Mildred::sightDistance = 300;
 std::vector<MapLine>* Mildred::mapLines = new vector<MapLine>();
 bool Mildred::isRunning;
 Player* Mildred::player = new Player(250, 250, 30, 270, 3);

void Mildred::Init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "There was an error initilizing SDL: " << SDL_GetError() << std::endl; 
	}
}
void Mildred::CreateWindow(string title, int width, int height) {
	const char* t = title.c_str(); 
	window = SDL_CreateWindow(t, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height, SDL_WINDOW_SHOWN); 

	CreateRenderer(); 

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

void Mildred::CreateMapLine(int x, int y, int endX, int endY) {
	MapLine ml(x, y, endX, endY);
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

void Mildred::test() {
		SDL_Surface* image = SDL_LoadBMP("textures/stone-tex.bmp");
		if (!image) {
			std::cout << SDL_GetError() << std::endl; 
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
		SDL_FreeSurface(image);
		image = NULL;

		// Determines the shape of the texture 
		SDL_Rect dst;
		dst.x = 150;
		dst.y = 0;
		dst.w = 500;
		dst.h = 250;
		// Determines what part of texture to render
		SDL_Rect r;
		r.x = 0;
		r.y = 0;
		r.w = 50;
		r.h = 50;

		RenderClear();
		SDL_RenderCopy(renderer, texture, &r, &dst);
	
}

void Mildred::RenderWallSlice(double* lineCollisionPointer, int drawPoint) {
	// If the ray has hit a wall
	if (lineCollisionPointer) {
		
		double collisionDistance = Calc::GetDistance(player->positionX + player->size / 2, player->positionY + player->size / 2, lineCollisionPointer[0], lineCollisionPointer[1]);
		//std::cout << collisionDistance << "\n";
		int colorShade = 255 - collisionDistance / 2.5; 
		int sliceVerticalOffset = collisionDistance / 2; 
		SetRenderDrawColor(colorShade, colorShade, colorShade, 255);
		DrawRect(1, screenHeight - collisionDistance * 2, drawPoint, sliceVerticalOffset); 
	}
}

void Mildred::CastRays() {
	double stepInterval = (double)fieldOfView / (double)screenWidth;
	// One iteration for each pixel column of the screen resolution 
	for (int i = 0; i < screenWidth; i++) {
		// Calculate each ray's x and y point based on player view angle and iteration count
		double rayAngleX = player->positionX + cos(player->viewAngle - Calc::ToRadians(fieldOfView / 2) + Calc::ToRadians(stepInterval * i)) * sightDistance; 
		double rayAngleY = player->positionY + sin(player->viewAngle - Calc::ToRadians(fieldOfView / 2) + Calc::ToRadians(stepInterval * i)) * sightDistance;

		// Only show every 30th angle line vision indicator
		//if (i % 30 == 0) {
			SetRenderDrawColor(0, 0, 255, 255); 
			SDL_RenderDrawLine(renderer, player->positionX + player->size / 2, player->positionY + player->size / 2, rayAngleX, rayAngleY); 
		//}

		// Check current angle line against existing walls to see if they collide
		for (int j = 0; j < mapLines->size(); j++) {
			// Render wall slice if they collide
			RenderWallSlice(Calc::LineToLineCollision(player->positionX + player->size / 2, player->positionY + player->size / 2, rayAngleX, rayAngleY, (*mapLines)[j].startX, (*mapLines)[j].startY, (*mapLines)[j].endX, (*mapLines)[j].endY), i);

		}

	}
	/*std::cout << c << std::endl; 
	std::cout << stepInterval << std::endl;*/
}