#include "AssetManager.h"
#include "Mildred.h"

AssetManager::AssetManager() {
	AssetManager::assets = new std::vector<Asset>();
}

void AssetManager::CreateAsset(std::string name, std::string type, std::string url) {
	Asset a(name, type, url);
	LoadTexture(a);
	assets->push_back(a);
}

void AssetManager::LoadTexture(Asset& a) {
	if (!a.tex) {
		const char* u = a.url.c_str();
		SDL_Surface* image = SDL_LoadBMP(u);
		if (!image) {
			std::cout << SDL_GetError() << std::endl;
			return; 
		}
		a.tex = SDL_CreateTextureFromSurface(Mildred::GetRenderer(), image);
		SDL_FreeSurface(image);
		image = NULL;
		std::cout << "Texture: " << a.name << " has been loaded!" << std::endl;
	}
	else {
		std::cout << "Texture: " << a.name << " has already been loaded!" << std::endl;

	}
}

SDL_Texture* AssetManager::GetTextureByName(std::string name) {
	for (int i = 0; i < assets->size(); i++) {
		if ((*assets)[i].name == name) {
			return (*assets)[i].tex; 
		}
	}
	return NULL; 
}

void AssetManager::PrintAllAssetInfo() {
	for (int i = 0; i < assets->size(); i++) {
		Asset a = (*assets)[i]; 
		std::cout << "Asset " << i + 1 << ":" << std::endl << a.name << std::endl << a.type << std::endl << a.url << std::endl;
		if (a.tex) {
			std::cout << "Texture set!" << std::endl;
		}
		else {
			std::cout << "Texture not set!" << std::endl;
		}
	}
}