#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

/**
 * A class representing a multi/composite shape -
 * a shape built of multiple components,
 * each of which is a base SFML shape.
 * 
 * Such a class is convinient for when we want
 * to work with the whole multi shape,
 * without having to handle each component individually.
 */
class MultiShape
{

  public:

    /**
     * Creates an empty multishape with no component shapes
     */
    MultiShape();

    /**
     * Creates a multishape from given component shapes
     * 
     * @param[in] components
     *  The components from which the multishape will be created
     */
    MultiShape(
        std::vector<sf::Shape*> const& components);

    /**
     * Copy constructor.
     * We need to copy the component shapes,
     * not only their pointers.
     * 
     * @param[in] other
     *  The other multishape, which we will copy to create this multishape
     */
    MultiShape(
        MultiShape const& other);

    /**
     * Draws the multishape on the given window.
     * 
     * @param[in] window
     *  The window where the multishape will be drawn
     */
    void Draw(sf::RenderWindow& window);

    /**
     * Frees the memory of each component shape
     */
    ~MultiShape();

  private:

    /// The component shapes that make up the multi shape
    std::vector<sf::Shape*> _components;
};