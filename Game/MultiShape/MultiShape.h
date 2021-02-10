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
     * relative to a given center.
     * 
     * @param[in] components
     *  The components from which the multishape will be created.
     *  Their given coordinates are relative to the center,
     *  and not to the screen
     * @param[in] center
     *  The screen position of the center
     */
    MultiShape(
        std::vector<sf::Shape*> const& components,
        sf::Vector2f const& center = {0.f, 0.f});

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
     * Returns a pointer to the component with the given index
     * 
     * @param[in] index
     *  The index of the component that we want
     */
    sf::Shape* operator[](unsigned index);
    /// Same function but for const MultiShape-s, returning pointer to const component
    sf::Shape const* operator[](unsigned index) const;

    /**
     * Draws the multishape on the given window.
     * 
     * @param[in] window
     *  The window where the multishape will be drawn
     */
    void Draw(sf::RenderTarget& window) const;

    /**
     * Returns the position of the center
     * 
     * @return center's position
     */
    sf::Vector2f GetPosition() const;

    /**
     * Sets the position of the center
     * 
     * @param[in] center
     *  The center's position to set
     */
    void SetPosition(sf::Vector2f const& center);

    /**
     * Moves the whole multishape by some delta vector
     * 
     * @param[in] delta
     *  The delta vector by which to move the multishape
     */
    void Move(sf::Vector2f const& delta);

    /**
     * Frees the memory of each component shape
     */
    ~MultiShape();

  private:

    /// The component shapes that make up the multi shape
    std::vector<sf::Shape*> _components;

    /* Center of the multishape.
       This is a special point that defines the position of the multishape.
       All components' coordinates are relative to that point,
       and the whole multishape can be moved by moving that point */
    sf::Vector2f _center;
};