#pragma once
#include <array>
#include <random>
#include <string>
#include "Entity.hpp"
#include "Constants.hpp"

class Tetromino
{
	using Grid = std::array<std::array<bool, 4>, 4>;
public:
	Tetromino(std::mt19937_64 &rd);
	void rotate(bool anti_clockwise);
	void translateGrid(bool anti_clockwise);
	Grid grid_;
	SDL_Color color_;
	int tetromino_type_;
	std::string tetromino_type_name_;
private:
	void translateGrid(int x, int y);
};