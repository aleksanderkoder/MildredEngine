// IMPLEMENTATION FILE
// Contains method implementations 

#include "Mildred.h"

 SDL_Renderer* Mildred::renderer;
 SDL_Window* Mildred::window;
 int Mildred::screenWidth, Mildred::screenHeight, Mildred::fieldOfView, Mildred::sightDistance;
 std::list<MapLine>* Mildred::mapLines;
 bool Mildred::isRunning;
 Player* Mildred::player;

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

	screenWidth = width;
	screenHeight = height;
	player = new Player(250, 250, 25, 0, 3);
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

SDL_Renderer* Mildred::GetRenderer() {
	return Mildred::renderer;
}

void Mildred::HandleUserInput() {
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_W]) {
		Mildred::player->MoveForward();
	}
	else if (state[SDL_SCANCODE_S]) {
		Mildred::player->MoveBackward();
	}
	else if (state[SDL_SCANCODE_A]) {
		Mildred::player->MoveLeft();
	}
	else if (state[SDL_SCANCODE_D]) {
		Mildred::player->MoveRight();
	}
	
	int mX, mY; 
	SDL_GetRelativeMouseState(&mX, &mY); 
	Mildred::player->AdjustAngle(&mX, &mY); 
}