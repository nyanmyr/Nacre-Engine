#ifndef GAME_STATE_MANAGER_HPP
#define GAME_STATE_MANAGER_HPP

enum State
{
	MENU,
	PLAYING,
	PAUSED
};

class GameState
{
public:
	GameState();

	static GameState& getInstance();
	GameState(const GameState&) = delete;
	GameState& operator=(const GameState&) = delete;

	State getGameState() const;
	void setGameState(State newState);

private:
	State currentState;
};

#endif