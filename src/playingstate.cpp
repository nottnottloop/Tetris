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
ticks_needed_(300),
piece_falling_(false),
current_tetromino_(rd_),
button_down_(false),
button_held_down_duration_(0)
{
	rd_.seed(std::random_device{}());
	ticks_at_last_update_ = SDL_GetTicks() + ticks_needed_;
	game_over_text_.openFont("res/fixedsys.ttf", 30);
	game_over_text_.loadFontTexture(RED, "Game Over!");

	for (int r = 0; r < BOARD_ROWS; r++)
	{
		for (int c = 0; c < BOARD_COLS; c++)
		{
			board_[r][c] = std::make_pair(false, BLACK);
		}
	}
}

void PlayingState::advanceGame()
{
	if (!piece_falling_)
	{
		spawnTetromino();
	}
	else if (isValidMove(0, 1))
	{
		deleteOldTetrominoLocation();
		y_index_++;
		moveTetromino(0);
	}
}

void PlayingState::spawnTetromino()
{
	current_tetromino_ = Tetromino(rd_);
	piece_falling_ = true;
	x_index_ = 0;
	y_index_ = -1;
	moveTetromino(0);
}

bool PlayingState::isValidMove(int x_move, int y_move)
{
	//check if we can move
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			if (current_tetromino_.grid_[r][c])
			{
				if (x_index_ + x_move + c < 0 || x_index_ + x_move + c > 9 || y_index_ == 15)
				{
					return false;
				}
			}
		}
	}
	return true;
}

void PlayingState::deleteOldTetrominoLocation()
{
	//delete old piece
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			if (current_tetromino_.grid_[r][c])
			{
				board_[y_index_ + r][x_index_ + c] = {false, current_tetromino_.color_};
			}
		}
	}
}

void PlayingState::moveTetromino(int index)
{
	if (!isValidMove(index, 0))
	{
		return;
	}

	deleteOldTetrominoLocation();

	x_index_ += index;

	//move the piece
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			if (current_tetromino_.grid_[r][c])
			{
				board_[y_index_ + r][x_index_ + c] = {true, current_tetromino_.color_};
			}
		}
	}
	updateBoard();
}

void PlayingState::rotateTetromino(bool anti_clockwise_or_not)
{
	deleteOldTetrominoLocation();
	current_tetromino_.rotate(anti_clockwise_or_not);
	moveTetromino(0);
}

void PlayingState::updateBoard()
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
				case SDLK_LEFT:
					if (!button_down_ || button_held_down_duration_ > BUTTON_HOLD_DOWN_AMOUNT)
					{
						moveTetromino(-1);
						button_held_down_duration_ -= 2;
						button_down_ = true;
					}
					break;
				case SDLK_RIGHT:
					if (!button_down_ || button_held_down_duration_ > BUTTON_HOLD_DOWN_AMOUNT)
					{
						moveTetromino(1);
						button_held_down_duration_ -= 2;
						button_down_ = true;
					}
					break;
				case SDLK_UP:
					if (!button_down_)
					{
						rotateTetromino(true);
						button_down_ = true;
					}
					break;
				case SDLK_DOWN:
					if (!button_down_)
					{
						rotateTetromino(false);
						button_down_ = true;
					}
					break;
				case SDLK_SPACE:
					deleteOldTetrominoLocation();
					spawnTetromino();
					break;
			}
	}
}

void PlayingState::update(Game& game) 
{
	if (SDL_GetTicks() - ticks_at_last_update_ > ticks_needed_)
	{
		ticks_at_last_update_ = SDL_GetTicks();
		advanceGame();
	}

	window.clear(BLACK, 0xFF);

	//tetromino blocks
	for (int r = 0; r < BOARD_ROWS; r++)
	{
		for (int c = 0; c < BOARD_COLS; c++)
		{
			if (board_[r][c].first)
			{
				window.renderRect({(SCREEN_WIDTH / 2 - CELL_SIZE * 5) + CELL_SIZE * c, r * CELL_SIZE, CELL_SIZE, CELL_SIZE}, board_[r][c].second);
			}
		}
		}

	//render current tetromino
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			if (current_tetromino_.grid_[r][c])
			{
				//window.renderRect({SCREEN_WIDTH / 2 + CELL_SIZE * (x_index_ + c), (y_index_ + r) * CELL_SIZE, CELL_SIZE, CELL_SIZE}, current_tetromino_.color_);
			}
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