#include "Shape.h"

//---------------------------------------------------------------------------------
void Circle::draw(sf::RenderWindow& _window, const sf::Color& _fillColor, const sf::Color& _outlineColor, float _fillRate) const
{
    float actualRadius = m_radius * _fillRate;
	sf::CircleShape sfCircle(actualRadius);
    sfCircle.setFillColor(_fillColor);
	sfCircle.setOutlineColor(_outlineColor);

    sf::Vector2f position = m_topLeft + (m_radius - actualRadius) * sf::Vector2f(1.f, 1.f);
	sfCircle.setPosition(position.x, position.y);
	_window.draw(sfCircle);
}

//---------------------------------------------------------------------------------
bool Circle::isPointInside(const sf::Vector2f& _mousePosition) const
{ 
    const sf::Vector2f center = computeCenter();
    const sf::Vector2f centerToMousePosition = _mousePosition - center;
    const float distance = sqrt(centerToMousePosition.x * centerToMousePosition.x + centerToMousePosition.y * centerToMousePosition.y);
    return distance < m_radius;
}

//---------------------------------------------------------------------------------
sf::Vector2f Circle::computeCenter() const
{
    return sf::Vector2f(m_topLeft.x, m_topLeft.y) + sf::Vector2f(m_radius, m_radius);
}

//---------------------------------------------------------------------------------
sf::Vector2f Circle::getSize() const
{
    return 2.f * m_radius * sf::Vector2f(1.f, 1.f);
}

//---------------------------------------------------------------------------------
void Rectangle::draw(sf::RenderWindow& _window, const sf::Color& _fillColor, const sf::Color& _outlineColor, float _fillRate) const
{
	sf::RectangleShape sfRectangle(sf::Vector2f(_fillRate * m_size.x, m_size.y));
    sfRectangle.setFillColor(_fillColor);
	sfRectangle.setOutlineColor(_outlineColor);
    sfRectangle.setOutlineThickness(3);
	sfRectangle.setPosition(m_topLeft.x, m_topLeft.y);
	_window.draw(sfRectangle);
}

//---------------------------------------------------------------------------------
bool Rectangle::isPointInside(const sf::Vector2f& _position) const
{
    const sf::Vector2f bottomRight = m_topLeft + m_size;
    return _position.x >= m_topLeft.x && _position.x <= bottomRight.x
        && _position.y >= m_topLeft.y && _position.y <= bottomRight.y;
}

//---------------------------------------------------------------------------------
sf::Vector2f Rectangle::computeCenter() const
{
    return sf::Vector2f(m_topLeft.x, m_topLeft.y) + 0.5f * sf::Vector2f(m_size.x, m_size.y);
}

//---------------------------------------------------------------------------------
sf::Vector2f Rectangle::getSize() const
{
    return m_size;
}

//---------------------------------------------------------------------------------
void RoundedRectangle::draw(sf::RenderWindow& _window, const sf::Color& _fillColor, const sf::Color& _outlineColor, float _fillRate) const
{
    sf::ConvexShape convexShape = buildConvexShape(_fillRate);
    convexShape.setFillColor(_fillColor);
    convexShape.setOutlineColor(_outlineColor);
    _window.draw(convexShape);
}

//---------------------------------------------------------------------------------
sf::ConvexShape RoundedRectangle::buildConvexShape(float _widthScale) const
{
    sf::ConvexShape convexShape;
    const unsigned int cornerPointsCount = 4;
    const float cornerRadius = 10;
    for (unsigned i = 0; i < cornerPointsCount * 4; ++i)
    {
        const float deltaAngle = 90.0f / (cornerPointsCount - 1);
        const unsigned int centerIndex = i / cornerPointsCount;
        sf::Vector2f center = [&]() -> sf::Vector2f 
        {
            switch (centerIndex)
            {
                case 0: return sf::Vector2f(_widthScale * m_size.x - cornerRadius,  cornerRadius );             break;
                case 1: return sf::Vector2f( cornerRadius,                          cornerRadius );             break;
                case 2: return sf::Vector2f( cornerRadius,                          m_size.y - cornerRadius );  break;
                case 3: return sf::Vector2f(_widthScale * m_size.x - cornerRadius,  m_size.y - cornerRadius );  break;
            }
        }();
        convexShape.setPointCount(cornerPointsCount * 4);

        sf::Vector2f cornerPoint(   +cornerRadius * cos(deltaAngle * (i - centerIndex) * PI / 180.f) + center.x,
                                    -cornerRadius * sin(deltaAngle * (i - centerIndex) * PI / 180.f) + center.y);
        convexShape.setPoint(i, cornerPoint);
    }
    convexShape.setPosition(m_topLeft.x, m_topLeft.y);
    return convexShape;
}