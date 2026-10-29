#include "WidgetManager.h"
#include "VisitorImplem.h"
#include "Commande.h"
#include "CommandeManager.h"
//---------------------------------------------------------------------------------
SINGLETON_DEFINITION(WidgetManager);

//---------------------------------------------------------------------------------
bool WidgetManager::onEvent(sf::Event& _event, const sf::Window& _window)
{
	const sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(_window);
	if (isPointInside(mousePosition, m_rootPanel))
	{
		if (_event.type == sf::Event::MouseMoved)
		{
			if (m_pressed)
			{
				m_pressed->handleMouseDragEvent(mousePosition);
			}
			else
			{
				m_hovered = findWidgetAtPosition(mousePosition);
			}
		}
		else if (_event.type == sf::Event::MouseButtonPressed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_pressed = m_hovered;
				if (m_pressed)
				{
					if (Slider<float>* floatSlider = dynamic_cast<Slider<float>*>(m_pressed))
					{
						m_currentCommand = new SliderCommand(*floatSlider);
					}
					else if (Slider<unsigned>* unsignedSlider = dynamic_cast<Slider<unsigned>*>(m_pressed))
					{
						m_currentCommand = new SliderCommand(*unsignedSlider);
					}

					m_pressed->handleMousePressedEvent(mousePosition);
				}
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				if (m_hovered)
				{
					RemoveWidgetVisitor deleteVisitor(m_hovered);
					m_rootPanel.accept(deleteVisitor);
					m_rootPanel.setup();

					delete m_hovered;
					m_hovered = nullptr;
				}
			}
		}
		else if (_event.type == sf::Event::MouseButtonReleased)
		{
			if (m_pressed)
			{
				if (m_currentCommand)
				{
					CommandManager::get()->Execute(m_currentCommand);
					std::cout << "push commande" << std::endl;
					m_currentCommand = nullptr;
				}

				const Widget* released = findWidgetAtPosition(mousePosition);
				if (released == m_pressed)
				{
					m_pressed->handleClick();
				}
				m_pressed = nullptr;
			}
		}
		else if (_event.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				m_drawMode = m_drawMode == DrawMode::Pastel ? DrawMode::Matrix : DrawMode::Pastel;
			}
		}
		return true;
	}

	return false;
}

//---------------------------------------------------------------------------------
ConstVisitor* WidgetManager::createDrawVisitor(sf::RenderTarget& _renderTarget, const sf::Font& _font, const Widget* _hovered, const Widget* _pressed) const
{
	if (m_drawMode == WidgetManager::DrawMode::Matrix)
		return new MatrixDrawVisitor(_renderTarget, _font, _hovered, _pressed);
	else
		return new PastelDrawVisitor(_renderTarget, _font, _hovered, _pressed);
}

//---------------------------------------------------------------------------------
void WidgetManager::draw(sf::RenderTarget& _renderTarget, const sf::Font& _font) const
{
	ConstVisitor* drawVisitor = createDrawVisitor( _renderTarget, _font, m_hovered, m_pressed);

	m_rootPanel.accept(*drawVisitor);

	delete drawVisitor;
}

//---------------------------------------------------------------------------------
Widget* WidgetManager::findWidgetAtPosition(const sf::Vector2f& _position)
{
	FindWidgetVisitor visitor(_position);
	m_rootPanel.accept(visitor);
	return visitor.getFound();
}