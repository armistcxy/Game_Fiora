#ifndef CYBERSWORD_H
#define CYBERSWORD_H
#include "LoadTexture.h"

#define SWORD_GRAVITY 4
class CyberSword
{
    public:
        CyberSword();
        LoadTexture m_sword_texture;
        SDL_Rect* get_rect(){return m_sword_rect;}
        void update_sword();
        float cooldown_time;
    private:
        SDL_Rect *m_sword_rect;
};

#endif // CYBERSWORD_H
