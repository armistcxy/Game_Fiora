#ifndef FONT_H
#define FONT_H
#include "SDL_ttf.h"
#include <iostream>
class Font{
public:
	Font();
	TTF_Font* g_font;
	TTF_Font* BigSize;
	TTF_Font* MediumSize; 
	TTF_Font* SmallSize;

	bool Get_Font_Type_and_Size(TTF_Font* font, const char* font_name, int size);
	bool Load_Font();
	bool Render_Text(SDL_Renderer* renderer, const char* text, TTF_Font* font, SDL_Color text_color, SDL_Rect* rect);

	int g_width, g_height;
	SDL_Texture* g_texture;
};
#endif // FONT_H
