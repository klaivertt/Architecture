#include "Engine.h"
#include "Entity.h"

using namespace CJ;

bool Engine::Initialize()
{
	m_entities.push_back(new Entity("tree_01.png", sf::IntRect(0, 0, 192, 256), sf::Vector2f(500.f, 500.f)));

	// TODO create 1 "Player" entity and 2 "Mob" entities.
	// Use "player_idle_01.png" (you can find it in CreajeuxEngine/WorkingDirectory) for graphics.

	return true;
}

void Engine::Inputs(const std::vector<sf::Event>& _events)
{
	// TODO entities process inputs
}

void Engine::Update(const float _deltaTime)
{
	// TODO update entities
}

void Engine::Render(sf::RenderTarget& _rt)
{
	// TODO render entities
}