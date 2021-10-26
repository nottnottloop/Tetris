#include <iostream>
#include <utility>
#include <SDL.h>
#include <limits.h>
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
game_over_text_({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50}, {0, 0}),
ticks_needed_(300),
button_down_(false),
currentPiece(0),
currentRotation(0),
currentX(nFieldWidth / 2),
currentY(0),
score(0),
button_held_down_duration_(0),
forceDown(false),
score_box_({SCREEN_WIDTH / 2 + 250, 50, 200, 100}, {0, 0}, WHITE, BLACK, WHITE, 3, score_text_)
{
	rd_.seed(std::random_device{}());
	ticks_at_last_update_ = SDL_GetTicks() + ticks_needed_;
	game_over_text_.openFont("res/fixedsys.ttf", 100);
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

	updateScoreBox();

	music_ = Mix_LoadMUS("res/tetris.mp3");
}

void PlayingState::playMusic()
{
	Mix_VolumeMusic(5);
	Mix_PlayMusic(music_, -1);
}

void PlayingState::updateScoreBox()
{
	char message[20];
	sprintf(message, "Score: %d", score);
	score_box_.updateText(message);
}

int PlayingState::rotate(int x, int y, unsigned int r)
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

void PlayingState::moveTetromino(int x, int y, int r)
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
	else if (r != 0)
	{
		if (doesPieceFit(currentPiece, currentRotation + r, currentX, currentY))
		{
			currentRotation += r;
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
			switch (event.key.keysym.sym)
			{
				case SDLK_LEFT:
				case SDLK_RIGHT:
				case SDLK_DOWN:
					button_down_ = false;
					button_held_down_duration_ = 0;
					break;
				case SDLK_x:
				case SDLK_z:
					rotate_button_down_ = false;
					break;
			}
			break;
		case SDL_KEYDOWN:
			button_held_down_duration_++;
			switch (event.key.keysym.sym)
			{
				case SDLK_LEFT:
					if (!button_down_ || button_held_down_duration_ > BUTTON_HOLD_DOWN_AMOUNT)
					{
						button_held_down_duration_ -= 2;
						button_down_ = true;
						moveTetromino(-1, 0, 0);
					}
					break;
				case SDLK_RIGHT:
					if (!button_down_ || button_held_down_duration_ > BUTTON_HOLD_DOWN_AMOUNT)
					{
						button_held_down_duration_ -= 2;
						button_down_ = true;
						moveTetromino(1, 0, 0);
					}
					break;
				case SDLK_z:
					if (!rotate_button_down_)
					{
						rotate_button_down_ = true;
						moveTetromino(0, 0, -1);
					}
					break;
				case SDLK_x:
					if (!rotate_button_down_)
					{
						rotate_button_down_ = true;
						moveTetromino(0, 0, 1);
					}
					break;
				case SDLK_DOWN:
					if (!button_down_ || button_held_down_duration_ > BUTTON_HOLD_DOWN_AMOUNT_FOR_GOING_DOWN)
					{
						button_held_down_duration_ -= 2;
						button_down_ = true;
						moveTetromino(0, 1, 0);
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
		forceDown = true;
	}

	window.clear(BLACK, 0xFF);


	//tetromino blocks
	for (int x = 0; x < nFieldWidth; x++)
	{
		for (int y = 0; y < nFieldHeight; y++)
			{
				SDL_Color display_color = getBlockDisplayColor(pField[y*nFieldWidth + x]);
				window.renderRect({(SCREEN_WIDTH / 2 - CELL_SIZE * 6) + CELL_SIZE * x, y * CELL_SIZE, CELL_SIZE, CELL_SIZE}, display_color);
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
				window.renderRect({(SCREEN_WIDTH / 2 - CELL_SIZE * 6) + CELL_SIZE * i + CELL_SIZE * currentX, CELL_SIZE * j + CELL_SIZE * currentY, CELL_SIZE, CELL_SIZE}, display_color);
			}
		}
	}

	if (forceDown)
	{
		if (doesPieceFit(currentPiece, currentRotation, currentX, currentY + 1))
			currentY++;
		else
		{
			// It can't! Lock the piece in place
			for (int px = 0; px < 4; px++)
				for (int py = 0; py < 4; py++)
					if (tetromino[currentPiece][rotate(px, py, currentRotation)] != L'.')
						pField[(currentY + py) * nFieldWidth + (currentX + px)] = tetromino[currentPiece][rotate(px, py, currentRotation)];

			// Check for lines
			for (int py = 0; py < 4; py++)
				if (currentY + py < nFieldHeight - 1)
				{
					bool bLine = true;
					for (int px = 1; px < nFieldWidth - 1; px++)
						bLine &= (pField[(currentY + py) * nFieldWidth + px]) != 0;

					if (bLine)
					{
						// Remove Line, set to =
						for (int px = 1; px < nFieldWidth - 1; px++)
							pField[(currentY + py) * nFieldWidth + px] = 8;
						vLines.push_back(currentY + py);
					}
				}

			score += 25;
			if (!vLines.empty())	score += (1 << vLines.size()) * 100;

			// Pick New Piece
			currentX = nFieldWidth / 2;
			currentY = 0;
			currentRotation = 0;
			currentPiece = rand() % 7;

			// If piece does not fit straight away, game over!
			game_over_ = !doesPieceFit(currentPiece, currentRotation, currentX, currentY);
		}
		forceDown = false;
	}

	if (!vLines.empty())
		{
			for (auto &v : vLines)
				for (int px = 1; px < nFieldWidth - 1; px++)
				{
					for (int py = v; py > 0; py--)
						pField[py * nFieldWidth + px] = pField[(py - 1) * nFieldWidth + px];
					pField[px] = 0;
				}

			vLines.clear();
		}

	//render score box
	if (!game_over_)
	{
		updateScoreBox();
	}
	window.render(score_box_);

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