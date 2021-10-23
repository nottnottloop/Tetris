#pragma once

#include <iostream>

struct Vector2f
{
	Vector2f()
	:x(0.0f), y(0.0f)
	{}

	Vector2f(float p_x, float p_y)
	:x(p_x), y(p_y)
	{}

	Vector2f operator+(const Vector2f other) const {
		return {x + other.x, y + other.y};
	}

	Vector2f operator-(const Vector2f other) const {
		return {x - other.x, y - other.y};
	}

	Vector2f& operator=(const Vector2f &other) {
		x = other.x;
		y = other.y;

		return *this;
	}

	void print()
	{
		std::cout << x << ", " << y << std::endl;
	}

	float x, y;
};

struct Vector2
{
	Vector2()
	:x(0), y(0)
	{}

	Vector2(int p_x, int p_y)
	:x(p_x), y(p_y)
	{}

	Vector2 operator+(const Vector2 other) const {
		return {x + other.x, y + other.y};
	}

	Vector2 operator-(const Vector2 other) const {
		return {x - other.x, y - other.y};
	}

	Vector2& operator=(const Vector2 &other) {
		x = other.x;
		y = other.y;

		return *this;
	}

	void print()
	{
		std::cout << x << ", " << y << std::endl;
	}

	int x, y;
};

