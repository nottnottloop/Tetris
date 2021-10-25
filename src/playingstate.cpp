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
button_down_(false),
currentPiece(0),
currentRotation(0),
currentX(nFieldWidth / 2),
currentY(0),
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

	pField = new unsigned char[nFieldWidth*nFieldHeight]; // Create play field buffer
	for (int x = 0; x < nFieldWidth; x++) // Board Boundary
		for (int y = 0; y < nFieldHeight; y++)
			pField[y*nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;

}

int PlayingState::rotate(int x, int y, int r)
{
	switch (r % 4)
	{
		case 0:
			return y * 4 + x;
		case 1:
			return 12 + y - (x * 4);
		case 2:
			return 15 - (y * 4) - x;
		case 3:
			return 3 - y + (x * 4);
	}
	return 0;
}

SDL_Color PlayingState::getBlockDisplayColor(char character)
{
	SDL_Color display_color = BLACK;
	switch (character)
	{
		case L'.':
			display_color = BLACK;
			break;
		case L'C':
			display_color = TETRIS_CYAN;
			break;
		case L'A':
			display_color = TETRIS_GOLD;
			break;
		case L'O':
			display_color = TETRIS_ORANGE;
			break;
		case L'G':
			display_color = TETRIS_GREEN;
			break;
		case L'P':
			display_color = TETRIS_PURPLE;
			break;
		case L'R':
			display_color = TETRIS_RED;
			break;
		case L'B':
			display_color = TETRIS_BLUE;
			break;
	}
	return display_color;
}

bool PlayingState::doesPieceFit(int nTetromino, int rotation, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//get index to access piece with
			int pi = rotate(i, j, rotation);

			//get index to access field
			int fi = (y + j) * nFieldWidth + (x + i);

			if (x + i >= 0 && x + i < nFieldWidth)
			{
				if (y + j >= 0 && y + j < nFieldHeight)
				{
					// In Bounds so do collision check
					if (tetromino[nTetromino][pi] != L'.' && pField[fi] != 0)
						return false; // fail on first hit
				}
			}
		}
	}
	return true;
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

void PlayingState::moveTetromino(int x, int y)
{
	if (x == -1)
	{
		if (doesPieceFit(currentPiece, currentRotation, currentX - 1, currentY))
		{
			currentX -= 1;
		}
	}
	else if (x == 1)
	{
		if (doesPieceFit(currentPiece, currentRotation, currentX + 1, currentY))
		{
			currentX += 1;
		}
	}
	else if (y == 1)
	{
		if (doesPieceFit(currentPiece, currentRotation, currentX, currentY + 1))
		{
			currentY += 1;
		}
	}
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
						button_held_down_duration_ -= 2;
						button_down_ = true;
						moveTetromino(-1, 0);
					}
					break;
				case SDLK_RIGHT:
					if (!button_down_ || button_held_down_duration_ > BUTTON_HOLD_DOWN_AMOUNT)
					{
						button_held_down_duration_ -= 2;
						button_down_ = true;
						moveTetromino(1, 0);
					}
					break;
				case SDLK_UP:
					if (!button_down_)
					{
						button_down_ = true;
					}
					break;
				case SDLK_DOWN:
					if (!button_down_ || button_held_down_duration_ > BUTTON_HOLD_DOWN_AMOUNT)
					{
						button_held_down_duration_ -= 2;
						button_down_ = true;
						moveTetromino(0, 1);
					}
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
	for (int x = 0; x < nFieldWidth; x++)
	{
		for (int y = 0; y < nFieldHeight; y++)
			{
				SDL_Color display_color = getBlockDisplayColor(pField[y*nFieldWidth + x]);
				window.renderRect({(SCREEN_WIDTH / 2 - CELL_SIZE * 5) + CELL_SIZE * x, y * CELL_SIZE, CELL_SIZE, CELL_SIZE}, display_color);
			}
		}

	//draw current piece
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (tetromino[currentPiece][rotate(i, j, currentRotation)] != L'.')
			{
				SDL_Color display_color = getBlockDisplayColor(tetromino[currentPiece][rotate(i, j, currentRotation)]);
				window.renderRect({(SCREEN_WIDTH / 2 - CELL_SIZE * 5) + CELL_SIZE * i + CELL_SIZE * (currentX - 1), CELL_SIZE * j + CELL_SIZE * currentY, CELL_SIZE, CELL_SIZE}, display_color);
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