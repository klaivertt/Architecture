#pragma once
#include "common.h"
#include "Widget.h"

//---------------------------------------------------------------------------------
class WidgetManager
{
public:
	SINGLETON_PUBLIC_DECLARATION(WidgetManager);

	void onMouseEvent(sf::Event& _mouseEvent);
	void Update(const sf::Vector2f& _mousePosition);
	void draw(sf::RenderTarget& _renderTarget, const sf::Font& _font) const;

	void pushWidget(Widget& _widget) { m_rootPanel.pushChild(_widget); }
	void setup() { m_rootPanel.setup(); }

private:
	SINGLETON_PRIVATE_DECLARATION(WidgetManager);

	Panel m_rootPanel{ "GUI", {10, 10}, sf::Color::Black, sf::Color::White };
};