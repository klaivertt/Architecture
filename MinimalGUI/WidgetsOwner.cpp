#include "WidgetsOwner.h"

WidgetsOwner* WidgetsOwner::s_instance = nullptr;

WidgetsOwner::WidgetsOwner()
{
}

WidgetsOwner::~WidgetsOwner()
{
}

void WidgetsOwner::Update(const sf::Vector2i& _pos)
{
	for (auto widget : widgets)
	{
		widget->Update(_pos);
	}
}

void WidgetsOwner::Draw(sf::RenderTarget& _render)
{
	for (auto widget : widgets)
	{
		widget->Draw(_render);
	}
}

void WidgetsOwner::Add(Widget* _widget)
{
	widgets.push_back(_widget);
}

void WidgetsOwner::Pressed(const sf::Vector2i& _pos)
{
	for (auto widget : widgets)
	{
		widget->Pressed(_pos);
	}
}

void WidgetsOwner::Released()
{
	for (auto widget : widgets)
	{
		widget->Released();
	}
}

void WidgetsOwner::Clear()
{
	for (auto widget : widgets)
	{
		delete widget;
	}

	widgets.clear();
}
