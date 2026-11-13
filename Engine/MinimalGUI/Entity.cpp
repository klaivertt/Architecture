#include "Entity.h"

using namespace CJ;

Entity::Entity(const char* _textureFile, const sf::IntRect& _area, const sf::Vector2f& _position)
{
	if (!m_texture.loadFromFile(_textureFile))
	{
		// Error
	}

	m_sprite.setPosition(_position);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(_area);
}

void Entity::Update(float _deltaTime)
{
	m_sprite.setPosition(m_sprite.getPosition() + m_velocity * _deltaTime);
}

void Entity::Render(sf::RenderTarget& _rt)
{
	_rt.draw(m_sprite);
}