#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>
#include "GameProp.h"
const int FPS = 60;
const int TARGET_DELTA_TIME = 1;

class Timer
{
    public:
        Timer(){};
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

        void update_pause_start_time();
        void update_pause_end_time();
        int64_t game_start_time;
        int64_t pause_time;
    private:
       float m_delta_time, m_prev_time;
       
       float current_time = 0.;

        
       int64_t pause_start_time;
       int64_t pause_end_time;
};

#endif // TIMER_H
