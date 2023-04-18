#include "CyberSword.h"

CyberSword::CyberSword()
{
    m_sword_rect = new SDL_Rect;
    m_sword_rect->x = -500;
    m_sword_rect->y = 0;
    m_sword_rect->w = 44;
    m_sword_rect->h = 128;
    cooldown_time = 0.f;
}

void CyberSword::update_sword()
{
    m_sword_rect->y += SWORD_GRAVITY;
    if (m_sword_rect->y >= 1500) m_sword_rect->y = 1500;
}
