#ifndef GHOST_H
#define GHOST_H

#include <SDL.h>
#include "Character.h"
#include "GameProp.h"
#include "cmath"
const int GHOST_FLY_FRAME = 6;
const int GHOST_DEATH_FRAME = 5;

enum GHOST_STATE
{
    GHOST_FLY,
    GHOST_DEATH
};
class Ghost
{
    public:
        Ghost();
        LoadTexture m_ghost_frame;
        SDL_Rect* Get_Rect();
        int current_frame;
        SDL_RendererFlip flip_flag;

        void update_pos(Character* player);

        int ghost_state;
        std::string id;

    private:
        SDL_Rect* m_rect;
        int x_vel, y_vel;
};

#endif // GHOST_H
