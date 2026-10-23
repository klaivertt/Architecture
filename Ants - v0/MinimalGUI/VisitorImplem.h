#pragma once
#include "Visitor.h"
#include "Widget.h"

bool isPointInside(const sf::Vector2f& _position, const Widget& _widget);

//---------------------------------------------------------------------------------
class FindWidgetVisitor : public Visitor
{
public:
	FindWidgetVisitor(const sf::Vector2f& _position) : m_position(_position)
	{
	}
	virtual void visit(Button& _button) override;
	virtual void visit(Slider<unsigned>& _slider) override;
	virtual void visit(Slider<float>& _slider) override;
	virtual void visit(Panel& _panel) override;

	Widget* getFound() const { return m_found; }

private:
	const sf::Vector2f& m_position;
	Widget* m_found{ nullptr };
};

//---------------------------------------------------------------------------------
class DrawVisitor : public ConstVisitor
{
public:
	DrawVisitor(sf::RenderTarget& _renderTarget, const sf::Font& _font,
		const Widget* _hovered, const Widget* _pressed)
		: m_renderTarget(_renderTarget), m_font(_font)
		, m_hovered(_hovered), m_pressed(_pressed)
	{
	}
	virtual void visit(const Button& _button) override;
	virtual void visit(const Slider<unsigned>& _slider) override;
	virtual void visit(const Slider<float>& _slider) override;
	virtual void visit(const Panel& _panel) override;
	virtual void visit(const Label& _panel) override;

	bool isWidgetHovered(const Widget& _widget) const { return (&_widget == m_hovered); }

private:
	template<typename WidgetType>
	sf::RectangleShape createRectangleShape(const WidgetType& _widget)
	{
		sf::RectangleShape r;
		r.setFillColor(getFillColor(_widget));
		r.setOutlineColor(getOutlineColor(_widget));
		r.setOutlineThickness(getOutlineThickness(_widget));
		r.setPosition(_widget.getTopLeft());
		r.setSize(_widget.getSize());
		return r;
	}

	virtual float getDefaultOutlineThickness() const { return 1.f; }
	virtual sf::Color getDefaultFillColor() const { return sf::Color::Black; }
	virtual sf::Color getDefaultOutlineColor() const { return sf::Color::Black; }
	virtual sf::Color getDefaultTextColor() const { return sf::Color::Black; }

	virtual float getOutlineThickness(const Widget& _widget) const { return getDefaultOutlineThickness(); }
	virtual sf::Color getFillColor(const Widget& _widget) const { return getDefaultFillColor(); }
	virtual sf::Color getOutlineColor(const Widget& _widget) const { return getDefaultOutlineColor(); }
	virtual sf::Color getTextColor(const Widget& _widget) const { return getDefaultTextColor(); }

	virtual float getOutlineThickness(const Slider<unsigned>& _widget) const { return getDefaultOutlineThickness(); }
	virtual sf::Color getFillColor(const Slider<unsigned>& _widget) const { return getDefaultFillColor(); }
	virtual sf::Color getOutlineColor(const Slider<unsigned>& _widget) const { return getDefaultOutlineColor(); }
	virtual sf::Color getTextColor(const Slider<unsigned>& _widget) const { return getDefaultTextColor(); }

	virtual float getOutlineThickness(const Slider<float>& _widget) const { return getDefaultOutlineThickness(); }
	virtual sf::Color getFillColor(const Slider<float>& _widget) const { return getDefaultFillColor(); }
	virtual sf::Color getOutlineColor(const Slider<float>& _widget) const { return getDefaultOutlineColor(); }
	virtual sf::Color getTextColor(const Slider<float>& _widget) const { return getDefaultTextColor(); }

	virtual float getOutlineThickness(const Button& _widget) const { return getDefaultOutlineThickness(); }
	virtual sf::Color getFillColor(const Button& _widget) const { return getDefaultFillColor(); }
	virtual sf::Color getOutlineColor(const Button& _widget) const { return getDefaultOutlineColor(); }
	virtual sf::Color getTextColor(const Button& _widget) const { return getDefaultTextColor(); }

