// HEADER FILE
// Contains class specification 
#ifndef MILDRED_H
#endif MILDRED_H

#include <iostream>
#include <SDL.h>
#include <vector>
#include "MapLine.h"
#include "Player.h"
#include "Calc.h"
#include "AssetManager.h"

using namespace std;

class Mildred {
	private:
		static SDL_Renderer* renderer; 
		static SDL_Window* window;
		static int screenWidth, screenHeight, fieldOfView, sightDistance; 
		static std::vector<MapLine>* mapLines;

	public: 
		static bool isRunning;
		static Player* player; 
		static AssetManager* assetManager;
		static void Init(); 
		static void CreateWindow(string title, int width, int height); 
		static void CreateRenderer();
		static void SetRenderDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		static void RenderPresent();
		static void RenderClear();
		static void DrawRect(int width, int height, int x, int y);
		static void CreateMapLine(int x, int y, int endX, int endY, string textureName);
		static void DrawMapLines(); 
		static SDL_Renderer* GetRenderer();
		static void HandleUserInput();
		static void RenderWallSlice(double* lineCollisionPointer, int drawPoint, string textureName); 
		static void CastRays(); 
		static SDL_Texture* GetTexture();
		static void HandleEvents(); 
};

