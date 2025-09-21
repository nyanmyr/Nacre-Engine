#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP

void MenuScene(RenderWindow& window) {

	// entity instantiation
	Entity playButton = em.createEntity();
	cm.addComponent(
		playButton,
		CPosition{
		((float)window.getSize().x / 2) - 50, ((float)window.getSize().y / 2) - 25
		}
	);
	cm.addComponent(
		playButton,
		CShape{
		RectangleShape(Vector2f(100.f, 50.f))
		}
	);
	cm.addComponent(
		playButton,
		CButton{
		MouseEvent::START_GAME
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

			if (event.type == Event::MouseButtonPressed)
			{
				MouseEvent mouseEvent = MouseEvent::NOTHING;

				if (event.mouseButton.button == Mouse::Left)
				{
					mouseEvent = MouseClickSystem(
						Vector2f(event.mouseButton.x, event.mouseButton.y)
					);
				}
				else
				{
					break;
				}

				switch (mouseEvent)
				{
				case NOTHING:
				default:
					break;
				case START_GAME:
					// on exit
					cm.entityDestroyed(playButton);
					em.destroyEntity(playButton);

					playScene(window, PLAYING);
					window.close();
					// cout << "test" << "\n";
					break;
				}
			}

			//if (event.type == Event::KeyReleased)
			//{
			//	if (event.key.code == Keyboard::Space)
			//	{
			//		// on exit
			//		cm.entityDestroyed(player);
			//		em.destroyEntity(player);

			//		playScene(window, PLAYING);
			//		window.close();
			//	}
			//}
		}

		// systems

		window.clear();
		// render systems
		RenderSystem(window);
		window.display();
	}
}

#endif