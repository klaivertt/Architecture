#include "Application.h"
#include "Editor.h"

using namespace CJ;

Application::~Application()
{
	if (m_window)
		delete m_window;
}

bool Application::Initialize(const char* _title, const sf::VideoMode& _mode, unsigned int _framerateLimite)
{
	m_window = new sf::RenderWindow(_mode, _title);
	m_window->setFramerateLimit(_framerateLimite);

    if (!m_engine.Initialize())
        return false;
    
    // TODO initialize the Editor here

	return true;
}

void Application::Run()
{
    while (m_window->isOpen())
    {
        // Events
        std::vector<sf::Event> inputs = ProcessEvents();

        // TODO
        // In the lines below, call the Editor's functions so that
        // everything works as intented.

        m_engine.Inputs(inputs);

        const float deltaTime = m_clock.restart().asSeconds();
        m_engine.Update(deltaTime);

        m_window->clear(sf::Color::Black);
        m_engine.Render(*m_window);
        m_window->display();
    }
}

std::vector<sf::Event> Application::ProcessEvents()
{
    std::vector<sf::Event> inputs;
    {
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window->close();
            }
            else if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                m_window->setView(sf::View(visibleArea));
            }
            else if (event.type == sf::Event::KeyPressed ||
                     event.type == sf::Event::KeyReleased ||
                     event.type == sf::Event::MouseButtonPressed ||
                     event.type == sf::Event::MouseButtonReleased ||
                     event.type == sf::Event::MouseMoved ||
                     event.type == sf::Event::MouseWheelMoved)
            {
                if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::F1 &&
                    m_editor)
                {
                    m_editorEnabled = !m_editorEnabled;
                }
                else
                {
                    inputs.push_back(event);
                }
            }
        }
    }

    return inputs;
}