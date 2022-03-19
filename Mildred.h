// HEADER FILE
// Contains class specification 
#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include "MapBoundary.h"
#include "Player.h"
#include "Calc.h"
#include "AssetManager.h"

using namespace std;

class Mildred {
	private:
		static SDL_Renderer* renderer; 
		static SDL_Window* window;
		static int screenWidth, screenHeight, fieldOfView, viewDistance, frameCount; 
		static vector<MapBoundary>* mapBoundaries;
		static Uint64 ticks, oldFps; 

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
		static void CreateMapBoundary(int x, int y, int endX, int endY, string textureName);
		static void DrawMapBoundaries();
		static SDL_Renderer* GetRenderer();
		static void HandleUserInput();
		static bool RenderWallSlice(double* lineCollisionPointer, int drawPoint, double rayAngleRad, int lineLenght, int lineStartX, int lineStartY, string textureName); 
		static void CastRays(); 
		static void HandleEvents(); 
		static void DisplayText(string msg, int txtSize, int xpos, int ypos);
		static void DisplayFPS(); 
		static void DrawTempBackground();
};

