#ifndef MOUSECURSOR_H
#define MOUSECURSOR_H

#include "LoadTexture.h"
class MouseCursor
{
    public:
        MouseCursor();
        LoadTexture Mouse_Texture;
        SDL_Rect Mouse_Rect;
        void Update(SDL_Event& event);

        void Sword_Falling();

        bool is_call;

};

#endif // MOUSECURSOR_H
