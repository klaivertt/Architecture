#include "Component.h"

using namespace CJ;

GraphicComponent::GraphicComponent(const char* _textureFile, sf::Vector2f& _position, const sf::IntRect& _area) : m_pos(_position)
{
	if (!m_texture.loadFromFile(_textureFile))
	{
		return;
	}

	m_sprite.setPosition(_position);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(_area);

	m_nbFrame = 0;
}

GraphicComponent::GraphicComponent(sf::Vector2f& _position, AnimParametter& _parametter) : m_pos(_position)
{
	if (!m_texture.loadFromFile(_parametter.path))
	{
		return;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(_position);

	sf::Vector2u textureSize = m_texture.getSize();

	sf::Vector2i divider = _parametter.frameDivider;

	m_frameSize = sf::Vector2i(textureSize.x / divider.x, textureSize.y / divider.y);

	m_startFrame = _parametter.startFrame;
	m_frameTime = _parametter.frameTime;
	m_nbFrame = _parametter.nbFrame;
	m_isLoop = _parametter.isLoop;

	sf::IntRect rect = sf::IntRect(m_startFrame.x + (m_frameSize.x * m_currentFrame), m_startFrame.y, m_frameSize.x, m_frameSize.y);

	m_sprite.setTextureRect(rect);
}

GraphicComponent::GraphicComponent(sf::Vector2f& _position) : m_pos(_position)
{
}

void GraphicComponent::Inputs(const std::vector<sf::Event>& _events)
{
}

void GraphicComponent::Update(const float _deltaTime)
{
	if (m_nbFrame > 0)
	{

		m_animationTimer += _deltaTime;

		if (m_animationTimer > m_frameTime)
		{
			m_animationTimer -= m_frameTime;
			if (m_isLoop)
			{
				m_isFinished = true;
				m_currentFrame = (m_currentFrame + 1) % m_nbFrame;
			}
			else if (m_currentFrame < m_nbFrame - 1)
			{
				m_currentFrame++;
				m_isFinished = false;
			}
			else
			{
				m_isFinished = true;
			}

			sf::IntRect rect = sf::IntRect(m_startFrame.x + (m_frameSize.x * m_currentFrame), m_startFrame.y, m_frameSize.x, m_frameSize.y);

			m_sprite.setTextureRect(rect);
		}
	}
}

void GraphicComponent::Render(sf::RenderTarget& _rt)
{
	m_sprite.setPosition(m_pos);
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

	m_startFrame = _anim.startFrame;
	m_frameTime = _anim.frameTime;
	m_nbFrame = _anim.nbFrame;
	m_isLoop = _anim.isLoop;
	m_currentFrame = 0;
	m_animationTimer = 0.f;
	m_isFinished = false;

	sf::IntRect rect = sf::IntRect(m_startFrame.x + (m_frameSize.x * m_currentFrame), m_startFrame.y, m_frameSize.x, m_frameSize.y);

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(rect);
}

TransformComponent::TransformComponent(sf::Vector2f _startPos)
{
	m_pos = _startPos;
}

void ControllerComponent::Inputs(const std::vector<sf::Event>& _events)
{
	for (const sf::Event& event : _events)
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			if (m_stateMachine)
			{
				if (!m_isAttack)
				{
					m_state = ATTACK;
					m_stateMachine->changeState(ATTACK);
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

		if (m_stateMachine)
		{
			unsigned int wanted = still ? IDLE : MOVE;

			if (wanted != m_state)
			{
				m_state = State(wanted);
				m_stateMachine->changeState(wanted);
			}
		}
		m_pos += m_velocity * _deltaTime;
	}
	else
	{
		if (m_stateMachine->CanChangeState())
		{
			m_isAttack = false;
		}
	}
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
		m_pos += m_velocity * _deltaTime;
	}
}

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
