#include "CheckBox.h"

CheckBox::CheckBox(sf::Shape* _shape, sf::Text* _text)
{
    this->m_shape = _shape;
    m_isActive = false;
    m_isOver = false;
    m_isPressed = false;
    m_shape->setOutlineColor(sf::Color(100, 100, 100));
    m_shape->setOutlineThickness(5.f);

    m_text = _text;
}

CheckBox::~CheckBox()
{
    delete this->m_shape;
    if (m_text)
    {
        delete m_text;
    }
}

void CheckBox::Update(const sf::Vector2i& _pos)
{
    sf::Color fillC = m_isActive ? COLOR_G : COLOR_R;

    this->m_shape->setFillColor(m_isOver ? fillC + sf::Color(20, 20, 20) : fillC);

    //isActive = false;
}

void CheckBox::Draw(sf::RenderTarget& _render)
{
    _render.draw(*m_shape);
    
    if (m_text != nullptr)
    {
        _render.draw(*m_text);
    }
}


void CheckBox::SetOnToggle(Callback _cb)
{
    m_onToggle = std::move(_cb);
}

const sf::Vector2f& CheckBox::GetSize(void)
{
    sf::FloatRect bound = m_shape ? m_shape->getLocalBounds() : sf::FloatRect();
    return sf::Vector2f(bound.width, bound.height);
}

void CheckBox::SetPosition(const sf::Vector2f& _pos)
{
    if (m_shape)
    {
        float xOffset = m_shape->getOutlineThickness();
        m_shape->setPosition(_pos.x + xOffset, _pos.y);

        if (m_text) 
        {
            CenterTextOnShape(*m_text, *m_shape);
        }
    }
}

void CheckBox::Pressed(const sf::Mouse::Button& _button, const sf::Vector2i& _pos)
{
    CheckCollision(_pos);
    if (m_isOver)
    {
        if (_button == sf::Mouse::Button::Left)
        {
            m_isPressed = true;
        }
        else if (_button == sf::Mouse::Button::Right)
        {
            if (m_owner)
            {
                m_owner->Delete(this);
            }
        }
    }
}

void CheckBox::Released()
{
    if (m_isPressed && m_isOver)
    {
        m_isActive = !m_isActive;
        if (m_onToggle)
        {
            m_onToggle(m_isActive);
        }
    }
    m_isPressed = false;
}

void CheckBox::SetOwner(Widget* _owner)
{
    m_owner = _owner;
}

void CheckBox::CheckCollision(const sf::Vector2i& const _pos)
{
    sf::FloatRect floatR = this->m_shape->getGlobalBounds();
    sf::Vector2f vec = sf::Vector2f(_pos);
    m_isOver = CollisionRectPoint(floatR, vec);
    //std::cout << "x : " << vec.x << "y : " << vec.y << std::endl;
    //std::cout << (isOver ? "collision" : "No collision") << std::endl;
}