	virtual float getOutlineThickness(const Panel& _widget) const { return getDefaultOutlineThickness(); }
	virtual sf::Color getFillColor(const Panel& _widget) const { return getDefaultFillColor(); }
	virtual sf::Color getOutlineColor(const Panel& _widget) const { return getDefaultOutlineColor(); }
	virtual sf::Color getTextColor(const Panel& _widget) const { return getDefaultTextColor(); }

	sf::RenderTarget& m_renderTarget;
	const sf::Font& m_font;

	const Widget* m_hovered{ nullptr };
	const Widget* m_pressed{ nullptr };
};

//---------------------------------------------------------------------------------
class PastelDrawVisitor : public DrawVisitor
{
public:
	PastelDrawVisitor(sf::RenderTarget& _renderTarget, const sf::Font& _font,
		const Widget* _hovered, const Widget* _pressed)
		: DrawVisitor(_renderTarget, _font, _hovered, _pressed)
	{
	}

private:
	virtual float getDefaultOutlineThickness() const { return 1.f; }
	virtual sf::Color getDefaultFillColor() const { return sf::Color(170, 200, 200); }
	virtual sf::Color getDefaultOutlineColor() const { return sf::Color::Black; }
	virtual sf::Color getDefaultTextColor() const { return sf::Color::Black; }

	virtual float getOutlineThickness(const Slider<unsigned>& _widget) const { return isWidgetHovered(_widget) ? 2.f : 1.f; }
	virtual sf::Color getFillColor(const Slider<unsigned>& _widget) const { return sf::Color(200, 170, 200); }
	virtual sf::Color getOutlineColor(const Slider<unsigned>& _widget) const { return sf::Color::Black; }
	virtual sf::Color getTextColor(const Slider<unsigned>& _widget) const { return sf::Color::Black; }

	virtual float getOutlineThickness(const Slider<float>& _widget) const { return isWidgetHovered(_widget) ? 2.f : 1.f; }
	virtual sf::Color getFillColor(const Slider<float>& _widget) const { return sf::Color(200, 170, 200); }
	virtual sf::Color getOutlineColor(const Slider<float>& _widget) const { return sf::Color::Black; }
	virtual sf::Color getTextColor(const Slider<float>& _widget) const { return sf::Color::Black; }

	virtual float getOutlineThickness(const Button& _widget) const { return isWidgetHovered(_widget) ? 2.f : 1.f; }
	virtual sf::Color getFillColor(const Button& _widget) const { return sf::Color(200, 200, 170); }
	virtual sf::Color getOutlineColor(const Button& _widget) const { return sf::Color::Black; }
	virtual sf::Color getTextColor(const Button& _widget) const { return sf::Color::Black; }

	virtual float getOutlineThickness(const Panel& _widget) const { return 1.f; }
	virtual sf::Color getFillColor(const Panel& _widget) const { return sf::Color(170, 200, 200); }
	virtual sf::Color getOutlineColor(const Panel& _widget) const { return sf::Color::Black; }
	virtual sf::Color getTextColor(const Panel& _widget) const { return sf::Color::Black; }
};

//---------------------------------------------------------------------------------
class MatrixDrawVisitor : public DrawVisitor
{
public:
	MatrixDrawVisitor(sf::RenderTarget& _renderTarget, const sf::Font& _font,
		const Widget* _hovered, const Widget* _pressed)
		: DrawVisitor(_renderTarget, _font, _hovered, _pressed)
	{
	}

private:
	virtual float getDefaultOutlineThickness() const { return 1.f; }
	virtual sf::Color getDefaultFillColor() const { return sf::Color(0, 50, 0); }
	virtual sf::Color getDefaultOutlineColor() const { return sf::Color::Green; }
	virtual sf::Color getDefaultTextColor() const { return sf::Color::Green; }

	virtual float getOutlineThickness(const Button& _widget) const { return 0.f; }
	virtual sf::Color getFillColor(const Button& _widget) const { return sf::Color::Black; }

	virtual sf::Color getFillColor(const Panel& _widget) const { return sf::Color::Transparent; }
};