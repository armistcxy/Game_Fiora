#include "Button.h"
Button::Button() {
	mouse_rect.w = 0;
	mouse_rect.h = 0; 
	button_rect = new SDL_Rect;
	button_rect->w = BUTTON_SIZE;
	button_rect->h = BUTTON_SIZE;

}
void Button::Render_button(SDL_Renderer* renderer, std::string id) {
	button_texture.Render(renderer, id, button_rect->x, button_rect->y,
		button_rect->w, button_rect->h);
}
void Button::Handle_event(SDL_Event* event) {

}
void Button::Set_position() {
	int x, y;
	SDL_GetMouseState(&x, &y);

	mouse_rect.x = x;
	mouse_rect.y = y;
}

void Button::Init_position(int x, int y) {
	button_rect->x = x;
	button_rect->y = y;
}

SDL_Rect* Button::Get_Rect() {
	return button_rect;
}

bool Button::Light_or_Dark() {
	Set_position();
	return CheckCollision(*button_rect, mouse_rect);
}