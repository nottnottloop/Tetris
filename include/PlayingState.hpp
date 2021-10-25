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
	int rotate(int x, int y, int r);
	bool doesPieceFit(int tetromino, int rotation, int x, int y);
	SDL_Color getBlockDisplayColor(char character);
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
	unsigned char *pField;

	int currentPiece;
	int currentRotation;
	int currentX;
	int currentY;

	int x_index_;
	int y_index_;
	bool button_down_;
	int button_held_down_duration_;
	bool game_over_;
	Text game_over_text_;
};