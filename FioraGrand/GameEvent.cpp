#include "GameEvent.h"

void GameEvent::AddEnemy()
{
    SDL_Rect *tmp_rect = new SDL_Rect;
    tmp_rect->w = 50;
    tmp_rect->h = 32;
    int last_y_pos = 30;

    for (int i = 1; i <= 12; i++)
    {
        tmp_rect->x = (rand() % 2 ? rand() % 400 : SCREEN_WIDTH - rand() % 400);
        tmp_rect->y = last_y_pos;
        last_y_pos += 50;

        // adding enemy

        enemies.push_back(Enemy(*tmp_rect));
    }
}


void GameEvent::Check_Player_And_Ghostball(Character& player, Enemy& ghostball, SDL_Renderer* renderer,
    Timer& time_manager, bool& is_mute)
{
    Uint32 current_time = time_manager.get_current_time();
    if (current_time - shield_time >= SHIELD_TIME)
        player.shield_state = false;
    if (CheckCollision(*player.Get_Hitbox(), *ghostball.Get_Rect()) && !player.shield_state)
    {
        ghostball.is_bang = true;
        if (!is_mute) Mix_PlayChannel(-1, explosion_sound, 0);
        ghostball.explosion_rect->x = ghostball.Get_Rect()->x;
        ghostball.explosion_rect->y = ghostball.Get_Rect()->y;

        ghostball.Get_Rect()->x = 0;

        player.current_heart_frame ++;
        if (player.current_heart_frame == HEART_FRAME)
        {
             player.id = "death";
             player.current_heart_frame = HEART_FRAME;
        }
        player.shield_state = true;
        shield_time = current_time;
    }
}

void GameEvent::AddGhost()
{
    for (int i = 1; i <= 2; i++)
    {
        ghosts.push_back(Ghost());
    }
}

void GameEvent::CallSword(MouseCursor& mouse, CyberSword& cybersword, Timer& time_manager)
{
    Uint32 current_time = time_manager.get_current_time();
    if (current_time - cooldown_time > SWORD_COOLDOWN_TIME) ulti_state = "ultimate";

    if (mouse.is_call && ulti_state == "ultimate")
    {
        cybersword.get_rect()->x = mouse.Mouse_Rect.x + mouse.Mouse_Rect.w/5 - 4;
        cybersword.get_rect()->y = WAITFORCALL;
        cooldown_time = current_time;
        ulti_state = "ultimate_gray";

        mouse.is_call = false;
    }
}

bool GameEvent::Check_PLayer_And_Ghost(Character& player, Ghost& ghost, Timer& time_manager)
{
    Uint32 current_time = time_manager.get_current_time();
    if (CheckCollision(*player.Get_Hitbox(), *ghost.Get_Rect()) && !player.shield_state)
    {
        player.current_heart_frame++;
        if (player.current_heart_frame == HEART_FRAME)
        {
            player.id = "death";
            player.current_heart_frame = HEART_FRAME;
        }
        player.shield_state = true;
        shield_time = current_time;
    }
    return false;
}


void GameEvent::Kill_Ghost(CyberSword& cybersword, bool& is_mute)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        if (CheckCollision(*cybersword.get_rect(), *enemies[i].Get_Rect()))
        {
            enemies[i].explosion_rect->x = enemies[i].Get_Rect()->x;
            enemies[i].explosion_rect->y = enemies[i].Get_Rect()->y;

            enemies[i].is_bang = true;
            if (!is_mute) Mix_PlayChannel(-1, explosion_sound, 0);
            enemies[i].Get_Rect()->x = -50;
            enemies[i].Get_Rect()->y = rand() % SCREEN_HEIGHT;
        }
    }
    for (int i = 0; i < ghosts.size(); i++)
    {
        if (CheckCollision(*cybersword.get_rect(), *ghosts[i].Get_Rect()))
        {
            ghosts[i].ghost_state = GHOST_DEATH;
        }
    }
}

void GameEvent::Reset_Event(SDL_Renderer* renderer) {
    ghosts.resize(0);
    AddGhost();
    for (auto& ghost : ghosts) {
        ghost.m_ghost_frame.Load_Texture_From_Path("asset/Ghost.png", "ghost", renderer);
        ghost.m_ghost_frame.Load_Texture_From_Path("asset/Ghost_Death.png", "ghost_death", renderer);
    }
    
    for (auto& enemy : enemies) {
        enemy.reset_x_pos();
   }
}









