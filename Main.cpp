#include <iostream>
#include <SDL.h>
#include "Mildred.h"

int main(int argc, char* argv[]) {

    Mildred::Init(); 
    Mildred::CreateWindow("Mildred Engine", 1920, 1080);
    Mildred::CreateMapLine(600, 200, 600, 550);

    while (Mildred::isRunning)
    {
        Mildred::HandleUserInput();
        Mildred::HandleEvents(); 
        Mildred::SetRenderDrawColor(0, 0, 0, 255);
        Mildred::RenderClear();
        /*Mildred::SetRenderDrawColor(0, 255, 0, 255);
        Mildred::DrawRect(50, 50, 150, 150);*/
        Mildred::DrawMapLines(); 
        Mildred::CastRays(); 
        Mildred::player->DrawPlayerOnMinimap();
        Mildred::RenderPresent(); 
    }


    /*if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        680, 480,
        0);

    if (!window)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }

    SDL_Surface* window_surface = SDL_GetWindowSurface(window);

    if (!window_surface)
    {
        std::cout << "Failed to get the surface from the window\n";
        return -1;
    }

    SDL_UpdateWindowSurface(window);

    SDL_Delay(5000);*/
	return 0; 
}