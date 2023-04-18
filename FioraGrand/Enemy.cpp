#include "Enemy.h"

Enemy::Enemy(SDL_Rect tmp_rect)
{
    // initialize enemy's properties
    m_rect = new SDL_Rect;
    m_rect->x = tmp_rect.x;
    m_rect->y = tmp_rect.y;
    m_rect->w = tmp_rect.w;
    m_rect->h = tmp_rect.h;

    // initialize explosion 
    explosion_rect = new SDL_Rect;
    explosion_rect->x = WAITFORCALL;
    explosion_rect->y = WAITFORCALL;
    explosion_rect->w = EXPLOSION_SIZE;
    explosion_rect->h = EXPLOSION_SIZE;

    // speed setting
    enemy_speed = 0;

    // not bang from start
    is_bang = false;

    //starting frame and random side
    current_frame = 0;
    current_explosion_frame = 0;
    flip_flag = (rand() % 2 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

SDL_Rect* Enemy::Get_Rect()
{
    return m_rect;
}
void Enemy::update_pos()
{
    if (flip_flag == SDL_FLIP_NONE)
    {
        m_rect->x += enemy_speed;
        if (m_rect->x + m_rect->w + enemy_speed > SCREEN_WIDTH)
        {
            m_rect->x = 0;
        }
    }
    else
    {
        m_rect->x -= enemy_speed;
        if (m_rect->x < 0)
        {
            m_rect->x = SCREEN_WIDTH;
        }
    }
    current_frame = (SDL_GetTicks() / DELAY_CONSTANT) % GHOSTBALL_FRAMES;
    
    if (is_bang) current_explosion_frame++;
    

    if (current_explosion_frame == EXPLOSION_FRAMES * EXPLOSION_DELAY) {
        explosion_rect->x = WAITFORCALL;
        explosion_rect->y = WAITFORCALL;
        current_explosion_frame = 0;
        is_bang = false;
    }
    enemy_speed = SDL_GetTicks() / INCREASE_SPEED_TIME + 1;
}

void Enemy::call_explosion(SDL_Renderer* renderer) {
    explosion_texture.RenderByFrame(renderer, "explosion", explosion_rect->x, explosion_rect->y,
        EXPLOSION_SIZE, EXPLOSION_SIZE, current_explosion_frame / EXPLOSION_DELAY);
}