#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include <iostream>


#include "LoadTexture.h"
#include "GameEvent.h"
#include "Character.h"
#include "Timer.h"
#include "Ghost.h"
#include "MouseCursor.h"
#include "CyberSword.h"



const char* WINDOW_TITLE = "FIORA GRAND CHALLENGE";


SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;
GameEvent game_update;
bool is_running = true;
LoadTexture g_background;
Timer time_manage;
Character player;
MouseCursor mouse;
CyberSword sword;



