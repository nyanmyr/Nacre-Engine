#include "Headers/Initialize.hpp"
#include "Headers/GameStateManager.hpp"

EntityManager& emInitialize = EntityManager::getInstance();
ComponentManager& cmInitialize = ComponentManager::getInstance();
GameState& gsInitialize = GameState::getInstance();

Entity playerID = emInitialize.createEntity();

void Initialize()
{
	Entity button = emInitialize.createEntity();
	cmInitialize.addComponent
	(
		button,
		CPosition
		{
			0.0f,
			0.0f
		}
	);
	cmInitialize.addComponent
	(
		button,
		CShape
		{
			RectangleShape(Vector2f(100.0f,50.0f))
		}
	);
	cmInitialize.addComponent(
		button,
		CZIndex{
			0
		}
	);
	cmInitialize.getComponent<CShape>(button).rect.setFillColor(Color::White);
	cmInitialize.addComponent(
		button,
		CVisibleState{
			MENU
		}
	);

	Entity button1 = emInitialize.createEntity();
	cmInitialize.addComponent
	(
		button1,
		CPosition
		{
			50.0f,
			25.0f
		}
	);
	cmInitialize.addComponent
	(
		button1,
		CShape
		{
			RectangleShape(Vector2f(100.0f,50.0f))
		}
	);
	cmInitialize.addComponent(
		button1,
		CZIndex{
			1
		}
	);
	cmInitialize.getComponent<CShape>(button1).rect.setFillColor(Color::Red);
	cmInitialize.addComponent(
		button1,
		CVisibleState{
			PLAYING
		}
	);
}

void RegisterComponents()
{
	cmInitialize.registerComponent<CPosition>();
	cmInitialize.registerComponent<CLineSegment>();
	cmInitialize.registerComponent<CVelocity>();
	cmInitialize.registerComponent<CShape>();
	//cmInitialize.registerComponent<Collision>();
	cmInitialize.registerComponent<CLifeTime>();
	cmInitialize.registerComponent<CZIndex>();
	cmInitialize.registerComponent<CVisibleState>();
}

Entity GetPlayerID()
{
	return playerID;
}