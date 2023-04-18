#include "CyberSword.h"

CyberSword::CyberSword()
{
    m_sword_rect = new SDL_Rect;
    m_sword_rect->x = SWORD_X_START;
    m_sword_rect->y = SWORD_Y_START;
    m_sword_rect->w = SWORD_WIDTH;
    m_sword_rect->h = SWORD_HEIGHT;

    tail_rect = new SDL_Rect;
    tail_rect->x = SWORD_X_START;
    tail_rect->y = SWORD_Y_START;
    tail_rect->w = SWORD_TAIL_WIDTH;
    tail_rect->h = SWORD_TAIL_HEIGHT;

    current_tail_frame = 0;
    cooldown_time = 0.f;
}

void CyberSword::update_sword()
{
    m_sword_rect->y += SWORD_GRAVITY;
    if (m_sword_rect->y >= SCREEN_HEIGHT) m_sword_rect->y = SCREEN_HEIGHT + SWORD_TAIL_HEIGHT ;

    tail_rect->x = m_sword_rect->x;
    tail_rect->y = m_sword_rect->y - tail_rect->h;

    current_tail_frame++;
    if (current_tail_frame >= SWORD_DELAY_FRAME * SWORD_TAIL_FRAMES) {
        current_tail_frame = 0;
    }
}
