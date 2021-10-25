#pragma once
#include <SDL.h>
#include <utility>
#include <vector>
#include <array>
#include <random>
#include "Math.hpp"
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
	void advanceGame();
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
	bool button_down_;
	int button_held_down_duration_;
	bool game_over_;
	Text game_over_text_;
};