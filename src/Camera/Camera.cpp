#include "Camera.h"

Camera::Camera()
{
    camera_rect.x = 0;
    camera_rect.y = 0;
    camera_rect.w = 500;
    camera_rect.h = 450;
}

void Camera::Update_camera(SDL_Rect* p_rect)
{
    camera_rect.x = p_rect->x - 300;
    camera_rect.y = p_rect->y - 100;

    if (camera_rect.x < 0) camera_rect.x = 0;
    if (camera_rect.y < 0) camera_rect.y = 0;
    if (camera_rect.x > 1200 - camera_rect.w) camera_rect.x = 1200 - camera_rect.w;
    if (camera_rect.y > 800 - camera_rect.h) camera_rect.y = 800 - camera_rect.h;


}
