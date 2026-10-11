#include "common.h"
#include "GameData.h"
#include "Load.h"
#include "Update.h"
#include "Draw.h";
#include "WidgetsOwner.h"

//---------------------------------------------------------------------------------
int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_S.x, SCREEN_S.y), "MinimalGUI");

	GameData data = GameData();

	if (Load(data) == -1)
	{
		return -1;
	}

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				window.close();
			}
			break;
			case sf::Event::Resized:
			{
				sf::FloatRect viewBounds(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(viewBounds));
			}
			break;
			case sf::Event::MouseButtonPressed:
			{
				// Todo handle mouse pressed
				if (event.mouseButton.button == sf::Mouse::Button::Left)
				{
					WidgetsOwner::get()->Pressed(data.mousePos);
				}
			}
			break;
			case sf::Event::MouseButtonReleased:
			{
				WidgetsOwner::get()->Released();
			}
			break;
			}
		}
		data.mousePos = sf::Mouse::getPosition(window);
		float deltaTime = clock.restart().asSeconds();
		Update(deltaTime, data);

		window.clear(sf::Color::Black);

		Draw(window, data);

		window.display();
	}

	WidgetsOwner::get()->Clear();

	return 0;
}
