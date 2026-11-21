#pragma once
#include "common.h"

namespace CJ
{
	class Entity;
	class Player;
	class Level;

	class Engine
	{
	public:
		bool Initialize();

		void Inputs(const std::vector<sf::Event>& _events);
		void Update(const float _deltaTime);
		void Render(sf::RenderTarget& _rt);

		const std::vector<Entity*>& GetEntities() const;
		const Level* ConstGetLevel() const { return m_level; }
		Level* GetLevel() const { return m_level; }
	private:
		Level* m_level{nullptr};
	};
}