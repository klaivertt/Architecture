#pragma once
#include "common.h"

namespace CJ
{
	class Entity
	{
	public:
		Entity(const char* _textureFile, const sf::IntRect& _area, const sf::Vector2f& _position);
		virtual ~Entity() = default;

		virtual void Inputs(const std::vector<sf::Event>& _events) {}
		virtual void Update(const float _deltaTime);
		virtual void Render(sf::RenderTarget& _rt);

		const sf::Sprite& GetSprite() const { return m_sprite; }
		sf::Sprite& GetSprite()				{ return m_sprite; }

		const sf::Vector2f& GetVelocity() const			{ return m_velocity; }
		void SetVelocity(const sf::Vector2f& _velocity) { m_velocity = _velocity; }

	private:
		sf::Texture m_texture;
		sf::Sprite m_sprite;
		sf::Vector2f m_velocity{ 0.f, 0.f };
	};

	// TODO create a "Player" and a "Mob" class. 
	// 
	// They both inherit from "Entity", and they need to override 
	// some functions in order to work as intented.
}