#include "Engine.h"
#include "Entity.h"
#include "Component.h"

using namespace CJ;

bool Engine::Initialize()
{
	Entity* tree = new Entity();
	GraphicComponent* treeGraphic = new GraphicComponent("tree_01.png", sf::Vector2f(500.f, 500.f),sf::IntRect(0, 0, 192, 256));
	tree->AddComponent(treeGraphic);
	
	m_entities.push_back(tree);

	return true;
}

void Engine::Inputs(const std::vector<sf::Event>& _events)
{

}

void Engine::Update(const float _deltaTime)
{
	
}

void Engine::Render(sf::RenderTarget& _rt)
{
	for (Entity* entity : m_entities)
	{
		GraphicComponent* gComponent = entity->GetComponent<GraphicComponent>();
		if (gComponent)
		{
			gComponent->Render(_rt);
		}
	}
}