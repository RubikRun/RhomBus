#include "RhombusShape.h"

RhombusShape::RhombusShape()
    : _horizontal(0), _vertical(0), _center(0, 0),
    ConvexShape(0)
{}

RhombusShape::RhombusShape(
    float horizontal,
    float vertical,
    sf::Vector2f const& center)
        : _horizontal(horizontal),
        _vertical(vertical),
        _center(center),
        ConvexShape(4)
{
    UpdateVertices();
}

sf::Vector2f RhombusShape::GetPosition() const
{
    return _center;
}

void RhombusShape::SetPosition(
    sf::Vector2f const& center)
{
    _center = center;
    UpdateVertices();
}

void RhombusShape::Move(
    sf::Vector2f const& delta)
{
    SetPosition(_center + delta);
}

float RhombusShape::GetHorizontal() const
{
    return _horizontal;
}

void RhombusShape::SetHorizontal(float horizontal)
{
    _horizontal = horizontal;
    UpdateVertices();
}

void RhombusShape::ChangeHorizontal(float delta)
{
    SetHorizontal(_horizontal + delta);
}

float RhombusShape::GetVertical() const
{
    return _vertical;
}

void RhombusShape::SetVertical(float vertical)
{
    _vertical = vertical;
    UpdateVertices();
}

void RhombusShape::ChangeVertical(float delta)
{
    SetVertical(_vertical + delta);
}

void RhombusShape::UpdateVertices()
{
    ConvexShape::setPoint(0, {_center.x - _horizontal / 2, _center.y});
    ConvexShape::setPoint(1, {_center.x, _center.y - _vertical / 2});
    ConvexShape::setPoint(2, {_center.x + _horizontal / 2, _center.y});
    ConvexShape::setPoint(3, {_center.x, _center.y + _vertical / 2});
}