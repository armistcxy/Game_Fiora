#include "Timer.h"

void Timer::get_time()
{
    // fps stable
    m_delta_time = (SDL_GetTicks() - m_prev_time) * (FPS / 1000.0f);

    if (m_delta_time > TARGET_DELTA_TIME)
    {
        m_delta_time = TARGET_DELTA_TIME;
    }

    m_prev_time = SDL_GetTicks(); // SDL_GetTicks return Uint32 type
}

void Timer::update_time() {
    current_time = SDL_GetTicks();
}