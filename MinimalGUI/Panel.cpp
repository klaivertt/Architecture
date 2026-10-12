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

void Panel::Pressed(const sf::Vector2i& _pos)
{
	for (auto widget : widgets)
	{
		widget->Pressed(_pos);
	}
}

void Panel::Released()
{
	for (auto widget : widgets)
	{
		widget->Released();
	}
}

const sf::Vector2f& Panel::GetSize(void)
{
	sf::FloatRect bound = rect ? rect->getLocalBounds() : sf::FloatRect();
	return sf::Vector2f(bound.width, bound.height);
}

void Panel::Add(Widget* _widget)
{
	widgets.push_back(_widget);

	sf::Vector2f size = sf::Vector2f(0, 0);

	size = sf::Vector2f(0, 0);
	for (auto widget : widgets)
	{
		sf::Vector2f widgetSize = widget->GetSize();
		if (size.x == 0)
		{
			size.x = widgetSize.x;
		}
		else if (size.x < widgetSize.x)
		{
			size.x = widgetSize.x;
		}

		size.y += widgetSize.y + margin.y;
	}

	rect.setSize(size);

}

void Panel::Delete(Widget* _widget)
{
	for (auto it = widgets.begin(); it != widgets.end(); ++it)
	{
		if (_widget == *it)
		{
			widgets.erase(it);
			delete *it;
			break;
		}
	}
}
