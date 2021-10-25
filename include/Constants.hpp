#pragma once
#include <SDL.h>

//#define DEBUG_CONTROLS 1

constexpr int SCREEN_WIDTH = 1024;
constexpr int SCREEN_HEIGHT = 760;

constexpr int BOARD_ROWS = 19;
constexpr int BOARD_COLS = 10;
constexpr int CELL_SIZE = 40;

enum PIECE_TYPE
{
	TYPE_L,
	TYPE_T,
	TYPE_S,
	TYPE_Z,
	TYPE_J,
	TYPE_O,
	TYPE_I,
};

//tetris colors
constexpr SDL_Color TETRIS_ORANGE = {254, 163, 8};
constexpr SDL_Color TETRIS_PURPLE = {133, 96, 165};
constexpr SDL_Color TETRIS_GREEN = {1, 255, 28};
constexpr SDL_Color TETRIS_RED = {255, 1, 3};
constexpr SDL_Color TETRIS_BLUE = {0, 0, 197};
constexpr SDL_Color TETRIS_GOLD = {120, 115, 5};
constexpr SDL_Color TETRIS_CYAN = {0, 186, 185};

constexpr int BUTTON_HOLD_DOWN_AMOUNT = 30;

constexpr SDL_Color MODS_BLUE = {0x00, 0xCE, 0xFF};
constexpr SDL_Color GAINSBORO = {220, 220, 220};
constexpr SDL_Color DISNEY_GOOFY_COLOR = {237, 126, 32};
constexpr SDL_Color LIGHT_PURPLE = {203, 195, 227};
constexpr SDL_Color SKY_BLUE = {135, 206, 235};
constexpr SDL_Color BUBBLE = {0xD7, 0xEA, 0xF9};
constexpr SDL_Color CLASSIC_BACKGROUND = {12, 67, 114};
constexpr SDL_Color NEW_BACKGROUND = {64, 114, 148};
constexpr SDL_Color RED = {255, 0, 0};
constexpr SDL_Color GREEN = {0, 255, 0};
constexpr SDL_Color LIGHT_GREEN = {144, 238, 144};
constexpr SDL_Color FERN = {113, 188, 120};
constexpr SDL_Color JUNGLE_GREEN = {41, 171, 135};
constexpr SDL_Color HONEYDEW = {240, 255, 240};
constexpr SDL_Color BLUE = {0, 0, 255};
constexpr SDL_Color CYAN = {0, 255, 255};
constexpr SDL_Color PEACH = {255, 229, 180};
constexpr SDL_Color PURPLE = {128, 0, 128};
constexpr SDL_Color ORANGE_RED = {255, 69, 0};
constexpr SDL_Color WHITE = {255, 255, 255};
constexpr SDL_Color BLACK = {0, 0, 0};
constexpr SDL_Color PASTEL_BLUE = {126, 214, 223};
constexpr SDL_Color LIME_GREEN = {186, 220, 88};
