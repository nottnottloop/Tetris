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
	void advanceGame();
	void spawnTetromino();
	void gameOver();
	void resetGame();
private:
	std::mt19937_64 rd_;
	Uint32 ticks_needed_;
	Uint32 ticks_at_last_update_;
	Uint32 counter_end_;
	bool piece_falling_;
	int x_index_;
	int y_index_;
	Tetromino current_tetromino_;
	std::array<std::array<std::pair<bool, SDL_Color>, BOARD_COLS>, BOARD_ROWS> board_;
	bool game_over_;
	Text game_over_text_;
};