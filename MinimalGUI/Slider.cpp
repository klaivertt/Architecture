#include "Slider.h"

Slider::Slider(sf::Vector2f _bound, float _current, sf::RectangleShape* _shape, sf::Text* _text, bool _isPercent)
{
	this->m_shape = _shape;
	m_isActive = false;
	m_isOver = false;
	m_shape->setOutlineColor(sf::Color(100, 100, 100));
	m_shape->setOutlineThickness(5.f);
	sf::FloatRect rectBound = m_shape->getLocalBounds();

	m_text = _text;

	m_bound = _bound;
	m_current = _current;
	m_isPercent = _isPercent;

	float percent = static_cast<float>(m_current) / m_bound.y;
	m_inPercent = std::clamp(percent, 0.f, 1.f);
}

Slider::~Slider()
{
	if (m_shape)
	{
		delete m_shape;
	}

	if (m_text)
	{
		delete m_text;
	}
}

void Slider::Update(const sf::Vector2i& _pos)
{
	if (m_isActive)
	{
		sf::FloatRect bound = m_shape->getGlobalBounds();
		float percent = static_cast<float>((_pos.x) - bound.left) / bound.width;
		m_inPercent = std::clamp(percent, 0.f, 1.f);
	}

}

void Slider::Draw(sf::RenderTarget& _render)
{
	if (m_shape)
	{
		sf::Color baseColor = m_shape->getFillColor();
		sf::FloatRect bound = m_shape->getLocalBounds();

		m_shape->setSize(sf::Vector2f(bound.width * m_inPercent, bound.height));
		m_shape->setFillColor(baseColor);
		_render.draw(*m_shape);

		m_shape->setFillColor(sf::Color::Transparent);
		m_shape->setSize(sf::Vector2f(bound.width, bound.height));
		m_shape->setOutlineColor(sf::Color(75, 75, 75));
		m_shape->setOutlineThickness(1.f);
		_render.draw(*m_shape);

		m_shape->setOutlineThickness(0.f);
		m_shape->setFillColor(baseColor);
	}

	if (m_text)
	{
		std::string base = m_text->getString();
		std::string string = "";
		if (m_isPercent)
		{
			string += std::to_string(int(m_inPercent * 100.f));
		}
		else
		{

			string += std::format("{:.2f}", m_current);
		}

		m_text->setString(base + " " + string);
		_render.draw(*m_text);
		m_text->setString(base);
	}
}

void Slider::SetOwner(Widget* _owner)
{
	m_owner = _owner;
}

void Slider::Pressed(const sf::Mouse::Button& _button, const sf::Vector2i& _pos)
{
	CheckCollision(_pos);
	if (m_isOver)
	{
		if (_button == sf::Mouse::Button::Left)
		{
			m_isActive = true;

			std::cout << "left" << std::endl;
		}
		else if (_button == sf::Mouse::Button::Right)
		{
			if (m_owner)
			{
				m_owner->Delete(this);
			}
			std::cout << "right" << std::endl;
		}
	}
}

void Slider::SetOnReleased(Callback _cb)
{
	m_onReleased = std::move(_cb);
}

void Slider::Released()
{
	if (m_isActive && m_onReleased)
	{
		//std::cout << "hi" << std::endl;
		m_current = m_bound.x + m_inPercent * (m_bound.y - m_bound.x);
		m_onReleased(m_current);
	}

	m_isActive = false;
}

const sf::Vector2f& Slider::GetSize(void)
{
	sf::FloatRect bound = m_shape ? m_shape->getLocalBounds() : sf::FloatRect();
	return sf::Vector2f(bound.width, bound.height);
}

void Slider::SetPosition(const sf::Vector2f& _pos)
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

void Slider::CheckCollision(const sf::Vector2i& _pos)
{
	sf::FloatRect floatR = this->m_shape->getGlobalBounds();
	sf::Vector2f vec = sf::Vector2f(_pos);
	m_isOver = CollisionRectPoint(floatR, vec);
}
