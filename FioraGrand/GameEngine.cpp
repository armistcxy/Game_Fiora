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

    // game icon
    SDL_Surface* game_icon = new SDL_Surface;
    game_icon = IMG_Load("asset/wibuhuhu.png");
    SDL_SetWindowIcon(g_window, game_icon);
    SDL_FreeSurface(game_icon);
    

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


    if (!game_font.Load_Font()) {
        std::cout << "Can't load font for game\n";
        return false;
    }

    if (!game_title.Load_Font()) {
        std::cout << "Can't load font for game\n";
        return false;
    }
    if (!play_button.button_texture.Load_Texture_From_Path("asset/Play_Button_Light.png", "play_light", g_renderer)) {
        std::cout << "Can't load play\n";
        return false;
    }

    if (!play_button.button_texture.Load_Texture_From_Path("asset/Play_Button_Dark.png", "play_dark", g_renderer)) {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!exit_button.button_texture.Load_Texture_From_Path("asset/Exit_Button_Light.png", "exit_light", g_renderer)) {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!exit_button.button_texture.Load_Texture_From_Path("asset/Exit_Button_Dark.png", "exit_dark", g_renderer)) {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!setting_button.button_texture.Load_Texture_From_Path("asset/Setting_Button_Light.png", "setting_light", g_renderer)) {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!setting_button.button_texture.Load_Texture_From_Path("asset/Setting_Button_Dark.png", "setting_dark", g_renderer)) {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!pause_button.button_texture.Load_Texture_From_Path("asset/Pause_Button_Light.png", "pause_light", g_renderer)) {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!pause_button.button_texture.Load_Texture_From_Path("asset/Pause_Button_Dark.png", "pause_dark", g_renderer)) {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!highscore_button.button_texture.Load_Texture_From_Path("asset/Highscore_Button_Light.png", "highscore_light", g_renderer)) {
        std::cout << "Can't load this img\n";
        return false;
    }
    if (!highscore_button.button_texture.Load_Texture_From_Path("asset/Highscore_Button_Dark.png", "highscore_dark", g_renderer)) {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!pause_manager.continue_button.button_texture.Load_Texture_From_Path("asset/Continue_Button_Light.png", "continue_light", g_renderer)) {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!pause_manager.continue_button.button_texture.Load_Texture_From_Path("asset/Continue_Button_Dark.png", "continue_dark", g_renderer)) {
        std::cout << "Can't load this img\n";
            return false;
    }

    if (!pause_manager.home_button.button_texture.Load_Texture_From_Path("asset/Home_Button_Light.png", "home_light", g_renderer)) {
        std::cout << "Can't load this img\n";
            return false;
    }

    if (!pause_manager.home_button.button_texture.Load_Texture_From_Path("asset/Home_Button_Dark.png", "home_dark", g_renderer)) {
        std::cout << "Can't load this img\n";
            return false;
    }

 
    if (!pause_manager.pause_screen_texture.Load_Texture_From_Path("asset/Span.png", "span", g_renderer)) {
        std::cout << "Can't load this img\n";
        return false;
    }

    if (!menu.menu_texture.Load_Texture_From_Path("asset/menu.png", "menu", g_renderer)) {
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

    if (!game_title_span.Load_Texture_From_Path("asset/Banner.png", "banner", g_renderer)) {
        std::cout << "Can't load this img\n";
        return false; 
    }
    
    
    play_button.Init_position(PLAY_BUTTON_POS);
    setting_button.Init_position(SETTING_BUTTON_POS);
    highscore_button.Init_position(HIGHSCORE_BUTTON_POS);
    exit_button.Init_position(EXIT_BUTTON_POS);
    pause_button.Init_position(SCREEN_WIDTH - BUTTON_SIZE, 0);
    pause_manager.continue_button.Init_position(CONTINUE_BUTTON_POS);
    pause_manager.home_button.Init_position(HOME_BUTTON_POS);
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
    bool is_pause = false;
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
        switch (game_state) {
        case GAME_MENU:
            menu.background_render(g_renderer);
            SDL_ShowCursor(NULL);
            game_title_span.Render(g_renderer, "banner", GAME_TITLE_PROPS);
            game_title.Render_Text(g_renderer, "GRAND FIORA CHALLENGE",game_title.MediumSize,game_title_color, &game_title_rect);
            (play_button.Light_or_Dark() ? play_button.Render_button(g_renderer, "play_light") :
                play_button.Render_button(g_renderer, "play_dark"));
            (exit_button.Light_or_Dark() ? exit_button.Render_button(g_renderer, "exit_light") :
                exit_button.Render_button(g_renderer, "exit_dark"));
            (setting_button.Light_or_Dark() ? setting_button.Render_button(g_renderer, "setting_light") :
                setting_button.Render_button(g_renderer, "setting_dark"));
            (highscore_button.Light_or_Dark() ? highscore_button.Render_button(g_renderer, "highscore_light") :
                highscore_button.Render_button(g_renderer, "highscore_dark"));

            time_manage.game_time(game_state, is_pause);
            mouse.Mouse_Texture.Render(g_renderer, "mouse", mouse.Mouse_Rect.x, mouse.Mouse_Rect.y,
                mouse.Mouse_Rect.w, mouse.Mouse_Rect.h);

            while (SDL_PollEvent(&events))
            {
                if (play_button.Light_or_Dark() && events.type == SDL_MOUSEBUTTONUP
                    && events.button.button == SDL_BUTTON_LEFT) {
                    game_state = GAME_PLAY;
                }
                if (exit_button.Light_or_Dark() && events.type == SDL_MOUSEBUTTONUP
                    && events.button.button == SDL_BUTTON_LEFT) {
                    is_running = false;
                    break;
                }
                
                if (events.type == SDL_QUIT) {
                    is_running = false;
                    break;
                }

                mouse.Update(events);
            }
            break;
        case GAME_PLAY:
            time_manage.get_time();
            time_manage.game_time(game_state,is_pause);

            while (SDL_PollEvent(&events))
            {
                if (pause_button.Light_or_Dark() && events.type == SDL_MOUSEBUTTONUP
                    && events.button.button == SDL_BUTTON_LEFT) {
                    is_pause = !is_pause;
                    time_manage.is_switch = true;
                }
                if (is_pause) {
                    if (pause_manager.continue_button.Light_or_Dark() && events.type == SDL_MOUSEBUTTONUP
                        && events.button.button == SDL_BUTTON_LEFT) {
                        is_pause = false;
                    }
                    if (pause_manager.home_button.Light_or_Dark() && events.type == SDL_MOUSEBUTTONUP
                        && events.button.button == SDL_BUTTON_LEFT) {
                        game_state = GAME_MENU;
                        break;
                    }
                }
                if (events.type == SDL_QUIT) {
                    is_running = false;
                    break;
                }

                mouse.Update(events);
            }
            SDL_RenderClear(g_renderer);
            if (time_manage.is_switch) {
                if (is_pause) {
                    time_manage.update_pause_start_time();
                }
                else time_manage.update_pause_end_time();
                time_manage.is_switch = false;
            }
            // map and background
            g_background.Render(g_renderer, "background", START_POINT, SCREEN_WIDTH, SCREEN_HEIGHT);
            g_background.Render(g_renderer, "map", START_POINT, SCREEN_WIDTH, SCREEN_HEIGHT);
            // end

            // player
            if (!is_pause) {
                player.Character_Handle(events);

                player.Update_Position(time_manage.get_delta_time());
            }


            player.m_character_frame.RenderByFrame(g_renderer, player.id,
                player.Get_Rect()->x, player.Get_Rect()->y,
                FRAME_SIZE, FRAME_SIZE, player.current_frame, player.flip_flag);

            player.heart_player.RenderByFrame(g_renderer, "heart", HEART_PROPS,
                player.current_heart_frame, SDL_FLIP_NONE);

            //end
            //sword
            if (!pause_button.Light_or_Dark() && !is_pause) game_update.CallSword(mouse, sword);
            if (!is_pause) sword.update_sword();

            sword.m_sword_texture.Render(g_renderer, "sword",
                sword.get_rect()->x, sword.get_rect()->y, sword.get_rect()->w,
                sword.get_rect()->h, SDL_FLIP_VERTICAL);

            sword.m_sword_texture.RenderByFrame(g_renderer, "sword_tail",
                sword.tail_rect->x, sword.tail_rect->y, sword.tail_rect->w, sword.tail_rect->h,
                sword.current_tail_frame / SWORD_DELAY_FRAME);

            if (!is_pause) game_update.Kill_Ghost(sword);

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

                if (!is_pause) {
                    ghost_ball.update_pos();
                    game_update.Check_Player_And_Ghostball(player, ghost_ball, g_renderer, time_manage);
                    
                }
                if (ghost_ball.is_bang) ghost_ball.call_explosion(g_renderer);

            }

            // ghost
            for (Ghost& ghost : game_update.ghosts)
            {
                ghost.m_ghost_frame.RenderByFrame(g_renderer, ghost.id, ghost.Get_Rect()->x, ghost.Get_Rect()->y
                    , ghost.Get_Rect()->w, ghost.Get_Rect()->h, ghost.current_frame, ghost.flip_flag);
                if (!is_pause) {
                    ghost.update_pos(&player);
                    game_update.Check_PLayer_And_Ghost(player, ghost);
                }
            }
            // font

            if (!is_pause) time_to_sec = time_manage.get_current_time() / TIME_TO_SEC;

            show_time = std::to_string(time_to_sec);
            show_time.resize(4);

            if (!is_pause) time_manage.update_time();

            game_font.Render_Text(g_renderer, show_time.c_str(), game_font.g_font, time_color, &time_rect);

            //pause_screen
            if (is_pause) {
                pause_manager.pause_screen_texture.Render(g_renderer, "span",
                    240, 100, 800, 500);
                (pause_manager.continue_button.Light_or_Dark() ? 
                    pause_manager.continue_button.Render_button(g_renderer, "continue_light") :
                    pause_manager.continue_button.Render_button(g_renderer, "continue_dark"));
                (pause_manager.home_button.Light_or_Dark() ? 
                    pause_manager.home_button.Render_button(g_renderer, "home_light") :
                    pause_manager.home_button.Render_button(g_renderer, "home_dark"));
            }

            // mouse cursor
            SDL_ShowCursor(NULL);

            mouse.Mouse_Texture.Render(g_renderer, "mouse", mouse.Mouse_Rect.x, mouse.Mouse_Rect.y,
                mouse.Mouse_Rect.w, mouse.Mouse_Rect.h);

            (pause_button.Light_or_Dark() ? pause_button.Render_button(g_renderer, "pause_light") :
                pause_button.Render_button(g_renderer, "pause_dark"));

            

            break;

            
        }
        SDL_RenderPresent(g_renderer);
        SDL_RenderClear(g_renderer);
    }
    //ending space
    Close();
}
