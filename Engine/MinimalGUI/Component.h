#pragma once

#include "common.h"

namespace CJ
{
	class StateMachineComponent;

	class Component
	{
	public:
		virtual void Inputs(const std::vector<sf::Event>& _events) {}
		virtual void Update(const float _deltaTime) {}
		virtual void Render(sf::RenderTarget& _rt) {}
		virtual const char* GetName() = 0;
	};


	class GraphicComponent : public Component
	{
	public:
		struct AnimParametter
		{
			AnimParametter(const char* _path, sf::Vector2i _frameDivider, sf::Vector2i _startFrame, float _frameTime, unsigned int _nbFrame, bool _isLoop = true)
			{
				path = _path;
				frameDivider = _frameDivider;
				startFrame = _startFrame;
				frameTime = _frameTime;
				nbFrame = _nbFrame;
				isLoop = _isLoop;
			}

			sf::Vector2i frameDivider = sf::Vector2i(0, 0);
			sf::Vector2i startFrame = sf::Vector2i(0, 0);
			unsigned int nbFrame = 0;
			float frameTime = 0.f;
			std::string path = "";
			bool isLoop = true;
		};

		GraphicComponent(const char* _textureFile, sf::Vector2f& _position, const sf::IntRect& _area);
		GraphicComponent(sf::Vector2f& _position, AnimParametter& _parametter);
		GraphicComponent(sf::Vector2f& _position);
		virtual ~GraphicComponent() = default;

		virtual void Inputs(const std::vector<sf::Event>& _events) override;
		virtual void Update(const float _deltaTime)override;
		virtual void Render(sf::RenderTarget& _rt)override;

		void SetAnim(AnimParametter& _anim);
		void AddAnimDelay(float _delay) { m_animationTimer -= _delay; }

		sf::Sprite& GetSprite(void)
		{
			return m_sprite;
		}

		bool GetIsFinished() const
		{
			return m_isFinished;
			//return true;
		}

		virtual const char* GetName() override { return "GraphicComponent"; }

	private:
		sf::Texture m_texture;
		sf::Sprite m_sprite;
		float m_animationTimer = 0.f;
		float m_frameTime = 0.f;
		sf::Vector2i m_frameSize = sf::Vector2i(0, 0);
		sf::Vector2i m_startFrame = sf::Vector2i(0, 0);
		unsigned int m_nbFrame = 0;
		unsigned int m_currentFrame = 0;
		bool m_isLoop = false;
		sf::Vector2f& m_pos;
		bool m_isFinished = true;
	};

	class ControllerComponent : public Component
	{
	public:
		ControllerComponent(sf::Vector2f& _position): m_pos(_position){}

		virtual void Inputs(const std::vector<sf::Event>& _events);
		virtual void Update(const float _deltaTime);
		virtual const char* GetName() { return "ControllerComponent"; }

		void AddStateMachine(StateMachineComponent& _state)
		{
			m_stateMachine = &_state;
		}

	private:
		float m_speed = 50.f;
		sf::Vector2f& m_pos;
		sf::Vector2f m_velocity{0.f,0.f};

		enum State
		{
			IDLE,
			MOVE,
			ATTACK,
			ALL_STATE
		};
		State m_state;
		StateMachineComponent* m_stateMachine{nullptr};
		bool m_isAttack = false;
	};

	class TransformComponent : public Component
	{
	public:
		TransformComponent(sf::Vector2f _startPos = sf::Vector2f(0.f, 0.f));

		sf::Vector2f& GetPos() { return m_pos; }
		void SetPos(const sf::Vector2f& _pos) { m_pos = _pos; }

		virtual const char* GetName() { return "TransformComponent"; }
	private:
		sf::Vector2f m_pos{ 0.f,0.f };
	};
	
	class PatrolComponent : public Component
	{
	public:
		PatrolComponent(sf::Vector2f& _pos) : m_pos(_pos) {}

		virtual void Update(const float _deltaTime);

		virtual const char* GetName() { return "PatrolComponent"; }

		void AddStateMachine(StateMachineComponent& _state)
		{
			m_stateMachine = &_state;
		}
	private:
		sf::Vector2f& m_pos;

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
		sf::Vector2f m_velocity{ 0.f,0.f };

		sf::Vector2f GetDir(Dir& _dir1, Dir& _dir2);

		StateMachineComponent* m_stateMachine{ nullptr };
	};

	class StateMachineComponent : public Component
	{
	public:
		StateMachineComponent(GraphicComponent& _component) : gComponent(_component) {}
		// Add anim in the right order
		void AddAnim(GraphicComponent::AnimParametter& _anim)
		{
			animByState.push_back(_anim);
		}

		void changeState(unsigned int const _state)
		{

			if(_state < animByState.size())
			{
				GraphicComponent::AnimParametter& anim = animByState[_state];
				gComponent.SetAnim(anim);
				std::cout << "spam change state" << std::endl;
			}
		}

		
		bool CanChangeState()
		{
			return gComponent.GetIsFinished();
		}

		virtual const char* GetName() { return "StateMachineComponent"; }
	
	private:
		std::vector<GraphicComponent::AnimParametter> animByState;
		GraphicComponent& gComponent;
	};
}

