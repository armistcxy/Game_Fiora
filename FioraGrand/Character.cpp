#include "Character.h"
Character::Character()
{
    // default rectangle for frames properties
    m_rect = new SDL_Rect;
    m_rect->x = DEFAULT_PLAYER_POS;
    m_rect->y = DEFAULT_PLAYER_POS;
    m_rect->w = FRAME_SIZE;
    m_rect->h = FRAME_SIZE;

    // default hit box properties
    m_hitbox = new SDL_Rect;
    m_hitbox->x = DEFAULT_PLAYER_POS;
    m_hitbox->y = DEFAULT_PLAYER_POS;
    m_hitbox->w = PLAYER_WIDTH;
    m_hitbox->h = PLAYER_HEIGHT;

    //shield
    shield_rect = new SDL_Rect;
    shield_rect->x = DEFAULT_PLAYER_POS;
    shield_rect->y = DEFAULT_PLAYER_POS;
    shield_rect->w = SHIELD_SIZE;
    shield_rect->h = SHIELD_SIZE;

    // default position, velocity, acceleration
    player_pos.x = (float)DEFAULT_PLAYER_POS;
    player_pos.y = (float)DEFAULT_PLAYER_POS;

    player_vel.x = VEL_PLAYER_START;
    player_vel.y = VEL_PLAYER_START;

    player_acc.x = ACC_PLAYER_X;
    player_acc.y = ACC_PLAYER_Y;

    // default state
    character_state = IDLE;
    id = "idle";
    current_frame = 0;
    tot_frame = 0;

    max_frame = IDLE_FRAMES;

    is_jumpping = false;
    current_heart_frame = 0;

    current_shield_frame = 0;
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
    //death state 
    if (current_heart_frame == MAX_HEAL)
    {
        id = "death";
        tot_frame++;
        current_frame = tot_frame / CHARACTER_DELAY;
        if (current_frame > max_frame) current_frame = max_frame;
        player_vel.x = VEL_PLAYER_START, player_vel.y = VEL_PLAYER_START;
        max_frame = DEATH_FRAMES;

        return;
    }
    // not allow any action after death 
    if (current_heart_frame >= MAX_HEAL) {
        if (tot_frame > 8 * max_frame) tot_frame = 0;
        current_frame = tot_frame / 8;
        return;
    }
    // if no input from keyboard
    
    player_vel.x = VEL_PLAYER_START;
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
    if (tot_frame > CHARACTER_DELAY * max_frame) tot_frame = 0;
    current_frame = tot_frame / CHARACTER_DELAY;

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
        player_vel.y = VEL_PLAYER_START;
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

void Character::shield_call(SDL_Renderer* renderer){
    if (shield_state) {
        shield_rect->x = player_pos.x - GET_CENTER_SHIELD_X;
        shield_rect->y = player_pos.y - GET_CENTER_SHIELD_Y;
        shield_texture.RenderByFrame(renderer, "shield", shield_rect->x, shield_rect->y,
            shield_rect->w, shield_rect->h, current_shield_frame);
        if (tot_frame > CHARACTER_DELAY * max_frame) current_shield_frame = 0;
        current_shield_frame = tot_frame / CHARACTER_DELAY;
    }
}



