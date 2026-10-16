#include "WidgetsOwner.h"

WidgetsOwner* WidgetsOwner::s_instance = nullptr;

WidgetsOwner::WidgetsOwner()
{
	m_owner = nullptr;
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

void WidgetsOwner::Pressed(const sf::Mouse::Button& _button, const sf::Vector2i& _pos)
{
	for (auto widget : widgets)
	{
		widget->Pressed(_button ,_pos);
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

void WidgetsOwner::Delete(Widget* _widget)
{
	if (_widget != nullptr)
	{
		deleteQueue.push_back(_widget);
	}
}

void WidgetsOwner::CleanDelete()
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
