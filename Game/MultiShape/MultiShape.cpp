#include "MultiShape.h"

MultiShape::MultiShape()
    : _center(0, 0)
{}

MultiShape::MultiShape(
    std::vector<sf::Shape*> const& components,
    sf::Vector2f const& center)
        : _components(components),
        _center(center)
{}

MultiShape::MultiShape(
    MultiShape const& other)
    /* initialize component vector
       with same size as in the other multishape */
    : _components(other._components.size(), nullptr)
{
    for (int i = 0; i < other._components.size(); i++)
    {
        // copy each component
        *_components[i] = *other._components[i];
    }
}

sf::Shape* MultiShape::operator[](
    unsigned index)
{
    return _components[index];
}

sf::Shape const* MultiShape::operator[](
    unsigned index) const
{
    return _components[index];
}

void MultiShape::Draw(
    sf::RenderTarget& window) const
{
    for (sf::Shape* component : _components)
    {
        // convert from relative coordinates to screen coordinates
        component->move(_center);

        window.draw(*component);

        // convert back to relative coordinates
        component->move(-_center);
    }
}

sf::Vector2f MultiShape::GetPosition() const
{
    return _center;
}

void MultiShape::SetPosition(
    sf::Vector2f const& center)
{
    _center = center;
}

void MultiShape::Move(
    sf::Vector2f const& delta)
{
    SetPosition(_center + delta);
}

MultiShape::~MultiShape()
{
    for (sf::Shape* component : _components)
    {
        delete component;
    }
}