#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include "LoadTexture.h"
#include "Font.h"
#include "Button.h"
#include <string>
#include <fstream>
class Highscore {
public:
	
	LoadTexture highscore_texture;
	double highscore_array[5];
	Font highscore_table[5];
	Font highscore_title;
	Button home_button;
	SDL_Color title_color = { 230,65,76,200 };
	SDL_Rect title_rect = { 575,115, 130, 75 };

	SDL_Rect highscore_rect[5];
	SDL_Rect index_rect[5];
	SDL_Color highscore_color = { 229, 18, 18, 200 };

	std::string current_score;
	std::string current_index;

	bool is_higher = false;

	void Init();

	void Get_Highscore_From_Past();

	void Update_Highscore(double current_score);

	void Render_highscore_title(SDL_Renderer* renderer);

	void Render_highscore_point(SDL_Renderer* renderer);
};
#endif
