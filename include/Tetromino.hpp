#pragma once
#include <array>
#include <random>
#include "Entity.hpp"
#include "Constants.hpp"

class Tetromino
{
public:
	Tetromino(std::mt19937_64 &rd);
private:
	std::array<std::array<bool, 4>, 4> grid_;
	SDL_Color color_;
	int tetromino_type_;
};