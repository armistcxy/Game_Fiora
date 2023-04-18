#include "GameEngine.h"
bool GameManager::Init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cout << "Failed to initialize video and audio: " << SDL_GetError() << '\n';
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        std::cout << "Failed to set hint: " << SDL_GetError() << '\n';
        return false;
    }

    int IMG_Flag = IMG_INIT_PNG | IMG_INIT_JPG;

    if (!(IMG_Init(IMG_Flag) && IMG_Flag)) {
        std::cout << "Failed to initialize img: " << IMG_GetError() << '\n';
        return false;
    }
    
    if (TTF_Init() < 0){
        std::cout << "Failed to initialize font: " << TTF_GetError() << '\n';
        return false;
    }
    
    g_window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (g_window == NULL)
    {
        std::cout << "Failed to create window: " << SDL_GetError() << '\n';
        return false;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (g_renderer == NULL)
    {
        std::cout << "Failed to create renderer: " << SDL_GetError() << '\n';
        return false;
    }

    SDL_SetRenderDrawColor(g_renderer, 25, 25, 25, 255);

    return true;
}
bool GameManager::LoadMedia() {
    if (!g_background.Load_Texture_From_Path("asset/map.png", "map", g_renderer))
    {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!g_background.Load_Texture_From_Path("asset/background.png", "background", g_renderer))
    {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!player.m_character_frame.Load_Texture_From_Path("asset/Idle.png", "idle", g_renderer))
    {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!player.m_character_frame.Load_Texture_From_Path("asset/Run.png", "run", g_renderer))
    {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!player.m_character_frame.Load_Texture_From_Path("asset/Jump.png", "jump", g_renderer))
    {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!player.m_character_frame.Load_Texture_From_Path("asset/Fall.png", "fall", g_renderer))
    {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!player.m_character_frame.Load_Texture_From_Path("asset/Death.png", "death", g_renderer))
    {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!player.heart_player.Load_Texture_From_Path("asset/Heart.png", "heart", g_renderer))
    {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!player.shield_texture.Load_Texture_From_Path("asset/sun_shield.png", "shield", g_renderer)) {
        std::cout << "Can't load this img\n";
        return false;
    }
    game_update.AddEnemy();
    game_update.AddGhost();

    for (Enemy& ghost_ball : game_update.enemies)
    {
        if (!ghost_ball.m_enemy_frame.Load_Texture_From_Path("asset/GhostBall.png", "ghostball", g_renderer))
        {
            std::cout << "Can't load this img\n";
            return false;
        }
        if (!ghost_ball.explosion_texture.Load_Texture_From_Path("asset/explosion.png", "explosion", g_renderer)) {
            std::cout << "Can't load explosion\n";
            return false;
        }
    }
    
    for (Ghost& ghost : game_update.ghosts)
    {
        if (!ghost.m_ghost_frame.Load_Texture_From_Path("asset/Ghost.png", "ghost", g_renderer))
        {
            std::cout << "Can't load this img\n";
            return false;
        }
        if (!ghost.m_ghost_frame.Load_Texture_From_Path("asset/Ghost_Death.png", "ghost_death", g_renderer))
        {
            std::cout << "Can't load this img\n";
            return false;
        }
    }

    if (!mouse.Mouse_Texture.Load_Texture_From_Path("asset/MouseCursor.png", "mouse", g_renderer))
    {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!sword.m_sword_texture.Load_Texture_From_Path("asset/CyberSword.png", "sword", g_renderer))
    {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!sword.m_sword_texture.Load_Texture_From_Path("asset/sword_tail.png", "sword_tail", g_renderer)) {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!game_update.ultimate.Load_Texture_From_Path("asset/Ultimate.png", "ultimate", g_renderer))
    {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!game_update.ultimate.Load_Texture_From_Path("asset/Ultimate_gray.png", "ultimate_gray", g_renderer))
    {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!game_font.Load_Font()) {
        std::cout << "Can't load font for game\n";
        return false;
    }

    game_font.g_font = TTF_OpenFont("font/upheavtt.ttf", 32);
    return true;
}
void GameManager::Close() {
    player.m_character_frame.Clean();

    for (Enemy& ghost_ball : game_update.enemies)
    {
        ghost_ball.m_enemy_frame.Clean();
    }

    for (Ghost& ghost : game_update.ghosts)
    {
        ghost.m_ghost_frame.Clean();
    }

    SDL_DestroyRenderer(g_renderer);
    g_renderer = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;


    IMG_Quit();
    SDL_Quit();
}

