#pragma once

#include "common.h"

//---------------------------------------------------------------------------------
class Shape
{
public:
    Shape(const sf::Vector2f& _topLeft) : m_topLeft(_topLeft) {}
    virtual ~Shape() {}

    virtual void                draw            (sf::RenderWindow& _window, const sf::Color& _fillColor, const sf::Color& _outlineColor, float _fillRate = 1.f) const = 0;
    virtual bool                isPointInside   (const sf::Vector2f& _position) const = 0;
    virtual sf::Vector2f        computeCenter   () const = 0;
    virtual const sf::Vector2f& getTopLeft      () const { return m_topLeft;}
    virtual sf::Vector2f        getSize         () const = 0;

protected:
    sf::Vector2f m_topLeft{ 0.f, 0.f };
};

//---------------------------------------------------------------------------------
class Circle : public Shape
{
public:
    Circle( sf::Vector2f _topLeft, float _radius)
        : Shape(_topLeft)
        , m_radius(_radius) 
    {}

    virtual void draw(sf::RenderWindow& _window, const sf::Color& _fillColor, const sf::Color& _outlineColor, float _fillRate) const override;
    virtual bool isPointInside(const sf::Vector2f& _mousePosition) const override;
    virtual sf::Vector2f computeCenter() const override;
    virtual sf::Vector2f getSize() const override;

private:
    float        m_radius;
};

//---------------------------------------------------------------------------------
class Rectangle : public Shape
{
public:
    Rectangle(  sf::Vector2f _topLeft, 
                sf::Vector2f _size)
        : Shape(_topLeft)
        , m_size(_size)
    {}

    virtual void draw(sf::RenderWindow& _window, const sf::Color& _fillColor, const sf::Color& _outlineColor, float _fillRate) const override;
    virtual bool isPointInside(const sf::Vector2f& _mousePosition) const override;
    virtual sf::Vector2f computeCenter() const override;
    virtual sf::Vector2f getSize() const override;

protected:
    sf::Vector2f m_size;
};

//---------------------------------------------------------------------------------
class RoundedRectangle : public Rectangle
{
public:
    RoundedRectangle(   sf::Vector2f _topLeft,
                        sf::Vector2f _size)
        : Rectangle(_topLeft, _size)
    {}

    virtual void draw(sf::RenderWindow& _window, const sf::Color& _fillColor, const sf::Color& _outlineColor, float _fillRate) const override;

private:
    sf::ConvexShape buildConvexShape(float _widthScale) const;
};