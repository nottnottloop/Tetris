#include <random>
#include "Tetromino.hpp"

Tetromino::Tetromino(std::mt19937_64 &rd)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			grid_[i][j] = false;
		}
	}

	switch (rd() % 7)
	{
		//L shape (orange)
		case 0:
			grid_[2][1] = true;
			grid_[2][2] = true;
			grid_[2][3] = true;
			grid_[1][3] = true;
			color_ = TETRIS_ORANGE;
			tetromino_type_ = TYPE_L;
			break;
		//T shape (purple)
		case 1:
			grid_[1][2] = true;
			grid_[2][2] = true;
			grid_[2][1] = true;
			grid_[2][3] = true;
			color_ = TETRIS_PURPLE;
			tetromino_type_ = TYPE_T;
			break;
		//S shape (green)
		case 2:
			grid_[3][1] = true;
			grid_[2][2] = true;
			grid_[3][2] = true;
			grid_[2][3] = true;
			color_ = TETRIS_GREEN;
			tetromino_type_ = TYPE_S;
			break;
		//Z shape (red)
		case 3:
			grid_[3][2] = true;
			grid_[2][2] = true;
			grid_[3][3] = true;
			grid_[2][1] = true;
			color_ = TETRIS_RED;
			tetromino_type_ = TYPE_Z;
			break;
		//J shape (blue)
		case 4:
			grid_[2][1] = true;
			grid_[2][2] = true;
			grid_[2][3] = true;
			grid_[1][1] = true;
			color_ = TETRIS_BLUE;
			tetromino_type_ = TYPE_J;
			break;
		//O shape (gold)
		case 5:
			grid_[1][2] = true;
			grid_[1][3] = true;
			grid_[2][2] = true;
			grid_[2][3] = true;
			color_ = TETRIS_GOLD;
			tetromino_type_ = TYPE_O;
			break;
		//I shape (cyan)
		case 6:
			grid_[3][0] = true;
			grid_[3][1] = true;
			grid_[3][2] = true;
			grid_[3][3] = true;
			color_ = TETRIS_CYAN;
			tetromino_type_ = TYPE_I;
			break;
	}
}