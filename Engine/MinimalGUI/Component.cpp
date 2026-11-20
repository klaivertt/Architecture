#include "Component.h"
#include "Entity.h"

using namespace CJ;

void GraphicComponent::Initialize()
{
	if (!m_texture.loadFromFile(m_anim.path))
	{
		return;
	}

	m_sprite.setTexture(m_texture);
	//m_sprite.setPosition(_position);

	sf::Vector2u textureSize = m_texture.getSize();

	sf::Vector2i divider = m_anim.frameDivider;

	m_frameSize = sf::Vector2i(textureSize.x / divider.x, textureSize.y / divider.y);

	sf::IntRect rect = sf::IntRect(m_anim.startFrame.x + (m_frameSize.x * m_currentFrame), m_anim.startFrame.y, m_frameSize.x, m_frameSize.y);

	m_sprite.setTextureRect(rect);

}

void GraphicComponent::Inputs(const std::vector<sf::Event>& _events)
{
}

void GraphicComponent::Update(const float _deltaTime)
{
	if (m_anim.nbFrame > 0)
	{

		m_animationTimer += _deltaTime;

		if (m_animationTimer > m_anim.frameTime)
		{
			m_animationTimer -= m_anim.frameTime;
			if (m_anim.isLoop)
			{
				m_isFinished = true;
				m_currentFrame = (m_currentFrame + 1) % m_anim.nbFrame;
			}
			else if (m_currentFrame < m_anim.nbFrame - 1)
			{
				m_currentFrame++;
				m_isFinished = false;
			}
			else
			{
				m_isFinished = true;
			}

			sf::IntRect rect = sf::IntRect(m_anim.startFrame.x + (m_frameSize.x * m_currentFrame), m_anim.startFrame.y, m_frameSize.x, m_frameSize.y);

			m_sprite.setTextureRect(rect);
		}
	}
}

void GraphicComponent::Render(sf::RenderTarget& _rt)
{
	//if (m_pos)
	//{
	//	m_sprite.setPosition(*m_pos);
	//}
	_rt.draw(m_sprite);
}

void GraphicComponent::SetAnim(AnimParametter& _anim)
{
	if (!m_texture.loadFromFile(_anim.path))
	{
		return;
	}

	sf::Vector2u textureSize = m_texture.getSize();

	sf::Vector2i divider = _anim.frameDivider;

	m_frameSize = sf::Vector2i(textureSize.x / divider.x, textureSize.y / divider.y);

	m_anim.startFrame = _anim.startFrame;
	m_anim.frameTime = _anim.frameTime;
	m_anim.nbFrame = _anim.nbFrame;
	m_anim.isLoop = _anim.isLoop;
	m_currentFrame = 0;
	m_animationTimer = 0.f;
	m_isFinished = false;

	sf::IntRect rect = sf::IntRect(m_anim.startFrame.x + (m_frameSize.x * m_currentFrame), m_anim.startFrame.y, m_frameSize.x, m_frameSize.y);

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(rect);
}

json GraphicComponent::Serialize() const
{
	json cJson;
	cJson["position"]["x"] = m_sprite.getPosition().x;
	cJson["position"]["y"] = m_sprite.getPosition().y;

	cJson.update(m_anim.Serialize());
	return cJson;
}

void GraphicComponent::Deserialize(const json& _json)
{
	const sf::Vector2f position = { _json["position"]["x"], _json["position"]["y"] };
	m_sprite.setPosition(position);

	m_anim.Deserialize(_json);

	Initialize();
}

void ControllerComponent::Initialized()
{
}

void ControllerComponent::Inputs(const std::vector<sf::Event>& _events)
{
	for (const sf::Event& event : _events)
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			StateMachineComponent* stateComponent = m_entity.GetComponent<StateMachineComponent>();
			if (stateComponent)
			{
				if (!m_isAttack)
				{
					m_state = ATTACK;
					stateComponent->changeState(ATTACK);
					m_isAttack = true;
				}
			}
		}
	}
}

void ControllerComponent::Update(const float _deltaTime)
{
	sf::Vector2f dir = sf::Vector2f(0.f, 0.f);
	if (!m_isAttack)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			dir.y = -1.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			dir.y = 1.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			dir.x = -1.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			dir.x = 1.f;
		}
		float normal = std::sqrt(dir.x * dir.x + dir.y * dir.y);
		normal = normal != 0.f ? normal : 1;
		dir = sf::Vector2f(dir.x / normal, dir.y / normal);
		m_velocity += dir * m_speed;

		m_velocity *= 0.85f;

		bool still = std::abs(m_velocity.x) < 0.1f && std::abs(m_velocity.y) < 0.1f;
		if (still)
		{
			m_velocity = sf::Vector2f(0.f, 0.f);
		}

		StateMachineComponent* stateComponent = m_entity.GetComponent<StateMachineComponent>();
		if (stateComponent)
		{
			unsigned int wanted = still ? IDLE : MOVE;

			if (wanted != m_state)
			{
				m_state = State(wanted);
				stateComponent->changeState(wanted);
			}
		}

		GraphicComponent* gComponent = m_entity.GetComponent<GraphicComponent>();
		if (gComponent)
		{
			sf::Sprite& _sprite = gComponent->GetSprite();

			_sprite.setPosition(_sprite.getPosition() + m_velocity * _deltaTime);
		}
	}
	else
	{
		StateMachineComponent* stateComponent = m_entity.GetComponent<StateMachineComponent>();
		if (stateComponent && stateComponent->CanChangeState())
		{
			m_isAttack = false;
		}
	}
}

