#include "Entity.h"

using namespace CJ;

//void Player::Update(const float _deltaTime)
//{
//	sf::Vector2f dir = sf::Vector2f(0.f, 0.f);
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
//	{
//		dir.y = -1.f;
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//	{
//		dir.y = 1.f;
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
//	{
//		dir.x = -1.f;
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//	{
//		dir.x = 1.f;
//	}
//	float normal = std::sqrt(dir.x * dir.x + dir.y * dir.y);
//	normal = normal != 0.f ? normal : 1;
//	dir = sf::Vector2f(dir.x / normal, dir.y / normal);
//	m_velocity += dir * m_speed;
//
//	m_sprite.setPosition(m_sprite.getPosition() + m_velocity * _deltaTime);
//
//	m_velocity *= 0.85f;
//	if (std::abs(m_velocity.x) < 0.1f && std::abs(m_velocity.y) < 0.1f)
//	{
//		m_velocity = sf::Vector2f(0.f, 0.f);
//	}
//
//	//keyUp = false;
//	//keyDown = false;
//	//keyLeft = false;
//	//keyRight = false;
//}
//
//Mob::Mob(const char* _textureFile, const sf::IntRect& _area, const sf::Vector2f& _position)
//	: Entity(_textureFile, _area, _position)
//{
//}
//
//void Mob::Update(const float _deltaTime)
//{
//	m_timer -= _deltaTime;
//
//	if (m_timer < 0.f)
//	{
//		m_timer += m_changeDir;
//		
//		m_state = static_cast<State>((m_state + 1) % ALL_STATE);
//		
//		if(m_state == PATROl)
//		{
//			Dir newDir = UP;
//
//			do
//			{
//				newDir = static_cast<Dir>(std::rand() % ALL_DIR);
//			} while (newDir == m_lastDir1);
//
//			m_lastDir1 = newDir;
//
//			Dir addedDir = static_cast<Dir>((std::rand() % 100 > 50) ? (std::rand() % 2) == 0 ? (newDir + 1) % ALL_DIR : (newDir + 2) % ALL_DIR : newDir);
//
//			m_lastDir2 = addedDir;
//			m_dir = GetDir(newDir, addedDir);
//
//			float normal = std::sqrt(m_dir.x * m_dir.x + m_dir.y * m_dir.y);
//			normal = normal != 0.f ? normal : 1;
//			m_dir = sf::Vector2f(m_dir.x / normal, m_dir.y / normal);
//			m_velocity = m_dir * m_speed;
//		}
//	}
//	
//	if ((m_velocity.x != 0.f || m_velocity.y != 0.f) && m_state == PATROl)
//	{
//		m_sprite.setPosition(m_sprite.getPosition() + m_velocity * _deltaTime);
//	}
//	//std::cout << m_sprite.getPosition().x << " : " << m_sprite.getPosition().y << std::endl;
//}
//
//sf::Vector2f Mob::GetDir(Dir& _dir1, Dir& _dir2)
//{
//	sf::Vector2f newDir = { 0.f,0.f };
//
//	switch (_dir1)
//	{
//	case UP:
//		newDir.y = -1;
//		break;
//	case DOWN:
//		newDir.y = 1;
//		break;
//	case LEFT:
//		newDir.x = -1;
//		break;
//	case RIGHT:
//		newDir.x = 1;
//		break;
//	default:
//		break;
//	}
//
//	switch (_dir2)
//	{
//	case UP:
//		newDir.y = -1;
//		break;
//	case DOWN:
//		newDir.y = 1;
//		break;
//	case LEFT:
//		newDir.x = -1;
//		break;
//	case RIGHT:
//		newDir.x = 1;
//		break;
//	default:
//		break;
//	}
//
//	return newDir;
//}
