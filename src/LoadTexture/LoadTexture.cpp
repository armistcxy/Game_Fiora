#include "LoadTexture.h"

LoadTexture::LoadTexture()
{
}

LoadTexture::~LoadTexture()
{
    Clean();
}

bool LoadTexture::Load_Texture_From_Path(std::string path, std::string id, SDL_Renderer* renderer)
{
    SDL_Surface* tmp_surf = IMG_Load(path.c_str());

    if (tmp_surf == NULL)
    {
        std::cout << "Failed to load image\n";
        return false;
    }

    SDL_Texture* tmp_texture = SDL_CreateTextureFromSurface(renderer, tmp_surf);

    if (tmp_texture == NULL)
    {
        std::cout << "Failed to create texture: " << SDL_GetError() << '\n';
        return false;
    }

    SDL_FreeSurface(tmp_surf);

    g_texture_map[id] = tmp_texture;

    return true;
}

void LoadTexture::Render(SDL_Renderer* renderer, std::string id, int x, int y, int width, int height, SDL_RendererFlip flip_flag)
{
    SDL_Rect src_rect = {0, 0, width, height};
    SDL_Rect dst_rect = {x, y, width, height};
    SDL_RenderCopyEx(renderer, g_texture_map[id], &src_rect, &dst_rect, 0, nullptr, flip_flag);
}

void LoadTexture::RenderByFrame(SDL_Renderer* renderer, std::string id, int x, int y, int width, int height, int frame, SDL_RendererFlip flip_flag)
{
    SDL_Rect src_rect = {width * frame, 0, width, height};
    SDL_Rect dst_rect = {x, y, width, height};
    SDL_RenderCopyEx(renderer, g_texture_map[id], &src_rect, &dst_rect, 0, nullptr, flip_flag);
}

void LoadTexture::Clean()
{
    for (auto it = g_texture_map.begin(); it != g_texture_map.end(); it++)
    {
        SDL_DestroyTexture(it->second);
    }
    g_texture_map.clear();
}




