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

	/*class Player : public Entity
	{
	public:
		Player(const char* _textureFile, const sf::IntRect& _area, const sf::Vector2f& _position);

		virtual void Inputs(const std::vector<sf::Event>& _events);
		virtual void Update(const float _deltaTime);
	private:
		bool keyUp = false;
		bool keyDown = false;
		bool keyLeft = false;
		bool keyRight = false;
		float m_speed = 50.f;
	};

	class Mob : public Entity
	{
	public:
		Mob(const char* _textureFile, const sf::IntRect& _area, const sf::Vector2f& _position);

		virtual void Update(const float _deltaTime);
	private:
		enum Dir
		{
			UP,
			DOWN,
			LEFT,
			RIGHT,
			ALL_DIR
		};

		enum State
		{
			IDLE,
			PATROl,
			ALL_STATE
		};

		Dir m_lastDir1 = UP;
		Dir m_lastDir2 = UP;
		float m_timer = 0.f;
		const float m_changeDir = 4.f;
		const float m_speed = 50.f;
		State m_state = IDLE;

		sf::Vector2f m_dir = { 0.f,0.f };

		sf::Vector2f GetDir(Dir& _dir1, Dir& _dir2);
	};*/
}