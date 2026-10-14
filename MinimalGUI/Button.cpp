#include "Button.h"

Button::Button(sf::Shape* _shape, sf::Text* _text)
{
	this->m_shape = _shape;
	m_isActive = false;
	m_isOver = false;
	m_text = _text;
}

Button::~Button()
{
	delete this->m_shape; 
	
	if (m_text)
	{
		delete m_text;
	}
}

void Button::Update(const sf::Vector2i& _pos)
{
	sf::Color fillC = m_isActive ? COLOR_G : COLOR_R;

	this->m_shape->setFillColor(m_isOver ? fillC + sf::Color(20, 20, 20) : fillC);
}

void Button::Draw(sf::RenderTarget& _render)
{
	_render.draw(*m_shape);

	if(m_text != nullptr)
	{
		_render.draw(*m_text);
	}
}

void Button::SetOwner(Widget* _owner)
{
	m_owner = _owner;
}

void Button::Pressed(const sf::Mouse::Button& _button, const sf::Vector2i& _pos)
{
	CheckCollision(_pos);
	if (m_isOver)
	{
		if(_button == sf::Mouse::Button::Left)
		{
			m_isActive = true;
		}
		else if (_button == sf::Mouse::Button::Right)
		{
			if (m_owner)
			{
				m_owner->Delete(this);
			}
		}
	}
}

void Button::Released()
{
	if (m_isActive && m_onClick)
	{
		m_onClick();
	}
	m_isActive = false;
}

void Button::SetOnClick(Callback _cb)
{
	m_onClick = std::move(_cb);
}

const sf::Vector2f& Button::GetSize(void)
{
	sf::FloatRect bound = m_shape ? m_shape->getLocalBounds() : sf::FloatRect();
	return sf::Vector2f(bound.width, bound.height);
}

void Button::SetPosition(const sf::Vector2f& _pos)
{
	if (m_shape)
	{
		m_shape->setPosition(_pos);

		if (m_text)
		{
			CenterTextOnShape(*m_text, *m_shape);
		}
	}
}

void Button::CheckCollision(const sf::Vector2i& const _pos)
{
	sf::FloatRect floatR = this->m_shape->getGlobalBounds();
	sf::Vector2f vec = sf::Vector2f(_pos);
	m_isOver = CollisionRectPoint(floatR, vec);
	//std::cout << "x : " << vec.x << "y : " << vec.y << std::endl;
	//std::cout << (isOver ? "collision" : "No collision") << std::endl;
}
