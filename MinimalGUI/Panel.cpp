#include "Panel.h"

Panel::Panel(sf::RectangleShape* _rect, sf::Vector2f _margin, sf::Text* _text)
{
	text = _text;
	rect = _rect;
	margin = _margin;
}

Panel::~Panel()
{
	if (text)
	{
		delete text;
	}

	for (auto widget : widgets)
	{
		delete widget;
	}

	widgets.clear();
}

void Panel::Update(const sf::Vector2i& _pos)
{
	for (auto widget : widgets)
	{
		widget->Update(_pos);
	}
}

void Panel::Draw(sf::RenderTarget& _render)
{
	if (rect)
	{
		_render.draw(*rect);
	}

	if (text)
	{
		_render.draw(*text);
	}

	for (auto widget : widgets)
	{
		widget->Draw(_render);
	}
}

void Panel::Pressed(const sf::Mouse::Button& _button, const sf::Vector2i& _pos)
{
	for (auto widget : widgets)
	{
		widget->Pressed(_button, _pos);
	}

	if (_button == sf::Mouse::Button::Right)
	{
		if (rect->getGlobalBounds().contains(sf::Vector2f(_pos)))
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
}

void Panel::Released()
{
	for (auto widget : widgets)
	{
		widget->Released();
	}
}

void Panel::SetOwner(Widget* _owner)
{
	m_owner = _owner;
}

const sf::Vector2f& Panel::GetSize(void)
{
	sf::FloatRect bound = rect ? rect->getLocalBounds() : sf::FloatRect();
	return sf::Vector2f(bound.width, bound.height);
}

void Panel::SetPosition(const sf::Vector2f& _pos)
{
	if (rect)
	{
		rect->setPosition(_pos);
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
}


void Panel::Layout()
{
	sf::Vector2f size(0.f, 0.f);
	sf::Vector2f pos = rect ? rect->getPosition() : sf::Vector2f(0, 0);
	float y = pos.y;
	pos.x += margin.x;
	if (text)
	{
		text->setPosition(pos.x, pos.y + margin.y / 2);
		y += text->getLocalBounds().height + margin.y / 0.5f;
	}

	for (Widget* widget : widgets)
	{
		sf::Vector2f widgetSize = widget->GetSize();

		widget->SetPosition(sf::Vector2f(pos.x + margin.x, y));

		size.y += widgetSize.y + margin.y;

		y += widgetSize.y + margin.y;
		size.x = std::max(size.x, widgetSize.x);
	}
	size.x += margin.x * 3.f;
	size.y = y - pos.y;

	if (rect)
	{
		rect->setSize(size);
	}
}
