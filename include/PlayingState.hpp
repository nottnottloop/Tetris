#pragma once
#include <SDL.h>
#include <utility>
#include <vector>
#include <array>
#include <random>
#include "GameState.hpp"
#include "Text.hpp"
#include "Entity.hpp"
#include "Constants.hpp"
#include "BasicButton.hpp"
#include "Tetromino.hpp"

class PlayingState : public GameState {
public:
	PlayingState();
	void handleInput(Game &game, const SDL_Event &event);
	void update(Game &game);
	void gameOver();
	void resetGame();
private:
	std::vector<Tetromino> tetrominoes_;
	std::array<std::array<std::pair<bool, SDL_Color>, BOARD_ROWS>, BOARD_COLS> board_;
	bool game_over_;
	Text game_over_text_;
};