#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "GameState.hpp"
#include "Text.hpp"
#include "BasicButton.hpp"

class IntroState : public GameState {
public:
	IntroState();
	void playMusic();
	void handleInput(Game &game, const SDL_Event &event);
	void update(Game &game);
private:
	Mix_Music *music_;
	Text text_;
	Text flavor_text_;
	Text controls_text_1_;
	Text controls_text_2_;
	Text controls_text_3_;
	BasicButton play_button_;
	bool mouse_down_;
	int mouse_x_;
	int mouse_y_;
};