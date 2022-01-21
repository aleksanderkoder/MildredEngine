#include <iostream>
#include <SDL.h>
#include "Mildred.h"
#include "MapLine.h"

int main(int argc, char* argv[]) {
    Mildred::Init(); 
    Mildred::CreateWindow("Mildred Engine", 1920, 1080);

    SDL_Event e;
    while (Mildred::isRunning)
    {
        // Check to see if there are any events and continue to do so until the queue is empty.
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                Mildred::isRunning = false;
                break;
        //        // Handles keyboard inputs based on key pressed

        //    case SDL.SDL_EventType.SDL_KEYDOWN:
        //        Mithril.RegisterKeyPress(e.key.keysym.sym);
        //        break;
        //    case SDL.SDL_EventType.SDL_KEYUP:
        //        Mithril.RemoveKeyPress(e.key.keysym.sym);
        //        break;
        //    case SDL.SDL_EventType.SDL_MOUSEMOTION:
        //        Mithril.player.AdjustAngle(e.motion.xrel, e.motion.yrel);
        //        break;
            }
        }

        Mildred::HandleUserInput();
        Mildred::SetRenderDrawColor(0, 0, 0, 255);
        Mildred::RenderClear();
        Mildred::SetRenderDrawColor(0, 255, 0, 255);
        Mildred::DrawRect(50, 50, 150, 150);
        Mildred::player->DrawPlayerOnMinimap();
        Mildred::RenderPresent(); 
        /*Mithril.HandlePressedKeys();
        Mithril.RenderClear();

        Mithril.SetRenderDrawColor(255, 255, 255, 255);
        Mithril.DrawRect(100, 100, 100 + t, 100);
        Mithril.DrawPlayerOnMinimap();
        Mithril.DrawMapLines();

        Mithril.RenderPresent();*/
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