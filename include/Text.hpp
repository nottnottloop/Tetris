#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Entity.hpp"

class Text : public Entity {
public:
	Text(Vector2f pos, Vector2f offset);
	void loadFontTexture(SDL_Color color, const char* text, bool blended=false, bool wrapped=false, int wrap_length=0);
	void openFont(const char* file_path, int size);
	SDL_Rect renderTextInfo();
	SDL_Rect renderCenteredTextInfo();
private:
	TTF_Font* font_;
};