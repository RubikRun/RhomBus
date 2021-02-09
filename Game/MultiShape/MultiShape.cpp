#include "MultiShape.h"

MultiShape::MultiShape()
{}

MultiShape::MultiShape(
    std::vector<sf::Shape*> const& components)
    : _components(components)
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

void MultiShape::Draw(
    sf::RenderWindow& window)
{
    for (sf::Shape* component : _components)
    {
        window.draw(*component);
    }
}

MultiShape::~MultiShape()
{
    for (sf::Shape* component : _components)
    {
        delete component;
    }
}