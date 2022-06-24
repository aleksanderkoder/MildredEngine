#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "Asset.h"

class AssetManager
{
	public:
		std::vector<Asset>* assets;
		AssetManager(); 
		void CreateAsset(std::string name, std::string type, std::string url);
		void LoadTexture(Asset& a); 
		SDL_Texture* GetTextureByName(std::string name);
		void PrintAllAssetInfo();
};

