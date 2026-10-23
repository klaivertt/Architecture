#include "common.h"
#include "Simulation.h"
#include "Shape.h"
#include "Widget.h"
#include "WidgetManager.h"

const int WINDOW_WIDTH = 1240;
const int WINDOW_HEIGHT = 720;


//---------------------------------------------------------------------------------
inline sf::Color pickRandomFillColor(const std::vector<sf::Color>& _palette)
{
    if (_palette.empty())
        return sf::Color::White;
    int idx = std::rand() % (int)_palette.size();
    return _palette[idx];
}

int main() 
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Simulation");
	window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return -1;

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    bool simulationPaused = false;
    float simulationSpeed = 1.f;
    unsigned int simulationFoodQuantity = 100;

    Simulation simulation;
    simulation.setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    Panel* uiPanel = new Panel("Controls", { 10, 10 });
    Slider<float>* simulationSpeedSlider = new Slider<float>("Simulation Speed", {200, 20}, 
                                                        0.1f, 5.f, 
                                                        [&]() -> float { return simulationSpeed; }, 
		                                                [&](float _value) { simulationSpeed = _value; });
    uiPanel->pushChild(*simulationSpeedSlider);

    Slider<unsigned>* agentMaxCount = new Slider<unsigned>("Agents Max Count", {200, 20}, 
                                                        10, 2000, 
                                                        [&]() -> unsigned { return (unsigned)simulation.getAgentsMaxCount(); }, 
		                                                [&](unsigned _value) { simulation.setAgentsMaxCount((size_t)_value); });

	uiPanel->pushChild(*agentMaxCount);

    Slider<unsigned>* randomWiddlgeStrength = new Slider<unsigned>("Random Wiggle Strength", {200, 20}, 
                                                        0, 30, 
                                                        [&]() -> unsigned { return simulation.getRandomWiggleStrength(); }, 
                                                        [&](unsigned _value){ simulation.setRandomWiggleStrength(_value); } );
	uiPanel->pushChild(*randomWiddlgeStrength);

    Label* label = new Label("Food Count : ", [&](){});

    uiPanel->pushChild(*label);

    WidgetManager::s_create();
    WidgetManager::get()->pushWidget(*uiPanel);
    WidgetManager::get()->setup();

    sf::Clock clock;
    while (window.isOpen()) 
    {
        // Events
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
                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    window.setView(sf::View(visibleArea));
                    simulation.setWindowSize(event.size.width, event.size.height);
                }
                break;
                }

                const bool isGUIEvent = WidgetManager::get()->onEvent(event, window);
                if (!isGUIEvent)
                {
                    if (event.type == sf::Event::MouseMoved &&
                        sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        const sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
                        simulation.trySpawnFoodSpot(mousePosition);
                    }
                }
            }
        }

        // Update
        {
            const float dt = clock.restart().asSeconds() * simulationSpeed;
			if (!simulationPaused)
                simulation.update(dt);
        }

        // Draw
        {
            window.clear(sf::Color::Black);
            simulation.draw(window);
			WidgetManager::get()->draw(window, font);
            window.display();
        }
    }

    return 0;
}
