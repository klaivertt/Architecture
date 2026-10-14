#pragma once

#include "Widget.h"

class Panel : public Widget
{
public:
	Panel(sf::RectangleShape* _rect, sf::Vector2f _margin = sf::Vector2f(0,0), sf::Text* _text = nullptr);
	~Panel();

	void Update(const sf::Vector2i& _pos);
	void Draw(sf::RenderTarget& _render);
	void Pressed(const sf::Mouse::Button& _button, const sf::Vector2i& _pos);
	void Released();

	void SetOwner(Widget* _owner);

	const sf::Vector2f& GetSize(void);
	void SetPosition(const sf::Vector2f& _pos);
	void Layout();

	void Add(Widget* _widget);
	void Delete(Widget* _widget);
	void CleanDelete();
private:
	std::vector<Widget*> widgets;
	std::vector<Widget*> deleteQueue;
	sf::Text* text;
	sf::RectangleShape* rect;
	sf::Vector2f margin;

};
