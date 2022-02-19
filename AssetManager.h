#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "Asset.h"
using namespace std;

class AssetManager
{
public:
	vector<Asset>* assets; 
	AssetManager(); 
	void CreateAsset(string name, string type, string url);
	void LoadTexture(Asset& a); 
	SDL_Texture* GetTextureByName(string name); 
	void PrintAllAssetInfo();
};

