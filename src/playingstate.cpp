#include <iostream>
#include <fstream>
#include <SDL.h>
#include "PlayingState.hpp"
#include "Text.hpp"
#include "RenderWindow.hpp"
#include "Game.hpp"
#include "Constants.hpp"
#include "BasicButton.hpp"

extern RenderWindow window;

PlayingState::PlayingState()
:GameState("PlayingState"),
game_over_(true),
game_over_text_({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, {0, 0})
{
	game_over_text_.openFont("res/fixedsys.ttf", 30);
	game_over_text_.loadFontTexture(RED, "Game Over!");
}

void PlayingState::gameOver() {
	game_over_ = true;
}

void PlayingState::resetGame() {
	game_over_ = false;
}

void PlayingState::handleInput(Game &game, const SDL_Event &event) {
	switch (event.type) {
		case SDL_QUIT:
			game.quit_ = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {

			}
	}
}

void PlayingState::update(Game& game) {
	window.clear(BLACK, 0xFF);
	if (game_over_) {
		window.render(game_over_text_, true);
	}
	window.display();
	window.showWindow();
}