#include "Editor.h"
#include "Engine.h"
#include "Entity.h"
#include "AssetsManager.h"
#include "Component.h"
#include "Level.h"

using namespace CJ;

// TODO implement Editor's functions here

Editor::Editor(Engine& _engine, bool& _enginePause) : m_engine(_engine), m_enginePause(_enginePause)
{
}

bool Editor::Initialize(const std::vector<Entity*>& _entities)
{
	sf::Font* font = AssetManager::get()->GetFont();
	m_entities = &_entities;

	if (!font)
	{
		return false;
	}

	m_text.setFont(*font);
	m_text.setString("Editor Mode");
	m_text.setFillColor(sf::Color::White);

	m_pauseText.setFont(*font);
	m_pauseText.setString("Engine Pause");
	m_pauseText.setFillColor(sf::Color::White);

	sf::Vector2f pauseTextPos = sf::Vector2f(m_text.getGlobalBounds().width + 30.f, 0.f);
	m_pauseText.setPosition(pauseTextPos);
	return true;
}

void Editor::Inputs(const std::vector<sf::Event>& _events)
{
	for (const sf::Event& event : _events)
	{
		const bool isCtrlPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);

		if (event.key.code == sf::Keyboard::S && isCtrlPressed)
		{
			m_engine.GetLevel()->SaveToFile();
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
				GetEntityAtMousePos(mousePos);
			}
		}

		if (event.type == sf::Event::MouseButtonReleased)
		{
			m_currentEntity = nullptr;
		}

	}
}

void Editor::Update(const float _deltaTime, const sf::Vector2i& _mousePos)
{
	if (m_currentEntity)
	{
		GraphicComponent* gComponent = m_currentEntity->GetComponent<GraphicComponent>();
		if (gComponent)
		{
			sf::Sprite& sprite = gComponent->GetSprite();

			sprite.setPosition(sf::Vector2f(_mousePos) + m_currentEntityOffset);
		}
	}
}

void Editor::Render(sf::RenderTarget& _rt)
{
	for (Entity* entity : *m_entities)
	{
		GraphicComponent* gComponent = entity->GetComponent<GraphicComponent>();
		if (gComponent)
		{
			sf::Sprite& sprite = gComponent->GetSprite();
			sf::RectangleShape rect;


			sf::FloatRect bound = sprite.getGlobalBounds();
			rect.setPosition(sprite.getPosition());
			rect.setSize(sf::Vector2f(bound.width, bound.height));
			rect.setOutlineThickness(3.f);
			if (m_currentEntity && m_currentEntity == entity)
			{
				rect.setOutlineColor(sf::Color::Green);
			}
			else
			{
				rect.setOutlineColor(sf::Color::Yellow);
			}
			rect.setFillColor(sf::Color::Transparent);

			_rt.draw(rect);
		}
	}


	if (m_enginePause)
	{
		_rt.draw(m_pauseText);
	}

	_rt.draw(m_text);
}

void Editor::GetEntityAtMousePos(sf::Vector2f _pos)
{
	for (const Entity* entity : *m_entities)
	{
		GraphicComponent* gComponent = entity->GetComponent<GraphicComponent>();
		if (gComponent)
		{
			const sf::Sprite& sprite = gComponent->GetSprite();

			sf::FloatRect bounds = sprite.getGlobalBounds();

			if (bounds.contains(_pos) && !m_currentEntity)
			{
				m_currentEntity = entity;
				sf::Vector2f sPos = sprite.getPosition();
				m_currentEntityOffset = sPos - _pos;
				break;
			}
		}
	}
}
