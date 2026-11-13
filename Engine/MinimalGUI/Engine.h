#pragma once
#include "common.h"

namespace CJ
{
	class Entity;
	class Player;

	class Engine
	{
	public:
		bool Initialize();

		void Inputs(const std::vector<sf::Event>& _events);
		void Update(const float _deltaTime);
		void Render(sf::RenderTarget& _rt);

		const std::vector<Entity*>& GetEntities() const { return m_entities; }

	private:
		std::vector<Entity*> m_entities;
	};
}