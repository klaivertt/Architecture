#pragma once
#include "common.h"

namespace CJ
{
	class Engine;
	class Entity;

	class Editor
	{
	public:
		Editor(Engine& _engine, const std::vector<Entity*>& _entities, bool& m_enginePause);
		bool Initialize();

		// TODO create an Editor class that mirrors the Engine class: 
		// it must have an "Initialize" function, as well as the functions 
		// "Inputs()", "Update()" and the "Render()".
		void Inputs(const std::vector<sf::Event>& _events);
		void Update(const float _deltaTime, const sf::Vector2i& _mousePos);
		void Render(sf::RenderTarget& _rt);
	private:
		const std::vector<Entity*>& m_entities;
		sf::Text m_text;
		sf::Text m_pauseText;
		Engine& m_engine;
		bool& m_enginePause;

		const Entity* m_currentEntity{ nullptr };
		sf::Vector2f m_currentEntityOffset{ 0.f,0.f };

		void GetEntityAtMousePos(sf::Vector2f _pos);
	};
}


