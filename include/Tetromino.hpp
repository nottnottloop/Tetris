#pragma once
#include <array>
#include <random>
#include <string>
#include "Entity.hpp"
#include "Constants.hpp"

class Tetromino
{
public:
	Tetromino(std::mt19937_64 &rd);
	std::array<std::array<bool, 4>, 4> grid_;
	SDL_Color color_;
	int tetromino_type_;
	std::string tetromino_type_name_;
};