#pragma once

#include "Widget.h"


class Button : public Widget
{
private:
	using Callback = std::function<void()>;
public:

	Button(sf::Shape* _shape, sf::Text* _text = nullptr);
	~Button();
	void Update(const sf::Vector2i& _pos) override;
	void Draw(sf::RenderTarget& _render) override;

	void SetOwner(Widget* _owner);
	void Delete(Widget* _widget) {}
	void CleanDelete() {}

	void Pressed(const sf::Mouse::Button& _button, const sf::Vector2i& _pos) override;
	void Released() override;

	void SetOnClick(Callback _cb);
	const sf::Vector2f& GetSize(void);
	void SetPosition(const sf::Vector2f& _pos);
protected:
	sf::Shape* m_shape;
	Callback m_onClick;
	sf::Text* m_text;
	void CheckCollision(const sf::Vector2i& _pos);
};