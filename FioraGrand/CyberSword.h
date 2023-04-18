#ifndef CYBERSWORD_H
#define CYBERSWORD_H
#include "LoadTexture.h"
#include "GameProp.h"

#define SWORD_GRAVITY 6
#define SWORD_X_START -500
#define SWORD_Y_START 0
#define SWORD_WIDTH 44
#define SWORD_HEIGHT 128

class CyberSword
{
    public:
        CyberSword();
        LoadTexture m_sword_texture;
        SDL_Rect* get_rect(){return m_sword_rect;}

        SDL_Rect* tail_rect;
        int current_tail_frame;

        void update_sword();
        float cooldown_time;
    private:
        SDL_Rect *m_sword_rect;
};

#endif // CYBERSWORD_H
