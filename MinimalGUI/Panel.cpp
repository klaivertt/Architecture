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

void Panel::Layout()
{
	sf::Vector2f size(0.f, 0.f);
	sf::Vector2f pos = rect ? rect->getPosition() : sf::Vector2f(0,0);
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
