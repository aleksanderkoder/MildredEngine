// HEADER FILE
// Contains class specification 
#pragma once

#include <iostream>
#include <SDL.h>
#include <vector>
#include "MapBoundary.h"
#include "Player.h"
#include "Calc.h"
#include "AssetManager.h"
#include "GUI.h"

class Mildred {
	private:
		static SDL_Renderer* renderer; 
		static SDL_Window* window;
		static int screenWidth, screenHeight, fieldOfView, viewDistance, frameCount; 
		static std::vector<MapBoundary>* mapBoundaries;
		static Uint64 ticks, prevFps; 

	public: 
		static bool isRunning;
		static Player* player; 
		static AssetManager* assetManager;
		static void Init(); 
		static void CreateWindow(std::string title, int width, int height);
		static void CreateRenderer();
		static void SetRenderDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		static void RenderPresent();
		static void RenderClear();
		static void DrawRect(int width, int height, int x, int y);
		static void CreateMapBoundary(int x, int y, int endX, int endY, std::string textureName);
		static void DrawMapBoundaries();
		static SDL_Renderer* GetRenderer();
		static void HandleUserInput();
		static void RenderWallSlice(double* lineCollisionPointer, int drawPoint, double rayAngleRad, int lineLenght, int lineStartX, int lineStartY, std::string textureName);
		static void CastRays(); 
		static void HandleEvents(); 
		static void DisplayFPS(); 
		static void DrawTempBackground();
};

