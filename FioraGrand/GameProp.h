#ifndef GAMEPROP_H
#define GAMEPROP_H

#define START_POINT 0, 0
#define DEFAULT_PLAYER_POS 500


#define DELAY_CONSTANT 50
#define CHARACTER_DELAY 8
#define EXPLOSION_DELAY 10
#define SWORD_DELAY_FRAME 12
#define MAX_HEAL 4

#define HEART_PROPS 0, 669, 51, 51
#define SWORD_PROPS 200, 656, 64, 64
#define GHOSTBALL_SIZE 56, 56
#define SHIELD_SIZE 175
#define TIME_SHOW_SIZE 64
#define SWORD_TAIL_WIDTH 45
#define SWORD_TAIL_HEIGHT 90

#define GET_CENTER_SHIELD_X 65
#define GET_CENTER_SHIELD_Y 70 

#define ACC_PLAYER_X  7.f
#define ACC_PLAYER_Y  -15.f

#define VEL_PLAYER_START 0.f
#define TIME_TO_SEC 1000.f

#define INCREASE_SPEED_TIME 7000

const int SCREEN_WIDTH = 1260;
const int SCREEN_HEIGHT = 720;

const int SOLID_FLOOR = 640;
const int DELAY = 50;

const int WAITFORCALL = -150;

// for player
const int FRAME_SIZE = 180;

const int PLAYER_WIDTH = 30;
const int PLAYER_HEIGHT = 45;

const int GRAVITY = 1;
const int IDLE_FRAMES = 10;
const int JUMP_FRAMES = 2;
const int RUN_FRAMES = 7;
const int DEATH_FRAMES = 10;

const int HEART_SIZE = 17;

//ghost
const int BOUND_DISTANCE = 300;
const int GHOST_FLY_FRAME = 6;
const int GHOST_DEATH_FRAME = 5;
const int GHOST_WIDTH = 64;
const int GHOST_HEIGHT = 44;

//enemy
const int EXPLOSION_SIZE = 96;
const int GHOSTBALL_FRAMES = 4;
const int EXPLOSION_FRAMES = 11;

// sword
const int SWORD_TAIL_FRAMES = 8;
#endif // GAMEPROP_H
