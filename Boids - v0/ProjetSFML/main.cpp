#include "common.h"
#include "Flocking.h"
#include "WidgetManager.h"
#include "Widget.h"

constexpr const int WINDOW_WIDTH = 1920;
constexpr const int WINDOW_HEIGHT = 1080;

constexpr const int NUM_BOIDS = 1000;
constexpr const int MAX_BOIDS = 2000;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Boids Flocking Simulation");

    Flocking flocking(NUM_BOIDS, window.getSize());

    // Color palette for UI (palette for random widget fills)
    std::vector<sf::Color> colorPalette{
        sf::Color(200, 100, 100),
        sf::Color(100, 200, 150),
        sf::Color(120, 150, 240),
        sf::Color(220, 180, 80),
        sf::Color(160, 120, 200),
        sf::Color(100, 180, 220)
    };

    // Named palette for panel / outlines / text
    struct ColorPalette
    {
        sf::Color m_background;
        sf::Color m_panelFill;
        sf::Color m_panelOutline;
        sf::Color m_sliderOutline;
        sf::Color m_text;
    } palette{
        sf::Color(20, 20, 40),      // background
        sf::Color(30, 30, 60),      // panel fill
        sf::Color::White,           // panel outline / general outline
        sf::Color::White,           // slider outline
        sf::Color::White            // text
    };

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Load a font for widgets
    sf::Font font;
    font.loadFromFile("arial.ttf"); // ensure font file is available

    // Create UI
    Panel* uiPanel = new Panel("Controls", {10, 10}, palette.m_panelFill, palette.m_panelOutline);

    Button* restartBtn = new Button("Restart", {30, 20}, pickRandomFillColor(colorPalette), palette.m_panelOutline);
    Slider<int>* boidSlider = new Slider<int>("Boids", sf::Vector2f{200, 20}, pickRandomFillColor(colorPalette), palette.m_sliderOutline, 0, MAX_BOIDS, NUM_BOIDS);
    Slider<float>* speedSlider = new Slider<float>("Speed", sf::Vector2f{200, 20}, pickRandomFillColor(colorPalette), palette.m_sliderOutline, 0.1f, 3.f, 1.f);
    restartBtn->SetCallBack([&flocking]() {flocking.restart(); });
    speedSlider->SetCallBack([&flocking](float _speed) {flocking.setSimulationSpeed(_speed); });
    boidSlider->SetCallBack([&flocking](int _count) {flocking.setNumBoids(_count); });
    uiPanel->pushChild(*restartBtn);
    uiPanel->pushChild(*boidSlider);
    uiPanel->pushChild(*speedSlider);

    WidgetManager::s_create();
    WidgetManager::get()->pushWidget(*uiPanel);
    WidgetManager::get()->setup();

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            WidgetManager::get()->onMouseEvent(event);
        }

        // Update
        {
            float dt = clock.getElapsedTime().asSeconds();
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            clock.restart();

            flocking.update(dt);
            WidgetManager::get()->Update(sf::Vector2f(mousePos));
        }

        // Draw
        {
            window.clear(palette.m_background);
            flocking.draw(window);
            WidgetManager::get()->draw(window, font);
            window.display();
        }
    }

    return 0;
}