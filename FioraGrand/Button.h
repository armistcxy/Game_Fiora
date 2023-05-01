#ifndef BUTTON_H
#define BUTTON_H
#include <SDL.h>
#include <iostream>
#include <string>
#include "GameProp.h"
#include "LoadTexture.h"
#include "Collision.h"
#include "MouseCursor.h"
enum BUTTON_TYPE
{
	PLAY,
	SETTING,
	RESTART,
	HOME,
	INFO,
	HIGHSCORE,
	EXIT
};
class Button {
public:
	Button();

	void Render_button(SDL_Renderer* renderer, std::string id);
	void Handle_event(SDL_Event* event);
	void Set_position();
	void Init_position(int x, int y);

	bool Light_or_Dark();
	SDL_Rect* Get_Rect();

	LoadTexture button_texture;
	SDL_Rect mouse_rect;

private:
	SDL_Rect* button_rect;

};
#endif