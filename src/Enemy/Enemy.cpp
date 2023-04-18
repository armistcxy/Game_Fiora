#include "Enemy.h"

Enemy::Enemy(SDL_Rect tmp_rect)
{
    m_rect = new SDL_Rect;
    m_rect->x = tmp_rect.x;
    m_rect->y = tmp_rect.y;
    m_rect->w = tmp_rect.w;
    m_rect->h = tmp_rect.h;
    enemy_speed = 0;
    time_boost = 1000;
    current_frame = 0;
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
        if (m_rect->x + m_rect->w + enemy_speed > 1260)
        {
            m_rect->x = 0;
        }
    }
    else
    {
        m_rect->x -= enemy_speed;
        if (m_rect->x < 0)
        {
            m_rect->x = 1260;
        }
    }
    current_frame = (SDL_GetTicks() / 50) % GHOSTBALL_FRAMES;

    enemy_speed = SDL_GetTicks() / 7000 + 1;
}
