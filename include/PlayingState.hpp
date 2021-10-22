#pragma once
#include <SDL.h>
#include <vector>
#include <array>
#include <random>
#include "GameState.hpp"
#include "Text.hpp"
#include "Entity.hpp"
#include "Constants.hpp"
#include "BasicButton.hpp"

class PlayingState : public GameState {
public:
	PlayingState();
	void handleInput(Game &game, const SDL_Event &event);
	void update(Game &game);
	void gameOver();
	void resetGame();
private:
	bool game_over_;
	Text game_over_text_;
};