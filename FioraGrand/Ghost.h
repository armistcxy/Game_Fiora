#ifndef GHOST_H
#define GHOST_H

#include <SDL.h>
#include "Character.h"
#include "GameProp.h"
#include "cmath"

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
        int total_frames = 0;
        int max_frames = GHOST_FLY_FRAME;
};

#endif // GHOST_H
