#include "Editor.h"
#include "Engine.h"
#include "Entity.h"
#include "AssetsManager.h"
#include "Component.h"

using namespace CJ;

// TODO implement Editor's functions here

Editor::Editor(Engine& _engine, const std::vector<Entity*>& _entities) : m_engine(_engine), m_entities(_entities)
{
}

bool Editor::Initialize()
{
	sf::Font* font = AssetManager::get()->GetFont();

	if (!font)
	{
		return false;
	}

	m_text.setFont(*font);
	m_text.setString("Editor Mode");
	m_text.setFillColor(sf::Color::White);
	return true;
}

void Editor::Inputs(const std::vector<sf::Event>& _events)
{
}

void Editor::Update(const float _deltaTime)
{
}

void Editor::Render(sf::RenderTarget& _rt)
{
	for (Entity* entity : m_entities)
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
			rect.setOutlineColor(sf::Color::Yellow);
			rect.setFillColor(sf::Color::Transparent);

			_rt.draw(rect);
		}
	}

	_rt.draw(m_text);
}
