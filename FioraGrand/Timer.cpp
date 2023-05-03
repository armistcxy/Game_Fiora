#include "Timer.h"

void Timer::get_time()
{
    // fps stable
    m_delta_time = (SDL_GetTicks() - game_start_time - pause_time - m_prev_time) * (FPS / 1000.0f);

    if (m_delta_time > TARGET_DELTA_TIME)
    {
        m_delta_time = TARGET_DELTA_TIME;
    }

    m_prev_time = SDL_GetTicks() - game_start_time - pause_time; // SDL_GetTicks return Uint32 type
}

void Timer::update_time() {
    current_time = SDL_GetTicks();
}
void Timer::update_pause_start_time() {
    pause_start_time = SDL_GetTicks();
}
void Timer::update_pause_end_time() {
    pause_end_time = SDL_GetTicks();
    pause_time += pause_end_time - pause_start_time;
}
void Timer::game_time(int& game_state, bool is_pause) {
    if (game_state != GAME_PLAY) {
        game_start_time = SDL_GetTicks();
        current_time = 0;
    }
    else {
        current_time = SDL_GetTicks() - game_start_time - pause_time;
    }
}