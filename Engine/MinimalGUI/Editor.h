#pragma once
#include "common.h"

namespace CJ
{
	class Engine;
	class Entity;

	class Editor
	{
	public:
		Editor(Engine& _engine, const std::vector<Entity*>& _entities);
		bool Initialize();

		// TODO create an Editor class that mirrors the Engine class: 
		// it must have an "Initialize" function, as well as the functions 
		// "Inputs()", "Update()" and the "Render()".
		void Inputs(const std::vector<sf::Event>& _events);
		void Update(const float _deltaTime);
		void Render(sf::RenderTarget& _rt);
	private:
		const std::vector<Entity*>& m_entities;
		sf::Text m_text;
		Engine& m_engine;
	};
}


