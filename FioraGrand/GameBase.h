#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <iostream>
#include <string>

#include "LoadTexture.h"
#include "GameEvent.h"
#include "Character.h"
#include "Timer.h"
#include "Ghost.h"
#include "MouseCursor.h"
#include "CyberSword.h"
#include "Font.h"


static const char* WINDOW_TITLE = "FIORA GRAND CHALLENGE";


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_renderer = NULL;
static GameEvent game_update;
static bool is_running = true;
static LoadTexture g_background;
static Timer time_manage;
static Character player;
static MouseCursor mouse;
static CyberSword sword;
static Font game_font;
static std::string show_time;
static float time_to_sec;
static SDL_Color time_color = { 255,0,0,100 };
static SDL_Rect time_rect = { SCREEN_WIDTH / 2 - TIME_SHOW_SIZE, 0, TIME_SHOW_SIZE, TIME_SHOW_SIZE };
