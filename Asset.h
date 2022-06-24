#pragma once
#include <string>
#include <SDL.h>

class Asset
{
	public:
		std::string name;
		std::string type;
		std::string url;
		SDL_Texture* tex; 
		Asset(std::string name, std::string type, std::string url);
};

