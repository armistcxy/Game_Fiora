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
#include "Button.h"
#include "Menu.h"
#include "Pause_screen.h"

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
static Font game_title;
static std::string show_time;
static float time_to_sec;
static SDL_Color time_color = { 255,0,0,100 };
static SDL_Color game_title_color = { 190,230,127,200};
static SDL_Rect time_rect = { SCREEN_WIDTH / 2 - TIME_SHOW_SIZE, 0, TIME_SHOW_SIZE, TIME_SHOW_SIZE };
static SDL_Rect game_title_rect = { SCREEN_WIDTH / 2 - GAME_TITLE_WIDTH / 2, 68, GAME_TITLE_WIDTH, GAME_TITLE_HEIGHT };
static Button play_button, exit_button, setting_button, highscore_button, pause_button;
static int game_state = GAME_MENU;
static Menu menu;
static LoadTexture game_title_span;
static Pause_screen pause_manager;