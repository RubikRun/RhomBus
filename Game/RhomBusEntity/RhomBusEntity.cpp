#include "RhomBusEntity.h"

#include "../RhombusShape/RhombusShape.h"

namespace RhomBus
{

RhomBusEntity::RhomBusEntity(
    sf::Vector2f const& position
)
    : _size(RHOMBUS_DEFAULT_SIZE),
    MultiShape(CreateComponents(RHOMBUS_DEFAULT_SIZE), position)
{}

RhomBusEntity::RhomBusEntity(
    float size,
    sf::Vector2f const& position)
        : _size(size),
        MultiShape(CreateComponents(size), position)
{}

float RhomBusEntity::GetHorizontalSize() const
{
    return _size;
}

float RhomBusEntity::GetVerticalSize() const
{
    return GetCenterHeight() + RHOMBUS_SMALL_DIAGONAL * _size / 2.f;
}

float RhomBusEntity::GetCenterHeight() const
{
    return RHOMBUS_GROUND_HEIGHT * _size;
}

sf::Vector2f RhomBusEntity::GetVelocity() const
{
    return _velocity;
}

void RhomBusEntity::ApplyVelocityForce(
    sf::Vector2f const& velocityForce)
{
    _velocity += velocityForce;
}

void RhomBusEntity::Update()
{
    MultiShape::Move(_velocity);
}

sf::Vector2f RhomBusEntity::GetNextPosition() const
{
    return MultiShape::GetPosition() + _velocity;
}

std::vector<sf::Shape*>
RhomBusEntity::CreateComponents(float size)
{
    // Construct body - a rhombus shape
    RhombusShape* body = new RhombusShape(
        size,
        RHOMBUS_SMALL_DIAGONAL * size
    );

    float const tyreRadius = RHOMBUS_TYRE_RADIUS * size;

    // Construct left tyre
    sf::CircleShape* leftTyre = new sf::CircleShape(
        tyreRadius);
    leftTyre->setPosition({
        -(RHOMBUS_TYRE_WIDE_DIST * size / 2) - 2 * tyreRadius,
        RHOMBUS_GROUND_HEIGHT * size - 2 * tyreRadius
    });

    // Construct right tyre
    sf::CircleShape* rightTyre = new sf::CircleShape(
        tyreRadius);
    rightTyre->setPosition({
        RHOMBUS_TYRE_WIDE_DIST * size / 2,
        RHOMBUS_GROUND_HEIGHT * size - 2 * tyreRadius
    });

    // Return vector of the 3 components
    return {
        body,
        leftTyre,
        rightTyre
    };
}

float const RhomBusEntity::RHOMBUS_DEFAULT_SIZE = 500.f;
float const RhomBusEntity::RHOMBUS_SMALL_DIAGONAL = 0.5f;
float const RhomBusEntity::RHOMBUS_TYRE_RADIUS = 0.12f;
float const RhomBusEntity::RHOMBUS_GROUND_HEIGHT = 0.35f;
float const RhomBusEntity::RHOMBUS_TYRE_WIDE_DIST = 0.4f;

} // namespace RhomBus