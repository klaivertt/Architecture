#include "Entity.h"
#include "Component.h"

using namespace CJ;

Component* CJ::Entity::AddComponent(const char* _typeName)
{
	Component* newComponent = Component::S_Create(_typeName, *this);
	if (newComponent)
	{
		m_components.push_back(newComponent);
	}
	return newComponent;
}

json Entity::Serialize() const
{
	json entityJson = json::array();
	for (Component* component : m_components)
	{
		json componentJson = component->Serialize();
		componentJson["type"] = Component::S_GetTypeName(*component);
		entityJson.push_back(componentJson);
	}
	return entityJson;
}

void Entity::Deserialize(const json& _json)
{
	for (const json& componentJson : _json)
	{
		const std::string componentType = componentJson["type"];

		Component* component = AddComponent(componentType.c_str());

		if (component)
		{
			component->Deserialize(componentJson);
		}
	}
}