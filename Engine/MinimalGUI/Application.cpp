#include "Application.h"
#include "Editor.h"
#include "AssetsManager.h"

using namespace CJ;

Application::~Application()
{
	if (m_window)
	{
		delete m_window;
	}
}

bool Application::Initialize(const char* _title, const sf::VideoMode& _mode, unsigned int _framerateLimite)
{
	m_window = new sf::RenderWindow(_mode, _title);
	m_window->setFramerateLimit(_framerateLimite);
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	AssetManager::s_create();

	m_editor = std::make_unique<Editor>(m_engine, m_engine.GetEntities(), m_pause);

	if (!m_engine.Initialize())
	{
		return false;
	}

	if (!m_editor->Initialize())
	{
		return false;
	}

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

		if(!m_pause)
		{
			m_engine.Inputs(inputs);
		}
		
		if (m_editor && m_editorEnabled)
		{
			m_editor->Inputs(inputs);
		}

		const float deltaTime = m_clock.restart().asSeconds();
		if (!m_pause)
		{
			m_engine.Update(deltaTime);
		}

		if (m_editor && m_editorEnabled)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
			m_editor->Update(deltaTime, mousePos);
		}

		m_window->clear(sf::Color::Black);
		m_engine.Render(*m_window);
		
		if (m_editor && m_editorEnabled)
		{
			m_editor->Render(*m_window);
		}

		m_window->display();

		inputs.clear();
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
					m_pause = m_editorEnabled;
				}
				if (event.type == sf::Event::KeyPressed &&
					event.key.code == sf::Keyboard::Space &&
					m_editor)
				{
					m_pause = !m_pause;
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