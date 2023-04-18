#ifndef LOADTEXTURE_H
#define LOADTEXTURE_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
class LoadTexture
{
    public:
        LoadTexture();
        ~LoadTexture();

        bool Load_Texture_From_Path(std::string path, std::string id, SDL_Renderer* renderer);

        void Render(SDL_Renderer* renderer, std::string id, int x, int y, int width, int height, SDL_RendererFlip flip_flag);

        void RenderByFrame(SDL_Renderer* renderer, std::string id, int x, int y, int width, int height, int frame, SDL_RendererFlip flip_flag);

        void Clean();

        std::map<std::string, SDL_Texture*> g_texture_map;

};

#endif // LOADTEXTURE_H
