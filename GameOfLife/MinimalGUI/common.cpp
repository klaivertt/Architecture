#include "common.h"

bool CollisionRectPoint(sf::FloatRect& _rect, sf::Vector2f& _vec)
{
    return _rect.contains(_vec);
}

int Random(int _min, int _max)
{
    return _min + rand() % (_max - _min);
}

void CenterTextOnShape(sf::Text& _text, const sf::Shape& _shape)
{
    sf::FloatRect textBound = _text.getLocalBounds();
    _text.setOrigin(textBound.left + textBound.width / 2.f, textBound.top + textBound.height / 2.f);

    sf::FloatRect shapeBound = _shape.getGlobalBounds();
    _text.setPosition(shapeBound.left + shapeBound.width / 2.f, shapeBound.top + shapeBound.height / 2.f);
}
