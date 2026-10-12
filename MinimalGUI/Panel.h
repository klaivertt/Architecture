#pragma once

#include "Widget.h"

class Panel : public Widget
{
public:
	Panel(sf::RectangleShape* _rect, sf::Vector2f _margin = sf::Vector2f(0,0), sf::Text* _text = nullptr);
	~Panel();

	void Update(const sf::Vector2i& _pos);
	void Draw(sf::RenderTarget& _render);
	void Pressed(const sf::Vector2i& _pos);
	void Released();
	const sf::Vector2f& GetSize(void);
	void SetPosition(const sf::Vector2f& _pos);
	void Layout();

	void Add(Widget* _widget);
	void Delete(Widget* _widget);
private:
	std::vector<Widget*> widgets;
	sf::Text* text;
	sf::RectangleShape* rect;
	sf::Vector2f margin;

};
