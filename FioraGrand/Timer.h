#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>
#include "GameProp.h"
const int FPS = 60;
const int TARGET_DELTA_TIME = 1;

class Timer
{
    public:
        
        bool is_switch;
        void get_time();

        float get_delta_time(){
            return m_delta_time;
        }
        
        void update_time();

        void game_time(int& game_state,bool is_pause);
        float get_current_time() {
            return current_time;
        };

        void reset_time();

        void update_pause_start_time();
        void update_pause_end_time();
        Uint32 game_start_time;
        Uint32 pause_time;
    private:
       float m_delta_time, m_prev_time;
       
       float current_time = 0.;

        
       Uint32 pause_start_time;
       Uint32 pause_end_time;
};

#endif // TIMER_H
