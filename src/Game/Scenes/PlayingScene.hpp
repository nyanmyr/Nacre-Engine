#ifndef PLAYING_SCENE_HPP
#define PLAYING_SCENE_HPP

string PLAYER_SPRITE_PATH = RESOURCES_PATH "Rayfighter.png";
string ENEMY_1_SPRITE_PATH = RESOURCES_PATH "EnemyCyan.png";
string ENEMY_2_SPRITE_PATH = RESOURCES_PATH "EnemyYellow.png";

void PlayingScene(RenderWindow& window) {

	// entity instantiation
	Entity player = em.createEntity();
	Texture playerTexture;
	playerTexture.loadFromFile(PLAYER_SPRITE_PATH);

	Sprite playerSprite;
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(.08f, .08f);
	//cout << playerSprite.getGlobalBounds().width << "\n";
	//cout << (512 * 0.08) << "\n";

	Rect<float> playerBounds = playerSprite.getGlobalBounds();
	int playerWidth = playerBounds.width;
	int playerHeight = playerBounds.height;
	playerSprite.setOrigin(
		playerTexture.getSize().x / 2,
		playerTexture.getSize().y / 2
	);

	cm.addComponent(
		player,
		CSprite{
			playerTexture,
			playerSprite
		}
	);
	cm.addComponent(
		player,
		CPosition{
		(float)window.getSize().x / 2,
		(float)window.getSize().y / 2
		}
	);
	cm.addComponent(
		player,
		CMouseAim{
		playerSprite.getRotation()
		}
	);
	cm.addComponent(
		player,
		CVelocity{
			0,
			0
		}
	);

	Clock clock;

	while (window.isOpen())
	{
		DeltaTime dt = clock.restart().asSeconds();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		// systems
		PlayerAim(Mouse::getPosition(window));

		PlayerInputSystem(player);

		MovementSystem(dt);

		window.clear();
		// render systems
		RenderSprites(window);
		window.display();
	}
}

#endif