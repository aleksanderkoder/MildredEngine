#include "AssetManager.h"
#include "Mildred.h"

AssetManager::AssetManager() {
	AssetManager::assets = new vector<Asset>(); 
}

void AssetManager::CreateAsset(string name, string type, string url) {
	Asset a(name, type, url);
	LoadTexture(a);
	assets->push_back(a);
}

void AssetManager::LoadTexture(Asset& a) {
	if (!a.tex) {
		const char* u = a.url.c_str();
		SDL_Surface* image = SDL_LoadBMP(u);
		if (!image) {
			cout << SDL_GetError() << endl;
			return; 
		}
		a.tex = SDL_CreateTextureFromSurface(Mildred::GetRenderer(), image);
		SDL_FreeSurface(image);
		image = NULL;
		cout << "Texture: " << a.name << " has been loaded!" << endl;
	}
	else {
		cout << "Texture: " << a.name << " has already been loaded!" << endl; 

	}
}

SDL_Texture* AssetManager::GetTextureByName(string name) {
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
		cout << "Asset " << i + 1 << ":" << endl << a.name << endl << a.type << endl << a.url << endl;
		if (a.tex) {
			cout << "Texture set!" << endl;
		}
		else {
			cout << "Texture not set!" << endl;
		}
	}
}