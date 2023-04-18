#ifndef CHARACTER_H
#define CHARACTER_H

#include "SDL.h"
#include "SDL_image.h"
#include "LoadTexture.h"
#include "Vector2D.h"
#include "GameProp.h"
#include <map>
#include <vector>

enum X_POS_STATE
{
    X_LEFT,
    X_RIGHT,
    X_STAND
};
enum Y_POS_STATE
{
    Y_LEFT,
    Y_RIGHT,
    Y_STAND
};

enum CHARACTER_STATE
{
    IDLE,
    RUN_LEFT,
    RUN_RIGHT,
    JUMPING
};

enum ATTACK_STATE
{
    ATTACK1,
    ATTACK2,
    NOT_ATTACK
};
class Character
{
public:
    Character();

    // frames stuff
    LoadTexture m_character_frame;
    int current_frame;
    int max_frame;
    SDL_Rect* Get_Rect();
    SDL_RendererFlip flip_flag;
    std::string id;

    // position and event
    void Update_Position(float dt);
    void Character_Handle(SDL_Event& event);

    void set_y_vel(float replace_y_vel);
    void set_y_pos(float replace_y_pos);
    float get_y_vel();

    bool is_jumpping;
    int character_state;
    bool shield_state = false;

    // heart
    LoadTexture heart_player;
    int current_heart_frame;
    int tot_frame;

    //shield
    LoadTexture shield_texture;
    int current_shield_frame;
    SDL_Rect* shield_rect;
    void shield_call(SDL_Renderer* renderer);
    // collision
    SDL_Rect* Get_Hitbox();
    std::vector<SDL_Rect> blocks {{75,178,130,30},{25,358,75,30},{75,460,150,30},{226,255,175,30},
        {275,410,125,30}, {480,330,75,30}, {455,510,100,30}, {680,180,150,30}, {605,255,75,30},
        {605,410,175,30}, {605,590,50,50}, {655,590,50,10}, {805,512,75,30}, {855,332,155,30},
        {1032,255,100,30}, {905,127, 130,30}, {1110, 75, 125, 30}};
private:
    // rectangle texture
    SDL_Rect* m_rect;

    // collision
    SDL_Rect* m_hitbox;

    // position and event
    Vector2D player_vel;
    Vector2D player_acc;
    Vector2D player_pos;

};

#endif // CHARACTER_H
