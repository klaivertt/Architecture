#include "WidgetManager.h"

//---------------------------------------------------------------------------------
SINGLETON_DEFINITION(WidgetManager);

//---------------------------------------------------------------------------------
void WidgetManager::onMouseEvent(sf::Event& _mouseEvent)
{
	if (_mouseEvent.type == sf::Event::MouseButtonPressed)
	{
		sf::Vector2f mousePosition(static_cast<float>(_mouseEvent.mouseButton.x), static_cast<float>(_mouseEvent.mouseButton.y));
		m_rootPanel.handleMousePressedEvent(_mouseEvent.mouseButton ,mousePosition);
	}
	
	if (_mouseEvent.type == sf::Event::MouseButtonReleased)
	{
		m_rootPanel.HandleMouseRelease();
	}
}

void WidgetManager::Update(const sf::Vector2f& _mousePosition)
{
	m_rootPanel.Update(_mousePosition);
}

//---------------------------------------------------------------------------------
void WidgetManager::draw(sf::RenderTarget& _renderTarget, const sf::Font& _font) const
{
	m_rootPanel.draw(_renderTarget, _font);
}