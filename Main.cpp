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

    GUI::Setup(1920, 1080); 
    GUI::SetRenderTarget(Mildred::GetRenderer()); 

    Button* h = GUI::CreateButton("Hei", 350, 50, 50, 250, 45, "fonts/comicz.ttf");
    GUI::CreateButton("Hello, world!", 350, 50, 450, 250, 16);
    GUI::CreateTextbox("Full name", 850, 50, 50, 750, 20, 50, "fonts/comicz.ttf");
    GUI::CreateTextbox("en annen tb", 550, 50, 500, 750, 45);
    Textbox* t = GUI::CreateTextbox("enda en tb", 250, 50, 500, 1000, 20, 50);
    t->SetCharLimit(3); 
    GUI::CreateButton("Hello, world!", 350, 50, 450, 450, 56);

    Checkbox* cb = GUI::CreateCheckbox(400, 400, 30); 

    SDL_Color color = { 0, 0, 0 };

    Label* l = GUI::CreateLabel("Mildred Engine", 25, 25, color, 36, "fonts/comicz.ttf");

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
        //GUI::DrawCircle(400, 400, 100); 

        // Example of how to render to texture!
        SDL_Texture* tex = SDL_CreateTexture(Mildred::GetRenderer(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 500, 500);
        SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND); 
        SDL_SetRenderTarget(Mildred::GetRenderer(), tex);
        Mildred::SetRenderDrawColor(255, 255, 255, 0);
        SDL_RenderClear(Mildred::GetRenderer()); 
        SDL_SetRenderDrawColor(Mildred::GetRenderer(), 0, 255, 0, 255); 
        SDL_RenderDrawLine(Mildred::GetRenderer(), 20, 20, 100, 100); 
        SDL_Rect rect; 
        rect.w = 500; 
        rect.h = 500;
        rect.x = 0;
        rect.y = 0; 
        SDL_SetRenderTarget(Mildred::GetRenderer(), NULL); 
        Mildred::SetRenderDrawColor(255, 255, 255, 255);
        SDL_RenderCopy(Mildred::GetRenderer(), tex, NULL, &rect);
        
        SDL_DestroyTexture(tex); 
        


        if (h->IsPressed()) {
            std::cout << "Hei is pressed" << std::endl; 
        }

        if (cb->IsChecked()) {
            //std::cout << "Checked!" << std::endl; 
            //cb->SetState(false); 
        }

        //Mildred::DisplayFPS(); 
        GUI::Render();
        Mildred::RenderPresent(); 
    }
   
    // SDL_Delay(5000);

	return 0; 
}