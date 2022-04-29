#include <iostream>
#include "Mildred.h"

int main(int argc, char* argv[]) {

    // Prepare engine settings 
    Mildred::Init(); 
    Mildred::CreateWindow("Mildred Engine", 1920, 1080);
    Mildred::assetManager->CreateAsset("test", "texture", "textures/stone-tex.bmp");
    Mildred::assetManager->CreateAsset("wall2", "texture", "textures/wall-1920.bmp");
    Mildred::assetManager->CreateAsset("wallpaper", "texture", "textures/wallpaper.bmp");
    Mildred::CreateMapBoundary(600, 200, 600, 550, "test2");
    Mildred::CreateMapBoundary(600, 200, 1000, 200, "wall2");
    Mildred::CreateMapBoundary(1000, 200, 1000, 500, "wallpaper");
    Mildred::assetManager->PrintAllAssetInfo();
    GUI::SetRenderTarget(Mildred::GetRenderer()); 
    GUI::CreateButton("heeeei", 5350, 100, 50, 50); 
    SDL_Color color = { 0, 255, 0 };
    // Begin game loop
    while (Mildred::isRunning)
    {
        // Runs every frame 
        Mildred::HandleUserInput();
        Mildred::HandleEvents(); 
        Mildred::SetRenderDrawColor(0, 0, 0, 255);
        Mildred::RenderClear();
        //Mildred::DrawTempBackground();
        Mildred::DrawMapBoundaries();
        Mildred::CastRays(); 
        Mildred::player->DrawPlayerOnMinimap();
        
        Mildred::DisplayText("Hello, world!", 18, 1700, 25, color);
        Mildred::DisplayFPS(); 
        GUI::Render(); 
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