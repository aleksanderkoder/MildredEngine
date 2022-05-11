#include <iostream>
#include "Mildred.h"

void test() {
    cout << "Hei fra test"; 
}

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

    GUI::Init(); 
    GUI::SetFont("fonts/OpenSans-Regular.ttf", 20); 
    GUI::SetRenderTarget(Mildred::GetRenderer()); 

    Button* h = GUI::CreateButton("Hei", 350, 50, 50, 250); 
    GUI::CreateButton("Hello, world!", 350, 50, 450, 250);
    SDL_Color color = { 0, 0, 0 };
    h->Bind(test); 

    // Begin game loop
    while (Mildred::isRunning)
    {
        // Runs every frame 
        Mildred::HandleUserInput();
        Mildred::HandleEvents(); 
        Mildred::SetRenderDrawColor(255, 255, 255, 255);
        Mildred::RenderClear();
        //Mildred::DrawMapBoundaries();
        //Mildred::CastRays(); 
        //Mildred::player->DrawPlayerOnMinimap();
        
        GUI::DisplayText("Mildred Engine", 750, 50, color, 45);
        Mildred::DisplayFPS(); 
        GUI::Render();

        Mildred::RenderPresent(); 
    }
   
    // SDL_Delay(5000);

	return 0; 
}