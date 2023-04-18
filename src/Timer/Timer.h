#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

const int FPS = 60;
const int TARGET_DELTA_TIME = 1;

class Timer
{
    public:
        Timer(){};
        void get_time();

        float get_delta_time(){return m_delta_time;}

    private:
       float m_delta_time, m_prev_time;
};

#endif // TIMER_H
