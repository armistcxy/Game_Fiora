#include "Character.h"
Character::Character()
{
    // default rectangle for frames properties
    m_rect = new SDL_Rect;
    m_rect->x = 400;
    m_rect->y = 500;
    m_rect->w = FRAME_SIZE;
    m_rect->h = FRAME_SIZE;

    // default hit box properties
    m_hitbox = new SDL_Rect;
    m_hitbox->x = 400;
    m_hitbox->y = 500;
    m_hitbox->w = PLAYER_WIDTH;
    m_hitbox->h = PLAYER_HEIGHT;

    // default position, velocity, acceleration
    player_pos.x = 500.f;
    player_pos.y = 500.f;

    player_vel.x = 0.f;
    player_vel.y = 0.f;

    player_acc.x = 7.f;
    player_acc.y = -15.f;

    // default state
    character_state = IDLE;
    id = "idle";
    current_frame = 0;
    tot_frame = 0;

    max_frame = IDLE_FRAMES;

    is_jumpping = false;
    current_heart_frame = 0;
}

SDL_Rect* Character::Get_Rect()
{
    return m_rect;
}

SDL_Rect* Character::Get_Hitbox()
{
    return m_hitbox;
}

// position and event
void Character::Character_Handle(SDL_Event& event)
{
    // get keystate from keyboard
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    // if no input from keyboard;
    if (id == "death")
    {
        tot_frame++;
        current_frame = tot_frame / 8;
        if (current_frame > max_frame) current_frame = max_frame;
        player_vel.x = 0, player_vel.y = 0;
        if (id == "death") max_frame = DEATH_FRAMES;
        return;
    }

    player_vel.x = 0.f;
    if (is_jumpping) id = "jump";
    else id = "idle";
    tot_frame++;

    // left move
    if (keystate[SDL_SCANCODE_D])
    {
        player_vel.x += player_acc.x;
        id = "run";
        flip_flag = SDL_FLIP_NONE;
        max_frame = JUMP_FRAMES;
    }

    // right move
    if (keystate[SDL_SCANCODE_A])
    {
        player_vel.x -= player_acc.x;
        id = "run";
        flip_flag = SDL_FLIP_HORIZONTAL;
        max_frame = JUMP_FRAMES;
    }

    // jumping
    if (keystate[SDL_SCANCODE_W] && !is_jumpping)
    {
        player_vel.y = player_acc.y;
        is_jumpping = true;
        max_frame = JUMP_FRAMES;
    }
    // update frame
    if (tot_frame > 8 * max_frame) tot_frame = 0;
    current_frame = tot_frame / 8;

}

void Character::Update_Position(float dt)
{
    // gravity
    player_vel.y += (float)GRAVITY * dt;

    // update position by time
    player_pos.x += player_vel.x * dt;
    player_pos.y += player_vel.y * dt;

    // no falling out of background
    if (player_pos.y + m_hitbox->h >= SOLID_FLOOR)
    {
        player_pos.y = (float)SOLID_FLOOR - m_hitbox->h;
        player_vel.y = 0.f;
        is_jumpping = false;
    }
    // jump and stand in platformw
    if (player_vel.y >= 0.f && is_jumpping)
    {
        id = "fall";
    }
    for (SDL_Rect& block : blocks)
    {
        if ((player_pos.x >= block.x - m_hitbox->w) && (player_pos.x <= block.x + block.w)
            && (player_pos.y + m_hitbox->h >= block.y) && (player_pos.y <= block.y)
            && (player_vel.y >= 0.f))
        {
                player_vel.y = 0.f;
                is_jumpping = false;
                player_pos.y = block.y - m_hitbox->h;
        }
    }


    // update hitbox and rectangle frame
    if (player_pos.x <= 0) player_pos.x = 0;
    if (player_pos.x + m_hitbox->w >= SCREEN_WIDTH) player_pos.x = SCREEN_WIDTH - m_hitbox->w;

    if (player_pos.y <= 0) player_pos.y = 0;

    m_hitbox->x = (int)player_pos.x;
    m_hitbox->y = (int)player_pos.y;

    m_rect->x = m_hitbox->x - (FRAME_SIZE - PLAYER_WIDTH) / 2;
    m_rect->y = m_hitbox->y - (FRAME_SIZE - PLAYER_HEIGHT) / 2;
}

void Character::set_y_vel(float replace_y_vel)
{
    player_vel.y = replace_y_vel;
}

void Character::set_y_pos(float replace_y_pos)
{
    player_pos.y = replace_y_pos;
}

float Character::get_y_vel()
{
    return player_vel.y;
}

// in case character die
void Character::reset_pos()
{
    player_pos.x = 100;
    player_pos.y = 640;
}



