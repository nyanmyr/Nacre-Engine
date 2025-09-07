#include "Headers/Initialize.hpp"

EntityManager& emInitialize = EntityManager::getInstance();
ComponentManager& cmInitialize = ComponentManager::getInstance();

Entity playerID = emInitialize.createEntity();

void Initialize()
{
	//RectangleShape tile = RectangleShape(Vector2f(50.f, 50.f));
//tile.setFillColor(Color::Black);
//tile.setOutlineColor(Color::White);
//tile.setOutlineThickness(1);

//for (size_t row = 0; row < 12; row++)
//{
//	for (size_t col = 0; col < 16; col++)
//	{
//		Entity tileID = em.createEntity();

//		cm.addComponent(
//			tileID, 
//			Position{
//			col * 50.f,
//			row * 50.f
//			}
//		);

//		cm.addComponent(tileID, ShapeComponent{tile});
//	}
//}

	cmInitialize.addComponent
	(
		playerID,
		CPosition
		{
			0.0f,
			0.0f
		}
	);
	cmInitialize.addComponent
	(
		playerID,
		CVelocity
		{
			0.0f,
			0.0f
		}
	);
	cmInitialize.addComponent
	(
		playerID,
		CShape
		{
			RectangleShape(Vector2f(50.0f,50.0f))
		}
	);
	cmInitialize.getComponent<CShape>(playerID).rect.setFillColor(Color(100, 100, 250));
	cmInitialize.addComponent(
		playerID,
		CZIndex{
			1
		}
	);
}

void RegisterComponents()
{
	cmInitialize.registerComponent<CPosition>();
	cmInitialize.registerComponent<CVelocity>();
	cmInitialize.registerComponent<CShape>();
	//cmInitialize.registerComponent<Collision>();
	cmInitialize.registerComponent<CLifeTime>();
	cmInitialize.registerComponent<CZIndex>();
}

Entity GetPlayerID()
{
	return playerID;
}