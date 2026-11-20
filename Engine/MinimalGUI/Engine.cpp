#include "Engine.h"
#include "Level.h"

using namespace CJ;

bool Engine::Initialize()
{
	m_level = new Level();
	m_level->Initialize();
	return true;
}

void Engine::Inputs(const std::vector<sf::Event>& _events)
{
	if (m_level)
		m_level->Inputs(_events);
}

void Engine::Update(const float _deltaTime)
{
	if (m_level)
		m_level->Update(_deltaTime);
}

void Engine::Render(sf::RenderTarget& _rt)
{
	if (m_level)
		m_level->Render(_rt);
}

const std::vector<Entity*>& Engine::GetEntities() const
{
	return m_level->GetEntities();
}
