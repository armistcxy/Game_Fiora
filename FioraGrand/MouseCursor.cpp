#include "MouseCursor.h"

MouseCursor::MouseCursor()
{
    // mouse cursor properties
    Mouse_Rect.x = 0;
    Mouse_Rect.y = 0;
    Mouse_Rect.w = 64;
    Mouse_Rect.h = 64;
    is_call = false;

}


void MouseCursor::Update(SDL_Event& event)
{
    // get current position
    int x, y;
    SDL_GetMouseState(&x, &y);

    // update position for rect
    Mouse_Rect.x = x;
    Mouse_Rect.y = y;
    is_call = false;

    // mouse click event
    if (event.type == SDL_MOUSEBUTTONDOWN){
        is_call = true;
    }

}


