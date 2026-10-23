#include "VisitorImplem.h"

//---------------------------------------------------------------------------------
bool isPointInside(const sf::Vector2f& _position, const Widget& _widget)
{
	const sf::Vector2f bottomRight = _widget.getTopLeft() + _widget.getSize();
	return _position.x >= _widget.getTopLeft().x && _position.x <= bottomRight.x
		&& _position.y >= _widget.getTopLeft().y && _position.y <= bottomRight.y;
}

//---------------------------------------------------------------------------------
void Visitor::visit(Panel& _panel)
{
	for (Widget* child : _panel.getChildren())
		child->accept(*this);
}

//---------------------------------------------------------------------------------
void ConstVisitor::visit(const Panel& _panel)
{
	for (const Widget* child : _panel.getChildren())
		child->accept(*this);
}

//---------------------------------------------------------------------------------
void FindWidgetVisitor::visit(Button& _button)
{
	if (isPointInside(m_position, _button))
		m_found = &_button;
}

//---------------------------------------------------------------------------------
void FindWidgetVisitor::visit(Slider<unsigned>& _slider)
{
	if (isPointInside(m_position, _slider))
		m_found = &_slider;
}

//---------------------------------------------------------------------------------
void FindWidgetVisitor::visit(Slider<float>& _slider)
{
	if (isPointInside(m_position, _slider))
		m_found = &_slider;
}

//---------------------------------------------------------------------------------
void FindWidgetVisitor::visit(Label& _label)
{
	if (isPointInside(m_position, _label))
		m_found = &_label;
}

//---------------------------------------------------------------------------------
void FindWidgetVisitor::visit(Panel& _panel)
{
	for (Widget* child : _panel.getChildren())
	{
		child->accept(*this);
		if (m_found)
			return;
	}
}

//---------------------------------------------------------------------------------
static void drawText(sf::RenderTarget& _renderTarget, const sf::Font& _font, const char* _label, const sf::Vector2f& _position, const sf::Color& _color, bool _bold = false)
{
	sf::Text labelText;
	labelText.setFont(_font);
	labelText.setString(_label);
	labelText.setCharacterSize(13);
	labelText.setFillColor(_color);
	labelText.setPosition(_position.x + 5.f, _position.y);
	if (_bold)
		labelText.setStyle(sf::Text::Bold);
	_renderTarget.draw(labelText);
}

//---------------------------------------------------------------------------------
void DrawVisitor::visit(const Button& _button)
{
	sf::RectangleShape r = createRectangleShape(_button);
	m_renderTarget.draw(r);

	const sf::Vector2f topRight = _button.getTopLeft() + sf::Vector2f(_button.getSize().x, 0.f);
	drawText(m_renderTarget, m_font, _button.getLabel(), { topRight.x + 5.f, topRight.y }, getTextColor(_button));
}

//---------------------------------------------------------------------------------
void DrawVisitor::visit(const Panel& _panel)
{
	sf::RectangleShape r = createRectangleShape(_panel);
	m_renderTarget.draw(r);
	drawText(m_renderTarget, m_font, _panel.getLabel(), { _panel.getTopLeft().x + 5.f, _panel.getTopLeft().y + 5.f }, getTextColor(_panel), true);
	ConstVisitor::visit(_panel);
}

//---------------------------------------------------------------------------------
void DrawVisitor::visit(const Slider<unsigned>& _slider)
{
	{
		sf::RectangleShape r = createRectangleShape(_slider);
		r.setFillColor(sf::Color::Transparent);
		m_renderTarget.draw(r);
	}
	{
		sf::RectangleShape r = createRectangleShape(_slider);
		r.setSize({ _slider.getSize().x * _slider.getRatio(), _slider.getSize().y });
		m_renderTarget.draw(r);
	}

	const std::string text = std::format("{}: {}", _slider.getLabel(), _slider.getValue());
	drawText(m_renderTarget, m_font, text.c_str(), { _slider.getTopLeft().x + 5.f, _slider.getTopLeft().y }, getTextColor(_slider));
}

//---------------------------------------------------------------------------------
void DrawVisitor::visit(const Slider<float>& _slider)
{
	{
		sf::RectangleShape r = createRectangleShape(_slider);
		r.setFillColor(sf::Color::Transparent);
		m_renderTarget.draw(r);
	}
	{
		sf::RectangleShape r = createRectangleShape(_slider);
		r.setSize({ _slider.getSize().x * _slider.getRatio(), _slider.getSize().y });
		m_renderTarget.draw(r);
	}

	const std::string text = std::format("{}: {}", _slider.getLabel(), _slider.getValue());
	drawText(m_renderTarget, m_font, text.c_str(), { _slider.getTopLeft().x + 5.f, _slider.getTopLeft().y }, getTextColor(_slider));
}

//---------------------------------------------------------------------------------
void DrawVisitor::visit(const Label& _label)
{
	const std::string& valueString = _label.getValueString();
	const std::string text = std::format("{}: {}", _label.getLabel(), valueString.c_str());

	sf::RectangleShape r = createRectangleShape(_label);
	m_renderTarget.draw(r);
	drawText(m_renderTarget, m_font, text.c_str(), { _label.getTopLeft().x + 5.f, _label.getTopLeft().y }, getTextColor(_label));
}

//---------------------------------------------------------------------------------
void RemoveWidgetVisitor::visit(Panel& _panel)
{
	_panel.removeChild(*m_target);
	Visitor::visit(_panel);
}