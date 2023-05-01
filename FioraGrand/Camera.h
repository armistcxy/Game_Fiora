#ifndef CAMERA_H
#define CAMERA_H
#include "Character.h"

class Camera
{
    public:
        Camera();
        SDL_Rect camera_rect;
        void Update_camera(SDL_Rect* player_rect);
};

#endif // CAMERA_H
