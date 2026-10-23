#pragma once

#include "common.h"
#include "Visitor.h"

class ConstVisitor;
class Visitor;


//---------------------------------------------------------------------------------
class Widget
{
public:
	Widget(const char* _label,
		const sf::Vector2f& _size)
		: m_label(_label)
		, m_size(_size)
	{
	}
	virtual ~Widget() {}

	virtual void accept(Visitor& _visitor) = 0;
	virtual void accept(ConstVisitor& _visitor) const = 0;

	const char* getLabel() const { return m_label; }
	const sf::Vector2f& getTopLeft() const { return m_topLeft; }
	void setTopLeft(const sf::Vector2f& _value) { m_topLeft = _value; }
	const sf::Vector2f& getSize() const { return m_size; }

	virtual void handleMousePressedEvent(const sf::Vector2f& _mousePosition) const {}
	virtual void handleMouseDragEvent(const sf::Vector2f& _mousePosition) const {}
	virtual void handleClick() const {}
	virtual void setup() {}

protected:
	const char* m_label{ nullptr };

	sf::Vector2f	m_topLeft{ 0,0 };
	sf::Vector2f	m_size{ 0,0 };
};

//---------------------------------------------------------------------------------
class Button : public Widget
{
public:
	Button(	const char* _label, const sf::Vector2f& _size,
			std::function<void()> _onPressed)
		: Widget(_label, _size), m_onPressed(_onPressed)
	{
	}

	virtual void accept(Visitor& _visitor) override;
	virtual void accept(ConstVisitor& _visitor) const override;

	virtual void handleClick() const override { m_onPressed(); }

private:
	std::function<void()> m_onPressed;
};

//---------------------------------------------------------------------------------
template<typename T>
class Slider : public Widget
{
private:
	using Getter = std::function<T()>;
	using Setter = std::function<void(T)>;

public:
	Slider(const char* _label, const sf::Vector2f& _size,
		T _minValue, T _maxValue, Getter _getter, Setter _setter)
		: Widget(_label, _size)
		, m_minValue(_minValue), m_maxValue(_maxValue)
		, m_getter(_getter), m_setter(_setter)
	{
	}

	virtual void accept(Visitor& _visitor) override { _visitor.visit(*this); }
	virtual void accept(ConstVisitor& _visitor) const override { _visitor.visit(*this); }

	virtual void handleMousePressedEvent(const sf::Vector2f& _mousePosition) const override;
	virtual void handleMouseDragEvent(const sf::Vector2f& _mouseDelta) const override;

	T getValue() const { return m_getter(); }
	T getMaxValue() const { return m_maxValue; }
	T getMinValue() const { return m_minValue; }

	float getRatio() const { return (m_getter() - m_minValue) / (float)(m_maxValue - m_minValue); }

private:
	Getter m_getter;
	Setter m_setter;

	T m_minValue;
	T m_maxValue;
};

//---------------------------------------------------------------------------------
class Panel : public Widget
{
public:
	Panel(const char* _label, const sf::Vector2f& _topLeft)
		: Widget(_label, {})
	{
		m_topLeft = _topLeft;
		m_size = { 0, 30 };
	}
	~Panel()
	{
		for (Widget* child : m_children)
			delete child;
	}

	virtual void accept(Visitor& _visitor) override;
	virtual void accept(ConstVisitor& _visitor) const override;

	void pushChild(Widget& _widget);
	void removeChild(Widget& _widget);

	const std::vector<Widget*>& getChildren() const { return m_children; }
	std::vector<Widget*>& getChildren() { return m_children; }
	virtual void setup() override;

private:
	std::vector<Widget*> m_children;
};


//---------------------------------------------------------------------------------
// Template implementations
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
template<typename T>
void Slider<T>::handleMousePressedEvent(const sf::Vector2f& _mousePosition) const
{
	handleMouseDragEvent(_mousePosition);
}

//---------------------------------------------------------------------------------
template<typename T>
void Slider<T>::handleMouseDragEvent(const sf::Vector2f& _mousePosition) const
{
	const float ratio = (_mousePosition.x - m_topLeft.x) / (float)m_size.x;
	T value = m_minValue + ratio * (m_maxValue - m_minValue);
	value = std::clamp(value, m_minValue, m_maxValue);
	m_setter(value);
}

class Label : public Widget
{
public:
	using Callback = std::function<void(std::string&)>;

	Label(const char* _label, Callback _callBack)
		: Widget(_label, {0,0})
	{
	}

	~Label()
	{
	}

	virtual void accept(Visitor& _visitor) override;
	virtual void accept(ConstVisitor& _visitor) const override;

	void AssignedCalback(Callback _callBack)
	{
		m_callback = _callBack;
	}

private:
	Callback m_callback;
};