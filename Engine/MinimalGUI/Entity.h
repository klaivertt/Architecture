#pragma once
#include "common.h"
namespace CJ
{
	class Component;

	class Entity
	{
	public:
		Entity() {}

		void AddComponent(Component* _component)
		{
			if (_component)
			{
				m_components.push_back(_component);
			}
		}

		template<typename T>
		T* GetComponent() const
		{
			for (Component* component : m_components)
			{
				if (T* typeComponent = dynamic_cast<T*>(component))
				{
					return typeComponent;
				}
			}

			return nullptr;
		}

	private:
		std::vector<Component*> m_components;
	};

}