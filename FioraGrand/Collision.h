#pragma once
#include "SDL.h"
static bool CheckCollision(const SDL_Rect& rect1, const SDL_Rect& rect2)
{
    int left1 = rect1.x;
    int right1 = rect1.x + rect1.w;
    int top1 = rect1.y;
    int bot1 = rect1.y + rect1.h;

    int left2 = rect2.x;
    int right2 = rect2.x + rect2.w;
    int top2 = rect2.y;
    int bot2 = rect2.y + rect2.h;

    if (left1 > right2 || left2 > right1 || top1 > bot2 || top2 > bot1) return false;
    return true;
}