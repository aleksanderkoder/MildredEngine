#pragma once
#include <string>
#include <SDL.h>

using namespace std;

class Asset
{
public:
	string name;
	string type;
	string url;
	SDL_Texture* tex; 
	Asset(string name, string type, string url);
};

