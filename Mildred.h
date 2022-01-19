// HEADER FILE
// Contains class specification 
#ifndef MILDRED_H
#endif MILDRED_H

#include <iostream>
#include <SDL.h>
#include <list>
#include "MapLine.h"
#include "Player.h"

using namespace std;

class Mildred {
	private:
		static SDL_Renderer* renderer; 
		static SDL_Window* window;
		static int screenWidth, screenHeight, fieldOfView, sightDistance; 
		static std::list<MapLine>* mapLines; 

	public: 
		static bool isRunning;
		static Player* player; 
		static void Init(); 
		static void CreateWindow(string title, int width, int height); 
		static void CreateRenderer();
		static void SetRenderDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		static void RenderPresent();
		static void RenderClear();
		static void DrawRect(int width, int height, int x, int y);

		class Calc {
			public:
				static double ToRadians(int deg) {
					
					return (deg * (std::atan(1.0) * 4)) / 180;
				}
	};
};

