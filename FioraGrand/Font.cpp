#include "Font.h"

Font::Font()
{
    g_font = NULL;
    BigSize = NULL;
    MediumSize = NULL;
    SmallSize = NULL;
}
bool Font::Get_Font_Type_and_Size(TTF_Font*& font,const char* font_name, int size) {
    font = TTF_OpenFont(font_name, size);
    if (font == NULL) {
        std::cout << "Faild to load font : " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}
bool Font::Load_Font() {
    bool flag1 = Get_Font_Type_and_Size(g_font, "font/upheavtt.ttf", 50);
    bool flag2 = Get_Font_Type_and_Size(BigSize, "font/upheavtt.ttf", 140);
    bool flag3 = Get_Font_Type_and_Size(MediumSize, "font/upheavtt.ttf", 80);
    bool flag4 = Get_Font_Type_and_Size(SmallSize, "font/upheavtt.ttf", 30);
    return (flag1 && flag2 && flag3 && flag4);
}

bool Font::Render_Text(SDL_Renderer* renderer, const char* text, TTF_Font* font,
    SDL_Color text_color, SDL_Rect* rect) {
    SDL_Surface* text_surface = TTF_RenderText_Solid(g_font, text, text_color);
    if (text_surface == NULL) {
        std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
        return false;
    }
    
    g_texture = SDL_CreateTextureFromSurface(renderer, text_surface); 

    if (g_texture == NULL) {
        std::cout << "Failed to create texture for text: " << TTF_GetError() << std::endl;
        return false;
    }
    

    SDL_RenderCopy(renderer, g_texture, NULL, rect);
    SDL_DestroyTexture(g_texture);
    SDL_FreeSurface(text_surface);

    return true;
}

