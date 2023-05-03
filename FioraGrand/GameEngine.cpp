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
    
    /* 44100 is standard frequency according to this tutorial
    https://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php
    */
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        std::cout << "Failed to initialize mixer: " << Mix_GetError() << '\n';
        return false;
    }
    SDL_Init(MIX_INIT_MP3);

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
        std::cout << "Can't load background\n";
        return false;
    }

    if (!g_background.Load_Texture_From_Path("asset/background.png", "background", g_renderer))
    {
        std::cout << "Can't load background\n";
        return false;
    }

    if (!player.m_character_frame.Load_Texture_From_Path("asset/Idle.png", "idle", g_renderer))
    {
        std::cout << "Can't load idle player img\n";
        return false;
    }

    if (!player.m_character_frame.Load_Texture_From_Path("asset/Run.png", "run", g_renderer))
    {
        std::cout << "Can't load run img\n";
        return false;
    }

    if (!player.m_character_frame.Load_Texture_From_Path("asset/Jump.png", "jump", g_renderer))
    {
        std::cout << "Can't load jump img\n";
        return false;
    }

    if (!player.m_character_frame.Load_Texture_From_Path("asset/Fall.png", "fall", g_renderer))
    {
        std::cout << "Can't load fall img\n";
        return false;
    }

    if (!player.m_character_frame.Load_Texture_From_Path("asset/Death.png", "death", g_renderer))
    {
        std::cout << "Can't load death img\n";
        return false;
    }

    if (!player.heart_player.Load_Texture_From_Path("asset/Heart.png", "heart", g_renderer))
    {
        std::cout << "Can't load heart img\n";
        return false;
    }

    if (!player.shield_texture.Load_Texture_From_Path("asset/sun_shield.png", "shield", g_renderer)) {
        std::cout << "Can't load shield img\n";
        return false;
    }
    game_update.AddEnemy();
    game_update.AddGhost();

    for (Enemy& ghost_ball : game_update.enemies)
    {
        if (!ghost_ball.m_enemy_frame.Load_Texture_From_Path("asset/GhostBall.png", "ghostball", g_renderer))
        {
            std::cout << "Can't load ghostball img\n";
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
            std::cout << "Can't load ghost img\n";
            return false;
        }
        if (!ghost.m_ghost_frame.Load_Texture_From_Path("asset/Ghost_Death.png", "ghost_death", g_renderer))
        {
            std::cout << "Can't load ghost death img\n";
            return false;
        }
    }

    if (!mouse.Mouse_Texture.Load_Texture_From_Path("asset/MouseCursor.png", "mouse", g_renderer))
    {
        std::cout << "Can't load mousecursor img\n";
        return false;
    }

    if (!sword.m_sword_texture.Load_Texture_From_Path("asset/CyberSword.png", "sword", g_renderer))
    {
        std::cout << "Can't load cybersword img\n";
        return false;
    }

    if (!sword.m_sword_texture.Load_Texture_From_Path("asset/sword_tail.png", "sword_tail", g_renderer)) {
        std::cout << "Can't load sword_tail img\n";
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
        std::cout << "Can't load play_button_light\n";
        return false;
    }

    if (!play_button.button_texture.Load_Texture_From_Path("asset/Play_Button_Dark.png", "play_dark", g_renderer)) {
        std::cout << "Can't load play_button_dark\n";
        return false;
    }

    if (!exit_button.button_texture.Load_Texture_From_Path("asset/Exit_Button_Light.png", "exit_light", g_renderer)) {
        std::cout << "Can't load exit_button_light\n";
        return false;
    }

    if (!exit_button.button_texture.Load_Texture_From_Path("asset/Exit_Button_Dark.png", "exit_dark", g_renderer)) {
        std::cout << "Can't load exit_button_dark\n";
        return false;
    }

    if (!setting_button.button_texture.Load_Texture_From_Path("asset/Setting_Button_Light.png", "setting_light", g_renderer)) {
        std::cout << "Can't load setting_button_light\n";
        return false;
    }

    if (!setting_button.button_texture.Load_Texture_From_Path("asset/Setting_Button_Dark.png", "setting_dark", g_renderer)) {
        std::cout << "Can't load setting_button_dark\n";
        return false;
    }

    if (!pause_button.button_texture.Load_Texture_From_Path("asset/Pause_Button_Light.png", "pause_light", g_renderer)) {
        std::cout << "Can't load pause_button_light\n";
        return false;
    }

    if (!pause_button.button_texture.Load_Texture_From_Path("asset/Pause_Button_Dark.png", "pause_dark", g_renderer)) {
        std::cout << "Can't load pause_button_dark\n";
        return false;
    }

    if (!highscore_button.button_texture.Load_Texture_From_Path("asset/Highscore_Button_Light.png", "highscore_light", g_renderer)) {
        std::cout << "Can't load highscore_button_light\n";
        return false;
    }
    if (!highscore_button.button_texture.Load_Texture_From_Path("asset/Highscore_Button_Dark.png", "highscore_dark", g_renderer)) {
        std::cout << "Can't load highscore_button_dark\n";
        return false;
    }

    if (!pause_manager.continue_button.button_texture.Load_Texture_From_Path("asset/Continue_Button_Light.png", "continue_light", g_renderer)) {
        std::cout << "Can't load continue_button_light\n";
        return false;
    }

    if (!pause_manager.continue_button.button_texture.Load_Texture_From_Path("asset/Continue_Button_Dark.png", "continue_dark", g_renderer)) {
        std::cout << "Can't load continue_button_dark\n";
            return false;
    }

    if (!pause_manager.home_button.button_texture.Load_Texture_From_Path("asset/Home_Button_Light.png", "home_light", g_renderer)) {
        std::cout << "Can't load home_button_light\n";
            return false;
    }

    if (!pause_manager.home_button.button_texture.Load_Texture_From_Path("asset/Home_Button_Dark.png", "home_dark", g_renderer)) {
        std::cout << "Can't load home_button_dark\n";
            return false;
    }

    if (!retry_button.button_texture.Load_Texture_From_Path("asset/Retry_Button_Light.png","retry_light",g_renderer)) {
        std::cout << "Can't load retry_button_light\n";
        return false;
    }
    
    if (!retry_button.button_texture.Load_Texture_From_Path("asset/Retry_Button_Dark.png", "retry_dark", g_renderer)) {
        std::cout << "Can't load retry_button_dark\n";
        return false;
    }

    if (!music_button.button_texture.Load_Texture_From_Path("asset/Music_Light.png", "music_light", g_renderer)) {
        std::cout << "Can't load music_button_light\n";
        return false;
    }

    if (!music_button.button_texture.Load_Texture_From_Path("asset/Music_Dark.png", "music_dark", g_renderer)) {
        std::cout << "Can't load music_button_dark\n";
        return false;
    }

    if (!music_button.button_texture.Load_Texture_From_Path("asset/Mute_Light.png", "mute_light", g_renderer)) {
        std::cout << "Can't load mute_button_light\n";
        return false;
    }

    if (!music_button.button_texture.Load_Texture_From_Path("asset/Mute_Dark.png", "mute_dark", g_renderer)) {
        std::cout << "Can't load mute_button_dark\n";
        return false;
    }

    if (!pause_manager.pause_screen_texture.Load_Texture_From_Path("asset/Span.png", "span", g_renderer)) {
        std::cout << "Can't load span\n";
        return false;
    }

    if (!menu.menu_texture.Load_Texture_From_Path("asset/menu.png", "menu", g_renderer)) {
        std::cout << "Can't load menu img\n";
        return false;
    } 

    if (!game_update.ultimate.Load_Texture_From_Path("asset/Ultimate.png", "ultimate", g_renderer))
    {
        std::cout << "Can't load ultimate png\n";
        return false;
    }

    if (!game_update.ultimate.Load_Texture_From_Path("asset/Ultimate_gray.png", "ultimate_gray", g_renderer))
    {
        std::cout << "Can't load ultimate_gray png\n";
        return false;
    }

    if (!game_title_span.Load_Texture_From_Path("asset/Banner.png", "banner", g_renderer)) {
        std::cout << "Can't load banner\n";
        return false; 
    }

    if (!highscore_manager.highscore_texture.Load_Texture_From_Path("asset/Highscore_Background.png", "highscore_bg", g_renderer)) {
        std::cout << "Can't load highscore_background\n";
        return false;
    }
    
    if (!highscore_manager.highscore_texture.Load_Texture_From_Path("asset/Highscore_span.png", "highscore_span", g_renderer)) {
        std::cout << "Can't load highscore_span\n";
        return false;
    }

    if (!highscore_manager.highscore_title.Load_Font()) {
        std::cout << "Can't load font for highscore title\n";
        return false;
    }

    for (int i = 0; i < 5; i++) {
        if (!highscore_manager.highscore_table[i].Load_Font()) {
            std::cout << "Can't load font for highscore\n";
            return false;
        }
    }
    
    if (!game_background.Load_Texture_From_Path("asset/Game_end_background.png", "game_end_background", g_renderer)) {
        std::cout << "Can't load game_end_background\n";
        return false;
    }

    if (!game_background.Load_Texture_From_Path("asset/Setting_background.png", "setting_background", g_renderer)) {
        std::cout << "Can't load setting_background\n";
        return false;
    }

    if (!game_end_noti.Load_Font()) {
        std::cout << "Can't load font for game_end_noti\n";
        return false;
    }

    play_button.Init_position(PLAY_BUTTON_POS);
    setting_button.Init_position(SETTING_BUTTON_POS);
    highscore_button.Init_position(HIGHSCORE_BUTTON_POS);
    exit_button.Init_position(EXIT_BUTTON_POS);
    pause_button.Init_position(SCREEN_WIDTH - BUTTON_SIZE, 0);
    pause_manager.continue_button.Init_position(CONTINUE_BUTTON_POS);
    pause_manager.home_button.Init_position(HOME_BUTTON_POS);
    music_button.Init_position(MUSIC_BUTTON_POS);
    retry_button.Init_position(RETRY_BUTTON_POS);

    highscore_manager.Init();
    
    //sound
    background_music = Mix_LoadMUS("sound/background_music.mp3");
    game_update.explosion_sound = Mix_LoadWAV("sound/explosion.wav");
    end_sound = Mix_LoadWAV("sound/death_sound.wav");

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
    
    Mix_FreeMusic(background_music);
    background_music = NULL;

    Mix_Quit();
    TTF_Quit();
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
        time_manage.game_time(game_state, is_pause);
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
                
                if (highscore_button.Light_or_Dark() && events.type == SDL_MOUSEBUTTONUP
                    && events.button.button == SDL_BUTTON_LEFT) {
                    game_state = GAME_HIGHSCORE;
                }

                if (setting_button.Light_or_Dark() && events.type == SDL_MOUSEBUTTONUP
                    && events.button.button == SDL_BUTTON_LEFT) {
                    game_state = GAME_SETTING;
                }

                if (events.type == SDL_QUIT) {
                    is_running = false;
                    break;
                }

                mouse.Update(events);
            }
            break;
        case GAME_PLAY:
            highscore_manager.is_higher = false;
            pause_manager.home_button.Init_position(HOME_BUTTON_POS);
            time_manage.get_time();
            time_manage.game_time(game_state,is_pause);
            if (Mix_PlayingMusic() == 0)
            {
                Mix_PlayMusic(background_music, -1);
            }
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
                        player.reset();
                        game_update.Reset_Event(g_renderer);
                        is_pause = false;
                        break;
                    }
                    if (music_button.Light_or_Dark() && events.type == SDL_MOUSEBUTTONUP
                        && events.button.button == SDL_BUTTON_LEFT) {
                        is_mute = !is_mute;
                        if (Mix_PlayingMusic() == 0)
                        {
                            Mix_PlayMusic(background_music, -1);
                        }
                        else
                        {
                            if (Mix_PausedMusic() == 1) Mix_ResumeMusic();
                            else Mix_PauseMusic();
                        }
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
            if (!pause_button.Light_or_Dark() && !is_pause) game_update.CallSword(mouse, sword, time_manage);
            if (!is_pause) sword.update_sword();

            sword.m_sword_texture.Render(g_renderer, "sword",
                sword.get_rect()->x, sword.get_rect()->y, sword.get_rect()->w,
                sword.get_rect()->h, SDL_FLIP_VERTICAL);

            sword.m_sword_texture.RenderByFrame(g_renderer, "sword_tail",
                sword.tail_rect->x, sword.tail_rect->y, sword.tail_rect->w, sword.tail_rect->h,
                sword.current_tail_frame / SWORD_DELAY_FRAME);

            if (!is_pause) game_update.Kill_Ghost(sword,is_mute);

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
                    ghost_ball.update_pos(time_manage);
                    game_update.Check_Player_And_Ghostball(player, ghost_ball, g_renderer, time_manage
                    ,is_mute);
                    
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
                    game_update.Check_PLayer_And_Ghost(player, ghost, time_manage);
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
                if (!is_mute) {
                    music_button.Light_or_Dark() ? music_button.Render_button(g_renderer, "music_light") :
                        music_button.Render_button(g_renderer, "music_dark");
                }
                else {
                    music_button.Light_or_Dark() ? music_button.Render_button(g_renderer, "mute_light") :
                        music_button.Render_button(g_renderer, "mute_dark");
                }
            }
            (pause_button.Light_or_Dark() ? pause_button.Render_button(g_renderer, "pause_light") :
                pause_button.Render_button(g_renderer, "pause_dark"));


            if (player.current_heart_frame == HEART_FRAME) {
                highscore_manager.Update_Highscore(time_to_sec); 
                game_state = GAME_END;
            }
            break;

        case GAME_HIGHSCORE:
            highscore_manager.highscore_texture.Render(g_renderer, "highscore_bg", START_POINT, SCREEN_WIDTH, SCREEN_HEIGHT);
            highscore_manager.highscore_texture.Render(g_renderer, "highscore_span", 300, 100, 650, 560);
            highscore_manager.Render_highscore_title(g_renderer);
            highscore_manager.Get_Highscore_From_Past();
            highscore_manager.Render_highscore_point(g_renderer);
            pause_manager.home_button.Init_position(SCREEN_WIDTH - BUTTON_SIZE, 0);
            
            (pause_manager.home_button.Light_or_Dark() ? 
                    pause_manager.home_button.Render_button(g_renderer, "home_light") :
                    pause_manager.home_button.Render_button(g_renderer, "home_dark"));
            while (SDL_PollEvent(&events))
            {
                if (events.type == SDL_QUIT) {
                    is_running = false;
                    break;
                }
                if (pause_manager.home_button.Light_or_Dark() && events.type == SDL_MOUSEBUTTONUP
                    && events.button.button == SDL_BUTTON_LEFT) {
                    game_state = GAME_MENU;
                    break;
                }
                mouse.Update(events);
            }
            break;
        case GAME_END:
            game_background.Render(g_renderer, "game_end_background", START_POINT, SCREEN_WIDTH, SCREEN_HEIGHT);
            retry_button.Light_or_Dark() ? retry_button.Render_button(g_renderer, "retry_light") :
                retry_button.Render_button(g_renderer, "retry_dark");
            pause_manager.home_button.Light_or_Dark() ? pause_manager.home_button.Render_button(g_renderer, "home_light") :
                pause_manager.home_button.Render_button(g_renderer, "home_dark");
            Mix_PauseMusic();
            if (!already_play_endsound) {
                if (!is_mute) Mix_PlayChannel(-1, end_sound, 0);
                already_play_endsound = true;
            }
            if (highscore_manager.is_higher) {
                game_end_noti.Render_Text(g_renderer, "New record, congratulations!!!",
                    game_end_noti.BigSize, game_title_color, &game_end_rect);
            }
            else {
                game_end_noti.Render_Text(g_renderer, "Better luck next time", game_end_noti.BigSize,
                    game_title_color, &game_end_rect);
            }

            while (SDL_PollEvent(&events))
            {
                if (events.type == SDL_QUIT) {
                    is_running = false;
                    break;
                }
                if (pause_manager.home_button.Light_or_Dark() && events.type == SDL_MOUSEBUTTONUP
                    && events.button.button == SDL_BUTTON_LEFT) {
                    game_state = GAME_MENU;
                    player.current_heart_frame = 0;
                    player.reset();
                    game_update.Reset_Event(g_renderer);
                    break;
                }

                if (retry_button.Light_or_Dark() && events.type == SDL_MOUSEBUTTONUP
                    && events.button.button == SDL_BUTTON_LEFT) {
                    game_state = GAME_PLAY;
                    player.current_heart_frame = 0;
                    player.reset();
                    game_update.Reset_Event(g_renderer);
                    break;
                }
                mouse.Update(events);
            }
            break;
        case GAME_SETTING:
            game_background.Render(g_renderer, "setting_background", START_POINT, SCREEN_WIDTH, SCREEN_HEIGHT);
            pause_manager.home_button.Init_position(SCREEN_WIDTH - BUTTON_SIZE, 0);
            (pause_manager.home_button.Light_or_Dark() ?
                pause_manager.home_button.Render_button(g_renderer, "home_light") :
                pause_manager.home_button.Render_button(g_renderer, "home_dark"));
            if (!is_mute) {
                music_button.Light_or_Dark() ? music_button.Render_button(g_renderer, "music_light") :
                    music_button.Render_button(g_renderer, "music_dark");
            }
            else {
                music_button.Light_or_Dark() ? music_button.Render_button(g_renderer, "mute_light") :
                    music_button.Render_button(g_renderer, "mute_dark");
            }
            while (SDL_PollEvent(&events))
            {
                if (events.type == SDL_QUIT) {
                    is_running = false;
                    break;
                }
                if (pause_manager.home_button.Light_or_Dark() && events.type == SDL_MOUSEBUTTONUP
                    && events.button.button == SDL_BUTTON_LEFT) {
                    game_state = GAME_MENU;
                    player.current_heart_frame = 0;
                    player.reset();
                    game_update.Reset_Event(g_renderer);
                    break;
                }      
                if (music_button.Light_or_Dark() && events.type == SDL_MOUSEBUTTONUP
                    && events.button.button == SDL_BUTTON_LEFT) {
                    is_mute = !is_mute;
                    if (Mix_PlayingMusic() == 0 && !is_mute)
                    {
                        Mix_PlayMusic(background_music, -1);
                    }
                    else
                    {
                        if (Mix_PausedMusic() == 1) Mix_ResumeMusic();
                        else Mix_PauseMusic();
                    }
                }
                mouse.Update(events);
            }
            break;
        }
        
        // mouse cursor
        SDL_ShowCursor(NULL);

        mouse.Mouse_Texture.Render(g_renderer, "mouse", mouse.Mouse_Rect.x, mouse.Mouse_Rect.y,
            mouse.Mouse_Rect.w, mouse.Mouse_Rect.h);

        
        SDL_RenderPresent(g_renderer);
        SDL_RenderClear(g_renderer);
    }
    //ending space
    Close();
}