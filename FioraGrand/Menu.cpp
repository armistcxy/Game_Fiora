#include "Menu.h"
void Menu::background_render(SDL_Renderer* renderer) {
	menu_texture.Render(renderer, "menu", START_POINT, SCREEN_WIDTH, SCREEN_HEIGHT);
}