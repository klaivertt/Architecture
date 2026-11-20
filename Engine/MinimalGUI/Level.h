#pragma once

#include "common.h"
namespace CJ
{
	class Entity;

	class Level
	{
	public:

		Level();
		void Initialize();

		const std::string& GetFileName() const { return m_fileName; }

		void Inputs(const std::vector<sf::Event>& _events);
		void Update(const float _deltaTime);
		void Render(sf::RenderTarget& _rt);

		void SaveToFile();
		void LoadFromFile(const char* _fileName);


		const std::vector<Entity*>& GetEntities() const { return m_entities; }
		std::vector<Entity*>& GetEntities() { return m_entities; }
	private:
		std::string m_fileName;
		std::vector<Entity*> m_entities;
	};
}