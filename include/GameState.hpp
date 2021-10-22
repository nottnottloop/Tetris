#pragma once
#include <SDL.h>
#include <string>

class Game;

class GameState {
public:
	GameState();
	GameState(std::string state_name);
	virtual void handleInput(Game &game, const SDL_Event &event) = 0;
	virtual void update(Game &game) = 0;
protected:
	bool initialised_;
	std::string state_name_;
};