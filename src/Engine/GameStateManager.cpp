#include "Headers/GameStateManager.hpp"

GameState::GameState() : currentState(MENU) {}

GameState& GameState::getInstance()
{
	static GameState instance;
	return instance;
}

State GameState::getGameState() const
{
	return currentState;
}

void GameState::setGameState(State newState) 
{
	currentState = newState;
}