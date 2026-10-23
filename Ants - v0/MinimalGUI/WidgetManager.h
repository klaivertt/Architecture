#pragma once
#include "common.h"
#include "Widget.h"

//---------------------------------------------------------------------------------
class WidgetManager
{
public:
	SINGLETON_PUBLIC_DECLARATION(WidgetManager);

	bool onEvent(sf::Event& _mouseEvent, const sf::Window& _window);
	void draw(sf::RenderTarget& _renderTarget, const sf::Font& _font) const;

	void pushWidget(Widget& _widget) { m_rootPanel.pushChild(_widget); }
	void setup() { m_rootPanel.setup(); }

private:
	SINGLETON_PRIVATE_DECLARATION(WidgetManager);

	Widget* findWidgetAtPosition(const sf::Vector2f& _position);

	Panel m_rootPanel{ "GUI", {10, 10} };

	sf::Vector2f m_mousePressedPosition{ 0, 0 };

	Widget* m_hovered{ nullptr };
	Widget* m_pressed{ nullptr };

	enum class DrawMode
	{
		Pastel,
		Matrix
	};
	DrawMode m_drawMode{ DrawMode::Pastel };
	ConstVisitor* createDrawVisitor(sf::RenderTarget& _renderTarget, const sf::Font& _font, const Widget* _hovered, const Widget* _pressed) const;
};