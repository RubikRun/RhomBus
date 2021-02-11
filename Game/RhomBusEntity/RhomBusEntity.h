#pragma once

#include "../MultiShape/MultiShape.h"

namespace RhomBus
{

/* A class representing a RhomBus entity - the main entity in the RhomBus game.
   It's a Bus made of a rhombus shape and 2 circle tyres.
*/
class RhomBusEntity : public MultiShape
{

  public:

    /**
     * Creates a default RhomBus entity
     * 
     * @param[in] position
     *  position of the center of the rhombus shape
     */
    RhomBusEntity(
        sf::Vector2f const& position = {0, 0}
    );

    /**
     * Creates a RhomBus entity with given size
     * 
     * @param[in] size
     *  size of the big diagonal of the rhombus shape
     * @param[in] position
     *  position of the center of the rhombus shape
     */
    RhomBusEntity(
        float size,
        sf::Vector2f const& position = {0, 0});

    /**
     * Applies force with the given velocity,
     * meaning that the given velocity is added to the current velocity.
     * 
     * @param[in] velocityForce
     *  velocity to be applied/forced on the RhomBus
     */
    void ApplyVelocityForce(sf::Vector2f const& velocityForce);

    /**
     * Updates the RhomBus for the next frame
     */
    void Update();

  private: /* functions */

    /**
     * Creates the components that make up the multishape of a RhomBus entity.
     * Those components are a RhombusShape body and 2 circle tyres.
     * 
     * @param[in] size
     *  size of the big diagonal of the rhombus shape
     * 
     * @return vector of pointers to component shapes
     */
    static std::vector<sf::Shape*> CreateComponents(float size);

  private: /* variables */

    /// The size of the big diagonal of the rhombus shape
    float _size;

    /// Velocity vector. Indicates the speed and direction at which the RhomBus is moving.
    sf::Vector2f _velocity;

    /// Default size of the big diagonal of the rhombus shape
    static float const RHOMBUS_DEFAULT_SIZE;

    /* All following constants are expressed relative to the big diagonal,
       as the ratio between their actual length and the big diagonal */

    /// Length of the small diagonal of the rhombus shape
    static float const RHOMBUS_SMALL_DIAGONAL;
    /// Radius of the tyres
    static float const RHOMBUS_TYRE_RADIUS;
    /// Distance from the center of the rhombus shape to the ground
    static float const RHOMBUS_GROUND_HEIGHT;
    /// Distance between the centers of the two tyres
    static float const RHOMBUS_TYRE_WIDE_DIST;
};

} // namespace RhomBus