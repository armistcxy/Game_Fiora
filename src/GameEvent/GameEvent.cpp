#include "GameEvent.h"

void GameEvent::AddEnemy()
{
    SDL_Rect *tmp_rect = new SDL_Rect;
    tmp_rect->w = 50;
    tmp_rect->h = 32;
    int last_y_pos = 30;
    for (int i = 1; i <= 10; i++)
    {
        tmp_rect->x = rand() % 1260;
        tmp_rect->y = last_y_pos;
        last_y_pos += 50;

        // adding enemy

        enemies.push_back(Enemy(*tmp_rect));
    }
}


bool GameEvent::CheckCollision(const SDL_Rect& rect1, const SDL_Rect& rect2)
{
    int left1 = rect1.x;
    int right1 = rect1.x + rect1.w;
    int top1 = rect1.y;
    int bot1 = rect1.y + rect1.h;

    int left2 = rect2.x;
    int right2 = rect2.x + rect2.w;
    int top2 = rect2.y;
    int bot2 = rect2.y + rect2.h;

    if (left1 > right2 || left2 > right1 || top1 > bot2 || top2 > bot1) return false;
    return true;
}

void GameEvent::Check_Player_And_Ghostball(Character& player, Enemy& ghostball)
{
    if (SDL_GetTicks() - shield_time >= 5000) player.shield_state = false;
    if (CheckCollision(*player.Get_Hitbox(), *ghostball.Get_Rect()) && !player.shield_state)
    {
        player.current_heart_frame ++;
        if (player.current_heart_frame == 4)
        {
             player.id = "death";
             player.current_heart_frame = 4;
        }
        player.shield_state = true;
        shield_time = SDL_GetTicks();
    }
}

void GameEvent::AddGhost()
{
    for (int i = 1; i <= 1; i++)
    {
        ghosts.push_back(Ghost());
    }
}

void GameEvent::CallSword(MouseCursor& mouse, CyberSword& cybersword)
{
    if (SDL_GetTicks() - cooldown_time > 5000) ulti_state = "ultimate";

    if (mouse.is_call && ulti_state == "ultimate")
    {
        cybersword.get_rect()->x = mouse.Mouse_Rect.x + mouse.Mouse_Rect.w/5 - 4;
        cybersword.get_rect()->y = - 150;
        cooldown_time = SDL_GetTicks();
        ulti_state = "ultimate_gray";

        mouse.is_call = false;
    }
}

bool GameEvent::Check_PLayer_And_Ghost(Character& player, Ghost& ghost)
{
    if (CheckCollision(*player.Get_Hitbox(), *ghost.Get_Rect()))
    {
       player.current_heart_frame ++;
       if (player.current_heart_frame == 6) player.id = "death";
    }

}


void GameEvent::Kill_Ghost(CyberSword& cybersword)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        if (CheckCollision(*cybersword.get_rect(), *enemies[i].Get_Rect()))
        {
            enemies[i].Get_Rect()->x = -50;
            enemies[i].Get_Rect()->y = rand() % 600;
        }
    }
    for (int i = 0; i < ghosts.size(); i++)
    {
        if (CheckCollision(*cybersword.get_rect(), *ghosts[i].Get_Rect()))
        {
            ghosts[i].Get_Rect()->x = rand() % 1260;
            ghosts[i].Get_Rect()->y = rand() % 600;
        }
    }
}










