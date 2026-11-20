#include "Engine.h"
#include "Entity.h"
#include "Component.h"

using namespace CJ;

bool Engine::Initialize()
{
	for (size_t i = 0; i < 10; i++)
	{

		Entity* tree = new Entity();

		TransformComponent* treeTransform = new TransformComponent(sf::Vector2f(100.f + i * 100.f, 500.f));

		GraphicComponent::AnimParametter param =
			GraphicComponent::AnimParametter("tree_01.png", sf::Vector2i(8, 1), sf::Vector2i(0, 0), (1.f / 8.f) * 0.8f, 8);

		GraphicComponent* treeGraphic = new GraphicComponent(treeTransform->GetPos(), param);
		treeGraphic->AddAnimDelay((std::rand() % 100) / 100.f);
		tree->AddComponent(treeGraphic);
		tree->AddComponent(treeTransform);

		m_entities.push_back(tree);
	}

	Entity* player = new Entity();

	TransformComponent* playerTransform = new TransformComponent(sf::Vector2f(400.f, 500.f));

	GraphicComponent* playerGraphic = new GraphicComponent(playerTransform->GetPos());

	StateMachineComponent* playerStateMachine = new StateMachineComponent(*playerGraphic);
	GraphicComponent::AnimParametter param =
		GraphicComponent::AnimParametter("player_idle_01.png", sf::Vector2i(8, 1), sf::Vector2i(0, 0), (1.f / 8.f) * 0.8f, 8);

	playerStateMachine->AddAnim(param);
	param = GraphicComponent::AnimParametter("player_run_01.png", sf::Vector2i(6, 1), sf::Vector2i(0, 0), (1.f / 6.f) * 0.8f, 6);
	playerStateMachine->AddAnim(param);
	param = GraphicComponent::AnimParametter("player_attack_01.png", sf::Vector2i(4, 1), sf::Vector2i(0, 0), (1.f / 4.f) * 0.5f, 4, false);
	playerStateMachine->AddAnim(param);

	ControllerComponent* playerController = new ControllerComponent(playerTransform->GetPos());

	playerController->AddStateMachine(*playerStateMachine);

	player->AddComponent(playerTransform);
	player->AddComponent(playerGraphic);
	player->AddComponent(playerController);

	m_entities.push_back(player);


	Entity* mob = new Entity();

	TransformComponent* mobTransform = new TransformComponent(sf::Vector2f(400.f, 500.f));


	GraphicComponent* mobGraphic = new GraphicComponent(mobTransform->GetPos());
	StateMachineComponent* mobStateMachine = new StateMachineComponent(*mobGraphic);

	param = GraphicComponent::AnimParametter("mob_idle_01.png", sf::Vector2i(12, 1), sf::Vector2i(0, 0), (1.f / 12.f) * 0.8f, 12);
	mobStateMachine->AddAnim(param);
	param = GraphicComponent::AnimParametter("mob_run_01.png", sf::Vector2i(6, 1), sf::Vector2i(0, 0), (1.f / 6.f) * 0.8f, 6);
	mobStateMachine->AddAnim(param);



	PatrolComponent* mobPatrol = new PatrolComponent(mobTransform->GetPos());
	mobPatrol->AddStateMachine(*mobStateMachine);

	mob->AddComponent(mobTransform);
	mob->AddComponent(mobGraphic);
	mob->AddComponent(mobPatrol);

	m_entities.push_back(mob);

	return true;
}

void Engine::Inputs(const std::vector<sf::Event>& _events)
{
	for (Entity* entity : m_entities)
	{
		ControllerComponent* controller = entity->GetComponent<ControllerComponent>();
		if (controller)
		{
			controller->Inputs(_events);
		}
	}
}

void Engine::Update(const float _deltaTime)
{
	for (Entity* entity : m_entities)
	{
		GraphicComponent* gComponent = entity->GetComponent<GraphicComponent>();
		if (gComponent)
		{
			gComponent->Update(_deltaTime);
		}
	}

	for (Entity* entity : m_entities)
	{
		ControllerComponent* controller = entity->GetComponent<ControllerComponent>();
		if (controller)
		{
			controller->Update(_deltaTime);
		}
	}

	for (Entity* entity : m_entities)
	{
		PatrolComponent* patrol = entity->GetComponent<PatrolComponent>();
		if (patrol)
		{
			patrol->Update(_deltaTime);
		}
	}

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