void GameManager::Run() {
    // Init & load space
    if (!Init())
    {
        std::cout << "Failed to initialize everything\n";
    }

    if (!LoadMedia())
    {
        std::cout << "Failed to load media\n";
    }

    SDL_Event events;
    while (is_running)
    {
        time_manage.get_time();

        while (SDL_PollEvent(&events))
        {

            if (events.type == SDL_QUIT) {
                is_running = false;
                break;
            }

            mouse.Update(events);
        }

        SDL_RenderClear(g_renderer);

        // map and background
        g_background.Render(g_renderer, "background", START_POINT, SCREEN_WIDTH, SCREEN_HEIGHT);
        g_background.Render(g_renderer, "map", START_POINT, SCREEN_WIDTH, SCREEN_HEIGHT);
        // end

        // player
        player.Character_Handle(events);

        player.Update_Position(time_manage.get_delta_time());


        player.m_character_frame.RenderByFrame(g_renderer, player.id,
            player.Get_Rect()->x, player.Get_Rect()->y,
            FRAME_SIZE, FRAME_SIZE, player.current_frame, player.flip_flag);

        player.heart_player.RenderByFrame(g_renderer, "heart", HEART_PROPS,
            player.current_heart_frame, SDL_FLIP_NONE);

        //end
        //sword
        game_update.CallSword(mouse, sword);
        sword.update_sword();

        sword.m_sword_texture.Render(g_renderer, "sword",
            sword.get_rect()->x, sword.get_rect()->y, sword.get_rect()->w,
            sword.get_rect()->h, SDL_FLIP_VERTICAL);

        sword.m_sword_texture.RenderByFrame(g_renderer, "sword_tail",
            sword.tail_rect->x, sword.tail_rect->y, sword.tail_rect->w, sword.tail_rect->h,
            sword.current_tail_frame / SWORD_DELAY_FRAME);

        game_update.Kill_Ghost(sword);

        game_update.ultimate.Render(g_renderer, game_update.ulti_state, SWORD_PROPS);
        //end
        // shield
        player.shield_call(g_renderer);
        //end
        // ghostball
        for (Enemy& ghost_ball : game_update.enemies)
        {
            ghost_ball.m_enemy_frame.RenderByFrame(g_renderer, "ghostball", ghost_ball.Get_Rect()->x,
                ghost_ball.Get_Rect()->y, GHOSTBALL_SIZE,
                ghost_ball.current_frame, ghost_ball.flip_flag);

            ghost_ball.update_pos();
            game_update.Check_Player_And_Ghostball(player, ghost_ball, g_renderer);

            if (ghost_ball.is_bang) ghost_ball.call_explosion(g_renderer);
        }

        // ghost
        for (Ghost& ghost : game_update.ghosts)
        {
            ghost.m_ghost_frame.RenderByFrame(g_renderer, ghost.id, ghost.Get_Rect()->x, ghost.Get_Rect()->y
                , ghost.Get_Rect()->w, ghost.Get_Rect()->h, ghost.current_frame, ghost.flip_flag);
            ghost.update_pos(&player);
            game_update.Check_PLayer_And_Ghost(player, ghost);
        }
        // font
        time_to_sec = time_manage.get_current_time() / TIME_TO_SEC;
        
        show_time = std::to_string(time_to_sec);
        show_time.resize(5);

        time_manage.update_time();
        
        game_font.Render_Text(g_renderer, show_time.c_str(), game_font.g_font, time_color, &time_rect);

        // mouse cursor
        SDL_ShowCursor(NULL);

        mouse.Mouse_Texture.Render(g_renderer, "mouse", mouse.Mouse_Rect.x, mouse.Mouse_Rect.y,
            mouse.Mouse_Rect.w, mouse.Mouse_Rect.h);

       
        SDL_RenderPresent(g_renderer);

    }
    //ending space
    Close();
}
