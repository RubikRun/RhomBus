#include "RhomBusEntity.h"

#include "../RhombusShape/RhombusShape.h"

#include <iostream>

namespace
{

auto constexpr TYRE_TEXTURE_FILE = "Textures/RhomBus-tyre.png";
auto constexpr BODY_TEXTURE_FILE = "Textures/RhomBus-body.png";

} // namespace

namespace RhomBus
{

RhomBusEntity::RhomBusEntity(
    sf::Vector2f const& position
)
    : _size(RHOMBUS_DEFAULT_SIZE),
    MultiShape(CreateComponents(RHOMBUS_DEFAULT_SIZE), position)
{
    LoadTyreTexture();
    SetTextureToTyres(&_tyreTexture);

    LoadBodyTexture();
    SetTextureToBody(&_bodyTexture);
}

RhomBusEntity::RhomBusEntity(
    float size,
    sf::Vector2f const& position)
        : _size(size),
        MultiShape(CreateComponents(size), position)
{
    LoadTyreTexture();
    SetTextureToTyres(&_tyreTexture);

    LoadBodyTexture();
    SetTextureToBody(&_bodyTexture);
}

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

    float const WINDOW_OFFSET = 30.f;
    float const WINDOW_HEIGHT = 65.f;

    sf::ConvexShape* leftWindow = new sf::ConvexShape(3);
    leftWindow->setPoint(0, {- size / 6 - WINDOW_OFFSET / 2, 0.f});
    leftWindow->setPoint(1, {-size / 2 + WINDOW_OFFSET, 0.f});
    leftWindow->setPoint(2, {- size / 6 - WINDOW_OFFSET / 2, -WINDOW_HEIGHT});
    leftWindow->setFillColor(sf::Color::Black);

    sf::ConvexShape* middleWindow = new sf::ConvexShape(4);
    middleWindow->setPoint(0, {- size / 6 + WINDOW_OFFSET / 2, 0.f});
    middleWindow->setPoint(1, {size / 6 - WINDOW_OFFSET / 2, 0.f});
    middleWindow->setPoint(2, {size / 6 - WINDOW_OFFSET / 2, -WINDOW_HEIGHT});
    middleWindow->setPoint(3, {- size / 6 + WINDOW_OFFSET / 2, -WINDOW_HEIGHT});
    middleWindow->setFillColor(sf::Color::Black);

    sf::ConvexShape* rightWindow = new sf::ConvexShape(3);
    rightWindow->setPoint(0, {size / 6 + WINDOW_OFFSET / 2, 0.f});
    rightWindow->setPoint(1, {size / 2 - WINDOW_OFFSET, 0.f});
    rightWindow->setPoint(2, {size / 6 + WINDOW_OFFSET / 2, -WINDOW_HEIGHT});
    rightWindow->setFillColor(sf::Color::Black);

    // Return vector of the 3 components
    return {
        body,
        leftTyre,
        rightTyre,
        leftWindow,
        middleWindow,
        rightWindow
    };
}

void RhomBusEntity::LoadTyreTexture()
{
    if (!_tyreTexture.loadFromFile(TYRE_TEXTURE_FILE))
    {
        std::cout << "Error: Cannot load RhomBus tyre texture." << std::endl;
    }
}

void RhomBusEntity::SetTextureToTyres(sf::Texture* texture)
{
    MultiShape::operator[](1)->setTexture(texture);
    MultiShape::operator[](2)->setTexture(texture);
}

void RhomBusEntity::LoadBodyTexture()
{
    if (!_bodyTexture.loadFromFile(BODY_TEXTURE_FILE))
    {
        std::cout << "Error: Cannot load RhomBus body texture." << std::endl;
    }
}

void RhomBusEntity::SetTextureToBody(sf::Texture* texture)
{
    MultiShape::operator[](0)->setTexture(texture);
}

float const RhomBusEntity::RHOMBUS_DEFAULT_SIZE = 500.f;
float const RhomBusEntity::RHOMBUS_SMALL_DIAGONAL = 0.5f;
float const RhomBusEntity::RHOMBUS_TYRE_RADIUS = 0.12f;
float const RhomBusEntity::RHOMBUS_GROUND_HEIGHT = 0.30f;
float const RhomBusEntity::RHOMBUS_TYRE_WIDE_DIST = 0.4f;

} // namespace RhomBus