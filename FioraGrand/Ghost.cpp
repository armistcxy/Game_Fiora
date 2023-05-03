#include "Ghost.h"

Ghost::Ghost()
{
    // set up for random spawn place and size of ghost
    m_rect = new SDL_Rect;
    m_rect->x = (rand() % 2 ? rand() % 300 : SCREEN_WIDTH - rand() % 300);
    m_rect->y = rand() % (SOLID_FLOOR - 400);

    m_rect->w = GHOST_WIDTH;
    m_rect->h = GHOST_HEIGHT;

    // frame, state, movement stuffs
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
    // get the distance beetween player and ghost
    int distance = sqrt((player->Get_Hitbox()->x - m_rect->x) * (player->Get_Hitbox()->x - m_rect->x)
                        + (player->Get_Hitbox()->y - m_rect->y) * (player->Get_Hitbox()->y - m_rect->y));
    
    // if player near the ghost, ghost chase her
    if (ghost_state != GHOST_DEATH) {
        if (distance < BOUND_DISTANCE)
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

        // if not, ghost go around in straight line
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

        // not go out of bound
        if (m_rect->x > SCREEN_WIDTH) flip_flag = SDL_FLIP_HORIZONTAL;
        else if (m_rect->x < 0) flip_flag = SDL_FLIP_NONE;
    }

    
    
    // death state
    if (ghost_state == GHOST_DEATH)
    {
        max_frames = GHOST_DEATH_FRAME;
        id = "ghost_death";
        m_rect->y += 5;

        if (m_rect->y >= BACK_FROM_HELL) {
            ghost_state = GHOST_FLY;
            max_frames = GHOST_FLY_FRAME;
            id = "ghost";
            m_rect->x = -50;
            m_rect->y = rand() % (SCREEN_HEIGHT - m_rect->w);
            
        }
    }

    total_frames++;
    if (ghost_state != GHOST_DEATH) {
        if (total_frames >= max_frames * 10) total_frames = 0;

        current_frame = total_frames / 10;
    }
    else {
        current_frame = total_frames / 30; 
    }
    
}

