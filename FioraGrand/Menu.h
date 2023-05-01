#ifndef MENU_H
#define MENU_H
#include "LoadTexture.h"
#include "GameProp.h"

class Menu {
public:
	LoadTexture menu_texture;

	void background_render(SDL_Renderer* renderer);
};
#endif // !MENU_H;

// high score
// freopen file skill
// instruction
// text
// play button
// 
// setting
// exit button