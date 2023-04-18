#include "Ghost.h"

Ghost::Ghost()
{
    m_rect = new SDL_Rect;
    m_rect->x = rand() % 1200;
    m_rect->y = rand() % 700;
    m_rect->w = 64;
    m_rect->h = 44;
    current_frame = 0;
    id = "ghost";
    ghost_state = GHOST_FLY;
    x_vel = 1, y_vel = 1;
}
SDL_Rect* Ghost::Get_Rect()
{
    return m_rect;
}

void Ghost::update_pos(Character* player)
{
    int distance = sqrt((player->Get_Hitbox()->x - m_rect->x) * (player->Get_Hitbox()->x - m_rect->x)
                        + (player->Get_Hitbox()->y - m_rect->y) * (player->Get_Hitbox()->y - m_rect->y));
    if (distance < 300)
    {
        if (player->Get_Hitbox()->x > m_rect->x)
        {
            m_rect->x += x_vel;
            flip_flag = SDL_FLIP_NONE;
        }
        else
        {
            m_rect->x -= x_vel;
            flip_flag = SDL_FLIP_HORIZONTAL;
        }

        if (player->Get_Hitbox()->y > m_rect->y)
        {
            m_rect->y += y_vel;
        }
        else m_rect->y -= y_vel;
    }

    else
    {
        if (flip_flag == SDL_FLIP_NONE)
        {
            m_rect->x += x_vel;
        }
        else
        {
            m_rect->x -= x_vel;
        }

    }

    if (m_rect->x > 1260) flip_flag = SDL_FLIP_HORIZONTAL;
    else if (m_rect->x <0) flip_flag = SDL_FLIP_NONE;

    if (ghost_state == GHOST_FLY)
    {
        current_frame = (SDL_GetTicks() / 50) % GHOST_FLY_FRAME;
    }

    else if (ghost_state ==  GHOST_DEATH)
    {
        current_frame++;
        if(current_frame >= GHOST_DEATH_FRAME) current_frame = GHOST_DEATH_FRAME;
        id = "ghost_death";
    }

}

