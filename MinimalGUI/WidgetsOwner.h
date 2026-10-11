#pragma once

#include "common.h"
#include "Widget.h"

class WidgetsOwner
{
public:
	static void s_create()
	{
		if (!s_instance)
		{
			s_instance = new WidgetsOwner();
		}
	}

	static WidgetsOwner* get()
	{
		return s_instance;
	}

	void Update(const sf::Vector2i& _pos);
	void Draw(sf::RenderTarget& _render);
	void Add(Widget* _widget);
	void Pressed(const sf::Vector2i& _pos);
	void Released();
	void Clear();
private:
	WidgetsOwner();
	~WidgetsOwner();

	std::vector<Widget*> widgets;

	static WidgetsOwner* s_instance;

};