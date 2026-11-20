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


		const std::string& getFileName() const { return m_fileName; }
		void SetFileName(const char* _fileName) { m_fileName = _fileName; }

		void SaveToFile();
		void LoadFromFile(const char* _fileName);

		json Serialize() const;
		void Deserialize(const json& _json);

		const std::vector<Entity*>& GetEntities() const { return m_entities; }
		std::vector<Entity*>& GetEntities() { return m_entities; }
	private:
		std::string m_fileName;
		std::vector<Entity*> m_entities;
	};
}