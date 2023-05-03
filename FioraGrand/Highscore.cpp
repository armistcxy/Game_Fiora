#include "Highscore.h"

void Highscore::Init() {
	int y = 250;
	for (int i = 0; i < 5; i++) {
		highscore_rect[i].x = 580;
		highscore_rect[i].y = y;
		highscore_rect[i].w = 100;
		highscore_rect[i].h = 50;

		index_rect[i].x = 500;
		index_rect[i].y = y;
		index_rect[i].w = 25;
		index_rect[i].h = 50;
		y += 50;
	}
}
void Highscore::Render_highscore_title(SDL_Renderer* renderer){
	highscore_title.Render_Text(renderer, "G.O.A.T", highscore_title.MediumSize, title_color, &title_rect);
}

void Highscore::Get_Highscore_From_Past() {
	#pragma warning(suppress : 4996)
	freopen("highscore.txt", "r", stdin);
	for (int i = 0; i < 5; i++) {
		std::cin >> highscore_array[i]; 
	}
}

void Highscore::Update_Highscore(double current_score) {
	
	Get_Highscore_From_Past();
	#pragma warning(suppress : 4996)
	freopen("highscore.txt", "w", stdout);
	for (int i = 0; i < 5; i++) {
		if (current_score > highscore_array[i]) {
			is_higher = true;
			std::cout << current_score << '\n';
			for (int j = i + 1; j < 5; j++) {
				highscore_array[j] = highscore_array[j - 1];
				std::cout << highscore_array[j] << '\n';
			}
			highscore_array[i] = current_score;
			return;
		}
		else std::cout << highscore_array[i] << '\n';
	}
}

void Highscore::Render_highscore_point(SDL_Renderer* renderer){
	for (int i = 0; i < 5; i++) {
		current_score = std::to_string(highscore_array[i]);
		current_score.resize(4);
		current_index = std::to_string(i + 1);
		highscore_table[i].Render_Text(renderer, current_index.c_str(), highscore_table[i].SmallSize, highscore_color, &index_rect[i]);
		highscore_table[i].Render_Text(renderer, current_score.c_str(), highscore_table[i].SmallSize, highscore_color, &highscore_rect[i]);
	}
}