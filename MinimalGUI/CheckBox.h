#pragma once
#include "Widget.h"



class CheckBox : public Widget
{
private:
	using Callback = std::function<void(bool)>;
public:
	CheckBox(sf::Shape* _shape, sf::Text* _text = nullptr);
	~CheckBox();
	void Update(const sf::Vector2i& _pos) override;
	void Draw(sf::RenderTarget& _render) override;

	void Pressed(const sf::Mouse::Button& _button, const sf::Vector2i& _pos) override;
	void Released() override;

	void SetOwner(Widget* _owner, bool _isManager = false);
	void Delete(Widget* _widget) {}
	void CleanDelete() {}

	void SetOnToggle(Callback _cb);
	const sf::Vector2f& GetSize(void);
	void SetPosition(const sf::Vector2f& _pos);
protected :
	sf::Shape* m_shape;
	Callback m_onToggle;
	bool m_isPressed;
	sf::Text* m_text;
	virtual void CheckCollision(const sf::Vector2i& _pos);
};
