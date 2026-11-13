#include "Component.h"

using namespace CJ;

GraphicComponent::GraphicComponent(const char* _textureFile, const sf::Vector2f& _position, const sf::IntRect& _area)
{
	if (!m_texture.loadFromFile(_textureFile))
	{
		// Error
	}

	m_sprite.setPosition(_position);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(_area);
}

GraphicComponent::GraphicComponent(const char* _textureFile, const sf::Vector2f& _position, AnimParametter& _parametter)
{
	sf::IntRect rect = { 10,10,10,10 };
	GraphicComponent(_textureFile, _position, rect);

	sf::Vector2u textureSize = m_texture.getSize();

	sf::Vector2i divider = _parametter.frameDivider;

	m_frameSize = sf::Vector2i(textureSize.x / divider.x, textureSize.y / divider.y);
	m_startFrame = _parametter.frameDivider;
	m_nbFrame = _parametter.nbFrame;
}

void GraphicComponent::Inputs(const std::vector<sf::Event>& _events)
{
}

void GraphicComponent::Update(const float _deltaTime)
{
}

void GraphicComponent::Render(sf::RenderTarget& _rt)
{
	_rt.draw(m_sprite);
}
