#pragma once

#include "common.h"
#include "Widget.h"

class WidgetsOwner : public Widget
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
	void Pressed(const sf::Mouse::Button& _button, const sf::Vector2i& _pos);
	void Released();
	void Clear();
	void Delete(Widget* _widget);
	void CleanDelete();

	const sf::Vector2f& GetSize(void) { return  sf::Vector2f(); }
	void SetOwner(Widget* _owner, bool _isManager = false){}
	void SetPosition(const sf::Vector2f& _pos){}
private:
	WidgetsOwner();
	~WidgetsOwner();
	std::vector<Widget*> widgets;
	std::vector<Widget*> deleteQueue;

	static WidgetsOwner* s_instance;
};