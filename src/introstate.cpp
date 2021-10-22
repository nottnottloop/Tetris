#include <iostream>
#include <SDL.h>
#include "IntroState.hpp"
#include "Text.hpp"
#include "RenderWindow.hpp"
#include "Game.hpp"
#include "BasicButton.hpp"
#include "Constants.hpp"
#include "Math.hpp"

extern RenderWindow window;

IntroState::IntroState()
:GameState("IntroState"),
text_({0, 0}, {0, 0}),
flavor_text_({0, 100}, {0, 0}),
play_button_({SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, 200, 100}, {0, 0}, BLACK, GAINSBORO, RED, 5, "Tetris Time")
{
	text_.openFont("res/fixedsys.ttf", 100);
	text_.loadFontTexture(WHITE, "Tetris");
	flavor_text_.openFont("res/fixedsys.ttf", 25);
	flavor_text_.loadFontTexture(WHITE, "Ominous black background...");
}

void IntroState::handleInput(Game &game, const SDL_Event &event) {
		switch (event.type) {
			case SDL_QUIT:
				game.quit_ = true;
				break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouse_x_, &mouse_y_);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse_down_ = true;
				break;
			case SDL_KEYDOWN:
			case SDL_MOUSEBUTTONUP:
				if (mouse_down_) {
				}
				mouse_down_ = false;
				break;
		}
}

void IntroState::update(Game &game) {
	window.clear(BLACK, 0xFF);
	window.render(text_);
	window.render(flavor_text_);
	window.render(play_button_);
	window.display();
	window.showWindow();
}