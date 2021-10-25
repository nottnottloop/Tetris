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

std::wstring tetromino[7];

PlayingState::PlayingState()
:GameState("PlayingState"),
game_over_(false),
game_over_text_({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, {0, 0}),
ticks_needed_(300),
piece_falling_(false),
button_down_(false),
button_held_down_duration_(0)
{
	rd_.seed(std::random_device{}());
	ticks_at_last_update_ = SDL_GetTicks() + ticks_needed_;
	game_over_text_.openFont("res/fixedsys.ttf", 30);
	game_over_text_.loadFontTexture(RED, "Game Over!");

	//create tetrominoes
	//I shape
	tetromino[0].append(L"..C...C...C...C.");
	//T shape
	tetromino[1].append(L"..P..PP...P.....");
	//O shape, A for gold or chemical symbol Au
	tetromino[2].append(L".....AA..AA.....");
	//Z shape
	tetromino[3].append(L"..R..RR..R......");
	//S shape
	tetromino[4].append(L".G...GG...G.....");
	//L shape
	tetromino[5].append(L".O...O...OO.....");
	//J shape
	tetromino[6].append(L"..B...B..BB.....");

}

void PlayingState::advanceGame()
{
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
		case SDL_KEYUP:
			button_down_ = false;
			button_held_down_duration_ = 0;
			break;
		case SDL_KEYDOWN:
			button_held_down_duration_++;
			//std::cout << button_down_held_delay_ << std::endl;
			switch (event.key.keysym.sym)
			{
			}
	}
}

void PlayingState::update(Game& game) 
{
	if (SDL_GetTicks() - ticks_at_last_update_ > ticks_needed_)
	{
		ticks_at_last_update_ = SDL_GetTicks();
	}

	window.clear(BLACK, 0xFF);

	//tetromino blocks
	//for (int r = 0; r < BOARD_ROWS; r++)
	//{
	//	for (int c = 0; c < BOARD_COLS; c++)
	//	{
	//		if (board_[r][c].first)
	//		{
	//			window.renderRect({(SCREEN_WIDTH / 2 - CELL_SIZE * 5) + CELL_SIZE * c, r * CELL_SIZE, CELL_SIZE, CELL_SIZE}, board_[r][c].second);
	//		}
	//	}
	//	}

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