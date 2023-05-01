#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include "GameProp.h"
#include "Enemy.h"
#include "Character.h"
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "Ghost.h"
#include "CyberSword.h"
#include "MouseCursor.h"
#include "Collision.h"
#include "Timer.h"
class GameEvent
{
public:
    GameEvent() {};

    void AddEnemy();
    void AddGhost();

    void Check_Player_And_Ghostball(Character& player, Enemy& ghostball, SDL_Renderer* renderer,
                                    Timer& time_manage);

    bool Check_PLayer_And_Ghost(Character& player, Ghost& ghost);

    void CallSword(MouseCursor& mouse, CyberSword& cybersword);
    std::vector<Enemy> enemies;
    std::vector<Ghost> ghosts;

    void Kill_Ghost(CyberSword& cybersword);
    float shield_time = 0.f;
    float cooldown_time = 0.f;
    std::string ulti_state = "ultimate";
    LoadTexture ultimate;
};

#endif // GAMEEVENT_H