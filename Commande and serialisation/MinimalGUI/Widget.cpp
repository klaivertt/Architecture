#include "Widget.h"
#include "Visitor.h"

//---------------------------------------------------------------------------------
void Panel::pushChild(Widget& _widget)
{
    m_children.push_back(&_widget);
    m_size.x = std::max(_widget.getSize().x + 2 * 5, m_size.x);
    m_size.y += _widget.getSize().y + 5;
}

//---------------------------------------------------------------------------------
void Panel::removeChild(Widget& _widget)
{
    for (unsigned int i = 0u; i < m_children.size(); ++i)
    {
        if (m_children[i] == &_widget)
        {
            m_children.erase(m_children.begin() + i);
            break;
		}
        else
        {
            m_size.x = std::max(m_children[i]->getSize().x + 2 * 5, m_size.x);
        }
    }
    m_size.y -= _widget.getSize().y + 5;
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

//---------------------------------------------------------------------------------
void Button::accept(Visitor& _visitor)
{
    _visitor.visit(*this);
}
//---------------------------------------------------------------------------------
void Button::accept(ConstVisitor& _visitor) const
{
    _visitor.visit(*this);
}

//---------------------------------------------------------------------------------
void Label::accept(Visitor& _visitor)
{
    _visitor.visit(*this);
}
//---------------------------------------------------------------------------------
void Label::accept(ConstVisitor& _visitor) const
{
    _visitor.visit(*this);
}

//---------------------------------------------------------------------------------
void Panel::accept(Visitor& _visitor)
{
    _visitor.visit(*this);
}
//---------------------------------------------------------------------------------
void Panel::accept(ConstVisitor& _visitor) const
{
    _visitor.visit(*this);
}
