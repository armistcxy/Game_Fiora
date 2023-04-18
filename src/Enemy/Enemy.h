#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>
#include "LoadTexture.h"
#include "GameProp.h"
const int GHOSTBALL_FRAMES = 4;
class Enemy
{
   public:
        Enemy(){};
        Enemy(SDL_Rect tmp_rect);
        LoadTexture m_enemy_frame;
        SDL_Rect* Get_Rect();
        SDL_RendererFlip flip_flag;
        int current_frame;

        void update_pos();
        int time_boost;
    private:
        SDL_Rect* m_rect;
        int enemy_speed;
};

#endif // ENEMY_H
