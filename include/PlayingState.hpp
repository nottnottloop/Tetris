#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
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
	void playMusic();
	void updateScoreBox();
	int rotate(int x, int y, unsigned int r);
	bool doesPieceFit(int tetromino, int rotation, int x, int y);
	SDL_Color getBlockDisplayColor(char character);
	void moveTetromino(int x, int y, int r);
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

	unsigned int currentPiece;
	unsigned int currentRotation;
	int currentX;
	int currentY;
	int score;
	bool forceDown;
	std::vector<int> vLines;

	bool button_down_;
	bool rotate_button_down_;
	int button_held_down_duration_;
	bool game_over_;
	Text game_over_text_;
	BasicButton score_box_;
	char score_text_[20];
	Mix_Music *music_;
};