void PatrolComponent::Initialize()
{

}

void PatrolComponent::Update(const float _deltaTime)
{
	m_timer -= _deltaTime;

	if (m_timer < 0.f)
	{
		m_timer += m_changeDir;

		if (static_cast<State>((m_state + 1) % ALL_STATE) != m_state)
		{
			m_state = static_cast<State>((m_state + 1) % ALL_STATE);
			if (m_stateMachine)
			{
				m_stateMachine->changeState(m_state);
			}
		}


		if (m_state == PATROl)
		{
			Dir newDir = UP;

			do
			{
				newDir = static_cast<Dir>(std::rand() % ALL_DIR);
			} while (newDir == m_lastDir1);

			m_lastDir1 = newDir;

			Dir addedDir = static_cast<Dir>((std::rand() % 100 > 50) ? (std::rand() % 2) == 0 ? (newDir + 1) % ALL_DIR : (newDir + 2) % ALL_DIR : newDir);

			m_lastDir2 = addedDir;
			m_dir = GetDir(newDir, addedDir);

			float normal = std::sqrt(m_dir.x * m_dir.x + m_dir.y * m_dir.y);
			normal = normal != 0.f ? normal : 1;
			m_dir = sf::Vector2f(m_dir.x / normal, m_dir.y / normal);
			m_velocity = m_dir * m_speed;
		}
	}

	if ((m_velocity.x != 0.f || m_velocity.y != 0.f) && m_state == PATROl)
	{
		GraphicComponent* gComponent = m_entity.GetComponent<GraphicComponent>();
		if (gComponent)
		{
			sf::Sprite& _sprite = gComponent->GetSprite();

			_sprite.setPosition(_sprite.getPosition() + m_velocity * _deltaTime);
		}
	}
}

//json PatrolComponent::Serialize() const
//{
//	json cJson;
//
//	cJson[]
//
//	return cJson;
//}
//
//void PatrolComponent::Deserialize(const json& _json)
//{
//}

sf::Vector2f PatrolComponent::GetDir(Dir& _dir1, Dir& _dir2)
{
	sf::Vector2f newDir = { 0.f,0.f };

	switch (_dir1)
	{
	case UP:
		newDir.y = -1;
		break;
	case DOWN:
		newDir.y = 1;
		break;
	case LEFT:
		newDir.x = -1;
		break;
	case RIGHT:
		newDir.x = 1;
		break;
	default:
		break;
	}

	switch (_dir2)
	{
	case UP:
		newDir.y = -1;
		break;
	case DOWN:
		newDir.y = 1;
		break;
	case LEFT:
		newDir.x = -1;
		break;
	case RIGHT:
		newDir.x = 1;
		break;
	default:
		break;
	}

	return newDir;
}

void StateMachineComponent::changeState(unsigned int const _state)
{

	if (_state < m_animByState.size())
	{
		GraphicComponent::AnimParametter& anim = m_animByState[_state];
		m_currentState = _state;
		GraphicComponent* gComponent = m_entity.GetComponent<GraphicComponent>();
		if (gComponent)
		{
			gComponent->SetAnim(anim);
		}
		//std::cout << "spam change state" << std::endl;
	}
}

bool StateMachineComponent::CanChangeState()
{
	GraphicComponent* gComponent = m_entity.GetComponent<GraphicComponent>();
	if (gComponent)
	{
		return gComponent->GetIsFinished();
	}
	return false;
}

json StateMachineComponent::Serialize() const
{
	json componentJson;
	componentJson["currentState"] = (int)m_currentState;
	componentJson["totalState"] = (int)m_totalState;

	json animationArray = json::array();
	for (const GraphicComponent::AnimParametter& animData : m_animByState)
	{
		json animDataJson;
		animationArray.push_back(animData.Serialize());
	}
	componentJson["animationData"] = animationArray;
	return componentJson;
}

void StateMachineComponent::Deserialize(const json& _json)
{
	m_totalState = _json["totalState"].get<int>();

	const json& animationDataArray = _json["animationData"];

	for (const json& animDataJson : animationDataArray)
	{
		GraphicComponent::AnimParametter animData;

		animData.Deserialize(animDataJson);

		m_animByState.push_back(animData);
	}

	int currentState = _json["currentState"].get<int>();
	changeState(currentState);
}

const char* Component::S_GetTypeName(Component& _component)
{
	return _component.GetName();
}

Component* Component::S_Create(const char* _typeName, Entity& _entity)
{
	const std::string typeName = _typeName;
	if (typeName == "GraphicComponent")
	{
		return new GraphicComponent(_entity);
	}
	else if (typeName == "ControllerComponent")
	{
		return new ControllerComponent(_entity);
	}
	else if (typeName == "PatrolComponent")
	{
		return new PatrolComponent(_entity);
	}
	else if (typeName == "StateMachineComponent")
	{
		return new StateMachineComponent(_entity);
	}

	return nullptr;
}
