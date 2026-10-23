#include "Widget.h"

//---------------------------------------------------------------------------------
bool Widget::isPointInside(const sf::Vector2f& _point) const
{
	const sf::Vector2f bottomRight = m_topLeft + m_size;
	return _point.x >= m_topLeft.x && _point.x <= bottomRight.x
		&& _point.y >= m_topLeft.y && _point.y <= bottomRight.y;
}

void Button::handleMousePressedEvent(const sf::Event::MouseButtonEvent& _event, const sf::Vector2f& _mousePosition)
{
	if (m_callback)
	{
		m_callback();
	}
}

//--------------------------------------------------------------------------------- 
void Button::draw(sf::RenderTarget& _renderTarget, const sf::Font& _font) const
{
	sf::RectangleShape r;
	r.setFillColor(m_fillColor);
	r.setOutlineColor(m_outlineColor);
	r.setOutlineThickness(1);
	r.setPosition(m_topLeft);
	r.setSize(m_size);
	_renderTarget.draw(r);

	const sf::Vector2f topRight = m_topLeft + sf::Vector2f(m_size.x, 0.f);
	drawText(_renderTarget, _font, m_label, { topRight.x + 5.f, topRight.y });
}

//---------------------------------------------------------------------------------
void CheckBox::handleMousePressedEvent(const sf::Event::MouseButtonEvent& _event, const sf::Vector2f& _mousePosition)
{
	m_value = !m_value;
	if (m_callback)
	{
		m_callback(m_value);
	}
}

//---------------------------------------------------------------------------------
void CheckBox::draw(sf::RenderTarget& _renderTarget, const sf::Font& _font) const
{
	sf::RectangleShape r;
	r.setFillColor(m_value ? m_fillColor : sf::Color::Black);
	r.setOutlineColor(m_outlineColor);
	r.setOutlineThickness(1);
	r.setPosition(m_topLeft);
	r.setSize(m_size);
	_renderTarget.draw(r);

	const sf::Vector2f topRight = m_topLeft + sf::Vector2f(m_size.x, 0.f);
	drawText(_renderTarget, _font, m_label, { topRight.x + 5.f, topRight.y });
}

//---------------------------------------------------------------------------------
void Panel::pushChild(Widget& _widget)
{
	m_children.push_back(&_widget);
	m_size.x = std::max(_widget.getSize().x + 2 * 5, m_size.x);
	m_size.y += _widget.getSize().y + 5;
}

//---------------------------------------------------------------------------------
void Panel::handleMousePressedEvent(const sf::Event::MouseButtonEvent& _event, const sf::Vector2f& _mousePosition)
{
	Widget* mousePressedWidget = nullptr;
	for (Widget* w : m_children)
	{
		if (w->isPointInside(_mousePosition))
		{
			w->handleMousePressedEvent(_event, _mousePosition);
		}
	}
}

void Panel::HandleMouseRelease()
{
	for (Widget* w : m_children)
	{
		w->HandleMouseRelease();
	}
}

//---------------------------------------------------------------------------------
void Panel::draw(sf::RenderTarget& _renderTarget, const sf::Font& _font) const
{
	sf::RectangleShape r;
	r.setFillColor(m_fillColor);
	r.setOutlineThickness(1);
	r.setOutlineColor(m_outlineColor);
	r.setPosition(m_topLeft);
	r.setSize(m_size);
	_renderTarget.draw(r);

	std::stringstream text;
	text << m_label;
	drawText(_renderTarget, _font, text.str().c_str(), m_topLeft + sf::Vector2f(0, 5), /*bold*/ true);

	for (Widget* w : m_children)
		w->draw(_renderTarget, _font);
}

void Panel::Update(const sf::Vector2f& _mousePosition)
{
	for (Widget* w : m_children)
	{
		w->Update(_mousePosition);
	}
}

//---------------------------------------------------------------------------------
void Panel::setup()
{
	float y = 30;
	for (Widget* w : m_children)
	{
		w->setTopLeft(m_topLeft + sf::Vector2f(5, y));
		w->setup();
		y += w->getSize().y + 5;
	}
}