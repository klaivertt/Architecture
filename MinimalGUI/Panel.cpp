#include "Panel.h"

Panel::Panel(sf::RectangleShape* _rect, sf::Vector2f _margin, sf::Text* _text)
{
	m_text = _text;
	m_shape = _rect;
	m_margin = _margin;
}

Panel::~Panel()
{
	if (m_text)
	{
		delete m_text;
	}

	if (m_shape)
	{
		delete m_shape;
	}

	for (auto widget : widgets)
	{
		delete widget;
	}

	widgets.clear();
}

void Panel::Update(const sf::Vector2i& _pos)
{
	if (!m_isActive)
	{
	for (auto widget : widgets)
	{
		widget->Update(_pos);
	}
	}

	if (m_isActive)
	{
		SetPosition(sf::Vector2f(_pos) - m_offset);
	}
}

void Panel::Draw(sf::RenderTarget& _render)
{
	if (m_shape)
	{
		_render.draw(*m_shape);
	}

	if (m_text)
	{
		_render.draw(*m_text);
	}

	for (auto widget : widgets)
	{
		widget->Draw(_render);
	}
}

void Panel::Pressed(const sf::Mouse::Button& _button, const sf::Vector2i& _pos)
{


	if (_button == sf::Mouse::Button::Left && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
	{
		if (m_shape->getGlobalBounds().contains(sf::Vector2f(_pos)))
		{
			if (m_managerOwned)
			{
				m_isActive = true;
				sf::FloatRect bound = m_shape->getGlobalBounds();
				m_offset = sf::Vector2f(_pos.x - bound.left, _pos.y - bound.top);
			}
		}
	}
	else if (_button == sf::Mouse::Button::Right)
	{
		if (m_shape->getGlobalBounds().contains(sf::Vector2f(_pos)))
		{
			if (widgets.size() == 0)
			{
				if (m_owner)
				{
					m_owner->Delete(this);
				}
			}
		}
	}
	
	if (_button == sf::Mouse::Button::Right && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
	{
		for (auto widget : widgets)
		{
			deleteQueue.push_back(widget);
		}
		if (m_owner)
		{
			m_owner->Delete(this);
		}
	}
	if (!m_isActive)
	{
		for (auto widget : widgets)
		{
			widget->Pressed(_button, _pos);
		}
	}
}

void Panel::Released()
{
	for (auto widget : widgets)
	{
		widget->Released();
	}
	m_isActive = false;
}

void Panel::SetOwner(Widget* _owner, bool _isManager)
{
	m_owner = _owner;
	m_managerOwned = _isManager;
}

const sf::Vector2f& Panel::GetSize(void)
{
	sf::FloatRect bound = m_shape ? m_shape->getLocalBounds() : sf::FloatRect();
	return sf::Vector2f(bound.width, bound.height);
}

void Panel::SetPosition(const sf::Vector2f& _pos)
{
	if (m_shape)
	{
		m_shape->setPosition(_pos);
	}

	Layout();
}

void Panel::Add(Widget* _widget)
{
	widgets.push_back(_widget);
	Layout();
}

void Panel::Delete(Widget* _widget)
{
	if (_widget != nullptr)
	{
		deleteQueue.push_back(_widget);
	}
}

void Panel::CleanDelete()
{
	for (auto* widget : widgets)
	{
		if (widget != nullptr)
		{
			widget->CleanDelete();
		}
	}

	for (Widget* widgetToDelete : deleteQueue)
	{
		auto it = std::find(
			widgets.begin(),
			widgets.end(),
			widgetToDelete
		);

		if (it != widgets.end())
		{
			delete* it;
			widgets.erase(it);
		}
	}

	deleteQueue.clear();
	Layout();
}


void Panel::Layout()
{
	sf::Vector2f size(0.f, 0.f);
	sf::Vector2f pos = m_shape ? m_shape->getPosition() : sf::Vector2f(0, 0);
	float y = pos.y;
	pos.x += m_margin.x;
	if (m_text)
	{
		m_text->setPosition(pos.x, pos.y + m_margin.y / 2);
		y += m_text->getLocalBounds().height + m_margin.y / 0.5f;
		size.x += m_text->getLocalBounds().width;
	}

	for (Widget* widget : widgets)
	{
		sf::Vector2f widgetSize = widget->GetSize();

		widget->SetPosition(sf::Vector2f(pos.x + m_margin.x, y));

		size.y += widgetSize.y + m_margin.y;

		y += widgetSize.y + m_margin.y;
		size.x = std::max(size.x, widgetSize.x);
	}
	size.x += m_margin.x * 3.f;
	size.y = y - pos.y;

	if (m_shape)
	{
		m_shape->setSize(size);
	}
}
