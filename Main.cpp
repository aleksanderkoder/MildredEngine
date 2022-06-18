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
    GUI::SetFont("fonts/OpenSans-Regular.ttf"); 
    GUI::SetRenderTarget(Mildred::GetRenderer()); 

    Button* h = GUI::CreateButton("Hei", 350, 50, 50, 250, 45); 
    GUI::CreateButton("Hello, world!", 350, 50, 450, 250, 16);
    GUI::CreateTextbox("Full name", 250, 50, 50, 750, 20);
    GUI::CreateTextbox("en annen tb", 250, 50, 500, 750, 20);
    Textbox* t = GUI::CreateTextbox("enda en tb", 250, 50, 500, 1000, 20);
    GUI::CreateButton("Hello, world!", 350, 50, 450, 450, 16);

    SDL_Color color = { 0, 0, 0 };
    h->Bind(test); 

    Label* l = GUI::CreateLabel("Mildred Engine", 25, 25, color, 36);

    // Begin game loop, runs every frame
    while (Mildred::isRunning)
    {
        Mildred::HandleUserInput();
        Mildred::HandleEvents();
        Mildred::SetRenderDrawColor(255, 255, 255, 255);
        Mildred::RenderClear();
        /*Mildred::DrawMapBoundaries();
        Mildred::CastRays(); 
        Mildred::player->DrawPlayerOnMinimap();*/
        
        Mildred::DisplayFPS(); 
        GUI::Render();
        Mildred::RenderPresent(); 
    }
   
    // SDL_Delay(5000);

	return 0; 
}