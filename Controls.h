#pragma once
#include <string>

using namespace std; 

class Controls
{
	public:
		string type; 
		int width, height, x, y;
};

class Button: public Controls {
	public:
		string label; 
		Button(string label, int width, int height, int x, int y); 
};

