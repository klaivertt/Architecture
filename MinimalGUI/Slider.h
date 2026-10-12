#pragma once

#include "Widget.h"

class Slider : public Widget
{
private:
	using Callback = std::function<void(float)>;
public:
	Slider(sf::Vector2f _bound = sf::Vector2f(0.f, 100.f), float _current = 0.f, sf::RectangleShape* _shape = nullptr, sf::Text* _text = nullptr);
	~Slider();

	void Update(const sf::Vector2i& _pos) override;
	void Draw(sf::RenderTarget& _render) override;

	void Pressed(const sf::Vector2i& _pos) override;
	void SetOnReleased(Callback _cb);
	void Released() override;
	const sf::Vector2f& GetSize(void);
private:
	sf::Vector2f m_bound;
	float m_current;
	Callback m_onReleased;

	sf::RectangleShape* m_shape;
	sf::Text* m_text;
	void CheckCollision(const sf::Vector2i& _pos) override;
};