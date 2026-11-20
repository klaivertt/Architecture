#pragma once

#include "common.h"

namespace CJ
{
	class StateMachineComponent;
	class Entity;

	class Component
	{
	protected:
		Entity& m_entity;
	public:
		Component(Entity& _entity) : m_entity(_entity) {}
		virtual void Inputs(const std::vector<sf::Event>& _events) {}
		virtual void Update(const float _deltaTime) {}
		virtual void Render(sf::RenderTarget& _rt) {}
		virtual const char* GetName() = 0;

		virtual json Serialize() const { return {}; }
		virtual void Deserialize(const json& _json) {}

		static const char* S_GetTypeName(Component& _component);
		static Component* S_Create(const char* _typeName, Entity& _entity);
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

			AnimParametter()
			{

			}

			virtual json Serialize() const
			{

				json cJson;

				cJson["TextureFiles"] = path;
				cJson["FrameCount"] = nbFrame;
				cJson["FrameDivider"]["w"] = frameDivider.x;
				cJson["FrameDivider"]["h"] = frameDivider.y;


				cJson["StartFrame"]["w"] = startFrame.x;
				cJson["StartFrame"]["h"] = startFrame.y;

				return cJson;
			}
			virtual void Deserialize(const json& _json)
			{
				path = _json["TextureFiles"];

				nbFrame = _json["frameCount"];

				frameDivider = { _json["FrameDivider"]["w"], _json["FrameDivider"]["h"] };
				startFrame = { _json["StartFrame"]["w"], _json["StartFrame"]["h"] };
			}

			sf::Vector2i frameDivider = sf::Vector2i(0, 0);
			sf::Vector2i startFrame = sf::Vector2i(0, 0);
			unsigned int nbFrame = 0;
			float frameTime = 0.f;
			std::string path = "";
			bool isLoop = true;
		};

		GraphicComponent(Entity& _entity) : Component(_entity) {}

		virtual void Initialize();
		virtual ~GraphicComponent() = default;

		virtual void Inputs(const std::vector<sf::Event>& _events) override;
		virtual void Update(const float _deltaTime)override;
		virtual void Render(sf::RenderTarget& _rt)override;

		void SetAnim(AnimParametter& _anim);
		void AddAnimDelay(float _delay) { m_animationTimer -= _delay; }

		virtual json Serialize() const;
		virtual void Deserialize(const json& _json);

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

		AnimParametter m_anim;

		sf::Vector2i m_frameSize = sf::Vector2i(0, 0);
		unsigned int m_currentFrame = 0;
		bool m_isFinished = true;
	};

	class ControllerComponent : public Component
	{
	public:
		ControllerComponent(Entity& _entity) : Component(_entity) {}

		void Initialized();
		
		virtual void Inputs(const std::vector<sf::Event>& _events);
		virtual void Update(const float _deltaTime);
		virtual const char* GetName() { return "ControllerComponent"; }

	private:
		float m_speed = 50.f;
		sf::Vector2f m_velocity{0.f,0.f};

		enum State
		{
			IDLE,
			MOVE,
			ATTACK,
			ALL_STATE
		};
		State m_state;
		bool m_isAttack = false;
	};

	//class TransformComponent : public Component
	//{
	//public:
	//	TransformComponent();
	//	void Initialize(sf::Vector2f _startPos = sf::Vector2f(0.f, 0.f));

	//	sf::Vector2f& GetPos() { return m_pos; }
	//	void SetPos(const sf::Vector2f& _pos) { m_pos = _pos; }

	//	virtual const char* GetName() { return "TransformComponent"; }
	//private:
	//	sf::Vector2f m_pos{ 0.f,0.f };
	//};
	
	class PatrolComponent : public Component
	{
	public:
		PatrolComponent(Entity& _entity) : Component(_entity) {}
		void Initialize();
		virtual void Update(const float _deltaTime);

		//virtual json Serialize() const;
		//virtual void Deserialize(const json& _json);

		virtual const char* GetName() { return "PatrolComponent"; }
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
		sf::Vector2f m_velocity{ 0.f,0.f };

		sf::Vector2f GetDir(Dir& _dir1, Dir& _dir2);

		StateMachineComponent* m_stateMachine{ nullptr };
	};

	class StateMachineComponent : public Component
	{
	public:
		StateMachineComponent(Entity& _entity) : Component(_entity) {}
		// Add anim in the right order
		void AddAnim(GraphicComponent::AnimParametter& _anim)
		{
			m_animByState.push_back(_anim);
			m_totalState = m_animByState.size();
		}

		void changeState(unsigned int const _state);

		bool CanChangeState();
		
		virtual json Serialize() const;
		virtual void Deserialize(const json& _json);


		virtual const char* GetName() { return "StateMachineComponent"; }
	
	private:
		std::vector<GraphicComponent::AnimParametter> m_animByState;
		int m_currentState = 0;
		int m_totalState = 0;
	};
}

