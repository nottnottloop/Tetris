#include <iostream>
#include <utility>
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
game_over_(false),
game_over_text_({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, {0, 0}),
ticks_needed_(300)
{
	rd_.seed(std::random_device{}());
	ticks_at_last_update_ = SDL_GetTicks() + ticks_needed_;
	game_over_text_.openFont("res/fixedsys.ttf", 30);
	game_over_text_.loadFontTexture(RED, "Game Over!");

	for (int r = 0; r < BOARD_ROWS; r++)
	{
		for (int c = 0; c < BOARD_COLS; c++)
		{
			board_[r][c] = std::make_pair(true, BLUE);
		}
	}
}

void PlayingState::advanceGame()
{
	if (!piece_falling_)
	{
		spawnTetromino();
	}
}

void PlayingState::spawnTetromino()
{
	tetrominoes_.push_back(Tetromino(rd_));
}

void PlayingState::gameOver() 
{
	game_over_ = true;
}

void PlayingState::resetGame() 
{
	game_over_ = false;
}

void PlayingState::handleInput(Game &game, const SDL_Event &event) 
{
	switch (event.type) 
	{
		case SDL_QUIT:
			game.quit_ = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_SPACE:
					break;
			}
	}
}

void PlayingState::update(Game& game) 
{
	//if (SDL_GetTicks() - ticks_at_last_update_ > ticks_needed_)
	//{
	//	ticks_at_last_update_ = SDL_GetTicks();
	//	advanceGame();
	//}

	window.clear(BLACK, 0xFF);

	//tetromino blocks
	for (int r = 0; r < BOARD_ROWS; r++)
	{
		for (int c = 0; c < BOARD_COLS; c++)
		{
			window.renderRect({(SCREEN_WIDTH / 2 - CELL_SIZE * 5) + CELL_SIZE * c, r * CELL_SIZE, CELL_SIZE, CELL_SIZE}, board_[r][c].second);
		}
	}

	//rows
	for (int r = 18; r > 0; r--)
	{
		window.renderRect({(SCREEN_WIDTH / 2 - CELL_SIZE * 5), (SCREEN_HEIGHT - CELL_SIZE * r), CELL_SIZE *BOARD_COLS, 1}, GAINSBORO);
	}
	//get pesky bottom row line drawn
	//window.renderRect({(SCREEN_WIDTH / 2 - CELL_SIZE * 5), SCREEN_HEIGHT - 3, CELL_SIZE * BOARD_COLS, 3}, GAINSBORO);

	//columns
	for (int c = 0; c < 11; c++)
	{
		int thickness = 1;
		if (c == 0 || c == 10)
		{
			thickness = 3;
		}
		window.renderRect({(SCREEN_WIDTH / 2 - CELL_SIZE * 5) + c * CELL_SIZE, 0, thickness, SCREEN_HEIGHT}, GAINSBORO);
	}

	//render game over text if game over
	if (game_over_)
	{
		window.render(game_over_text_, true);
	}
	window.display();
	window.showWindow();
}