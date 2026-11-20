#include "Level.h"
#include "Entity.h"
#include "Component.h"

using namespace CJ;

Level::Level()
{
}

void Level::Initialize()
{
	//for (size_t i = 0; i < 10; i++)
	//{

	//	Entity* tree = new Entity();


	//	GraphicComponent::AnimParametter param =
	//		GraphicComponent::AnimParametter("tree_01.png", sf::Vector2i(8, 1), sf::Vector2i(0, 0), (1.f / 8.f) * 0.8f, 8);

	//	GraphicComponent* treeGraphic = new GraphicComponent(*tree);
	//	treeGraphic->Initialize();
	//	treeGraphic->SetAnim(param);
	//	treeGraphic->AddAnimDelay((std::rand() % 100) / 100.f);
	//	tree->AddComponent(treeGraphic);

	//	m_entities.push_back(tree);
	//}

	//// player init
	//Entity* player = new Entity();

	//GraphicComponent* playerGraphic = new GraphicComponent(*player);
	//playerGraphic->Initialize();

	//StateMachineComponent* playerStateMachine = new StateMachineComponent(*player);
	//GraphicComponent::AnimParametter param =
	//	GraphicComponent::AnimParametter("player_idle_01.png", sf::Vector2i(8, 1), sf::Vector2i(0, 0), (1.f / 8.f) * 0.8f, 8);

	//playerStateMachine->AddAnim(param);
	//param = GraphicComponent::AnimParametter("player_run_01.png", sf::Vector2i(6, 1), sf::Vector2i(0, 0), (1.f / 6.f) * 0.8f, 6);
	//playerStateMachine->AddAnim(param);
	//param = GraphicComponent::AnimParametter("player_attack_01.png", sf::Vector2i(4, 1), sf::Vector2i(0, 0), (1.f / 4.f) * 0.5f, 4, false);
	//playerStateMachine->AddAnim(param);

	//ControllerComponent* playerController = new ControllerComponent(*player);
	//playerController->Initialized();

	//player->AddComponent(playerGraphic);
	//player->AddComponent(playerController);
	//player->AddComponent(playerStateMachine);

	//m_entities.push_back(player);

	//// Mob init
	//Entity* mob = new Entity();

	//GraphicComponent* mobGraphic = new GraphicComponent(*mob);
	//mobGraphic->Initialize();
	//StateMachineComponent* mobStateMachine = new StateMachineComponent(*mob);

	//param = GraphicComponent::AnimParametter("mob_idle_01.png", sf::Vector2i(12, 1), sf::Vector2i(0, 0), (1.f / 12.f) * 0.8f, 12);
	//mobStateMachine->AddAnim(param);
	//param = GraphicComponent::AnimParametter("mob_run_01.png", sf::Vector2i(6, 1), sf::Vector2i(0, 0), (1.f / 6.f) * 0.8f, 6);
	//mobStateMachine->AddAnim(param);


	//PatrolComponent* mobPatrol = new PatrolComponent(*mob);
	//mobPatrol->Initialize();

	//mob->AddComponent(mobGraphic);
	//mob->AddComponent(mobStateMachine);
	//mob->AddComponent(mobPatrol);

	//m_entities.push_back(mob);

}

void Level::Inputs(const std::vector<sf::Event>& _events)
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

void Level::Update(const float _deltaTime)
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

void Level::Render(sf::RenderTarget& _rt)
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

void Level::SaveToFile()
{
	json levelJson = Serialize();
	std::ofstream file(m_fileName);
	if (file.is_open())
	{
		file << levelJson.dump(4);
		file.close();
	}
}

void Level::LoadFromFile(const char* _fileName)
{
	m_fileName = _fileName;
	std::ifstream file(_fileName);
	if (file.is_open())
	{
		json levelJson;
		file >> levelJson;
		Deserialize(levelJson);
		file.close();
	}
}

json Level::Serialize() const
{
	json entitiesArray = json::array();

	for (Entity* entity : m_entities)
	{
		entitiesArray.push_back(entity->Serialize());
	}

	return entitiesArray;
}

void Level::Deserialize(const json& _json)
{
	m_entities.clear();

	for (const json& entityJson : _json)
	{
		Entity* entity = new Entity();
		entity->Deserialize(entityJson);
		m_entities.push_back(entity);
	}
}
