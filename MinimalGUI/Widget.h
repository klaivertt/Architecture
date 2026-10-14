#pragma once
#include "common.h"

#define COLOR_R sf::Color(200,50,50)
#define COLOR_G sf::Color(50,200,50)

class Widget
{
public:
	virtual ~Widget() = default;

	virtual void Update(const sf::Vector2i& _pos) = 0;
	virtual void Draw(sf::RenderTarget& _render) = 0;

	virtual void Pressed(const sf::Mouse::Button& _button, const sf::Vector2i& _pos) = 0;
	virtual void Released() = 0;
	virtual void Delete(Widget* _widget) = 0;
	virtual void CleanDelete() = 0;

	virtual const sf::Vector2f& GetSize(void) = 0;
	virtual void SetOwner(Widget* _owner) = 0;
	virtual void SetPosition(const sf::Vector2f& _pos) = 0;
protected:
	bool m_isActive;
	bool m_isOver;
	Widget* m_owner;
};