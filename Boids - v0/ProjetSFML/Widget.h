#pragma once

#include "common.h"
#include <vector>
#include <cstdlib>

// Helper: pick a random color from a palette
inline sf::Color pickRandomFillColor(const std::vector<sf::Color>& _palette)
{
	if (_palette.empty()) return sf::Color::White;
	int idx = std::rand() % (int)_palette.size();
	return _palette[idx];
}

static void drawText(sf::RenderTarget& _renderTarget, const sf::Font& _font, const char* _label, const sf::Vector2f& _position, bool _bold = false)
{
	sf::Text labelText;
	labelText.setFont(_font);
	labelText.setString(_label);
	labelText.setCharacterSize(13);
	labelText.setFillColor(sf::Color::White);
	labelText.setPosition(_position.x + 5.f, _position.y);

	if (_bold)
		labelText.setStyle(sf::Text::Bold);

	_renderTarget.draw(labelText);
}

//---------------------------------------------------------------------------------
class Widget
{
public:
	Widget(const char* _label,
		const sf::Vector2f& _size,
		sf::Color _fillColor, sf::Color _outlineColor)
		: m_label(_label)
		, m_size(_size)
		, m_fillColor(_fillColor)
		, m_outlineColor(_outlineColor)
	{
	}
	virtual ~Widget() {}

	const sf::Color& getFillColor() const { return m_fillColor; }
	const sf::Color& getOutlineColor() const { return m_outlineColor; }

	const char* getLabel() const { return m_label; }
	const sf::Vector2f& getTopLeft() const { return m_topLeft; }
	void setTopLeft(const sf::Vector2f& _value) { m_topLeft = _value; }
	const sf::Vector2f& getSize() const { return m_size; }

	bool isPointInside(const sf::Vector2f& _point) const;

	virtual void handleMousePressedEvent(const sf::Event::MouseButtonEvent& _event, const sf::Vector2f& _mousePosition) = 0;

	virtual void HandleMouseRelease() = 0;

	virtual void Update(const sf::Vector2f& _mousePosition) = 0;
	virtual void draw(sf::RenderTarget& _renderTarget, const sf::Font& _font) const = 0;
	virtual void setup() {}

protected:
	const char* m_label{ nullptr };

	sf::Vector2f	m_topLeft{ 0,0 };
	sf::Vector2f	m_size{ 0,0 };

	sf::Color		m_fillColor;
	sf::Color		m_outlineColor;
};

//---------------------------------------------------------------------------------
class Button : public Widget
{
private:
	using Callback = std::function<void(void)>;
public:
	Button(const char* _label, const sf::Vector2f& _size,
		sf::Color _fillColor, sf::Color _outlineColor)
		: Widget(_label, _size, _fillColor, _outlineColor)
	{
	}

	virtual void Update(const sf::Vector2f& _mousePosition) override
	{
	}

	virtual void handleMousePressedEvent(const sf::Event::MouseButtonEvent& _event, const sf::Vector2f& _mousePosition) override;

	virtual void HandleMouseRelease() override
	{
	}

	void SetCallBack(Callback _callBack)
	{
		m_callback = std::move(_callBack);
	}



	virtual void draw(sf::RenderTarget& _renderTarget, const sf::Font& _font) const override;

private:
	virtual const sf::Color& getButtonFillColor() const { return m_fillColor; }

	Callback m_callback;
};

//---------------------------------------------------------------------------------
class CheckBox : public Widget
{
private:
	using Callback = std::function<void(bool)>;
public:
	CheckBox(const char* _label,
		const sf::Vector2f& _size,
		sf::Color _fillColor, sf::Color _outlineColor)
		: Widget(_label, _size, _fillColor, _outlineColor)
	{
	}

	bool getValue() const { return m_value; }

	virtual void Update(const sf::Vector2f& _mousePosition) override
	{

	}

	void SetCallBack(Callback _callBack)
	{
		m_callback = std::move(_callBack);
	}

	virtual void HandleMouseRelease() override
	{
	}

	virtual void draw(sf::RenderTarget& _renderTarget, const sf::Font& _font) const override;
	virtual void handleMousePressedEvent(const sf::Event::MouseButtonEvent& _event, const sf::Vector2f& _mousePosition) override;

private:
	bool m_value{ false };

	Callback m_callback;
};

//---------------------------------------------------------------------------------
template<typename T>
class Slider : public Widget
{
private:
	using Callback = std::function<void(T)>;
public:
	Slider(const char* _label, const sf::Vector2f& _size,
		sf::Color _fillColor, sf::Color _outlineColor,
		T _minValue, T _maxValue, T _initialValue)
		: Widget(_label, _size, _fillColor, _outlineColor)
		, m_minValue(_minValue), m_maxValue(_maxValue), m_value(_initialValue)
	{
	}

	virtual void Update(const sf::Vector2f& _mousePosition) override
	{
		if (m_pressed)
		{
			float ratio = (_mousePosition - m_topLeft).x / (float)m_size.x;
			ratio = std::clamp(ratio, 0.f, 1.f);
			m_value = m_minValue + ratio * (m_maxValue - m_minValue);
		}
	}

	void SetCallBack(Callback _callBack)
	{
		m_callback = std::move(_callBack);
	}

	virtual void draw(sf::RenderTarget& _renderTarget, const sf::Font& _font) const override
	{
		sf::RectangleShape r;
		{
			r.setFillColor(sf::Color::Black);
			r.setOutlineColor(m_outlineColor);
			r.setOutlineThickness(1);
			r.setPosition(m_topLeft);
			r.setSize(m_size);
			_renderTarget.draw(r);
		}
		{
			r.setFillColor(m_fillColor);
			r.setOutlineColor(m_outlineColor);
			r.setPosition(m_topLeft);
			r.setSize({ m_size.x * getRatio(), m_size.y });
			_renderTarget.draw(r);
		}

		std::stringstream text;
		text << m_label << ": " << m_value;
		drawText(_renderTarget, _font, text.str().c_str(), m_topLeft);
	}

	virtual void handleMousePressedEvent(const sf::Event::MouseButtonEvent& _event, const sf::Vector2f& _mousePosition) override
	{
		m_pressed = true;
	}

	virtual void HandleMouseRelease() override
	{
		if (m_callback)
		{
			m_callback(m_value);
		}
		m_pressed = false;
	}

	float getValue() const { return m_value; }
	float getMaxValue() const { return m_maxValue; }
	float getMinValue() const { return m_minValue; }

private:
	float getRatio() const { return float(m_value - m_minValue) / float(m_maxValue - m_minValue); }

	T m_value{};
	T m_minValue{};
	T m_maxValue{};

	bool m_pressed{ false };

	Callback m_callback;
};

//---------------------------------------------------------------------------------
class Panel : public Widget
{
public:
	Panel(const char* _label, const sf::Vector2f& _topLeft,
		sf::Color _fillColor, sf::Color _outlineColor)
		: Widget(_label, {}, _fillColor, _outlineColor)
	{
		m_topLeft = _topLeft;
		m_size = { 0, 30 };
	}
	~Panel()
	{
		for (Widget* child : m_children)
			delete child;
	}

	virtual void handleMousePressedEvent(const sf::Event::MouseButtonEvent& _event, const sf::Vector2f& _mousePosition) override;
	virtual void HandleMouseRelease() override;

	virtual void draw(sf::RenderTarget& _renderTarget, const sf::Font& _font) const override;
	virtual void Update(const sf::Vector2f& _mousePosition) override;
	void pushChild(Widget& _widget);
	std::vector<Widget*>& getChildren() { return m_children; }
	virtual void setup() override;

private:
	std::vector<Widget*> m_children;
};