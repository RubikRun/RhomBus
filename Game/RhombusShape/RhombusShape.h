#pragma once

#include <SFML/Graphics.hpp>

/**
 * A class representing a rhombus shape
 * with vertical and horizontal diagonals
 */
class RhombusShape : public sf::ConvexShape
{

  public:
    
    /**
     * Creates a zero rhombus shape
     */
    RhombusShape();

    /**
     * Creates a rhombus shape with the given diagonal lengths,
     * and puts it on the given center position
     * 
     * @param[in] horizontal
     *  Length of the horizontal diagonal
     * @param[in] vertical
     *  Length of the vertical diagonal
     * @param[in] center (optional)
     *  Position of the center
     */
    RhombusShape(
        float horizontal,
        float vertical,
        sf::Vector2f const& center = {0, 0});

    /**
     * Returns the position of the center
     * 
     * @return center
     */
    sf::Vector2f GetPosition() const;

    /**
     * Sets center of the rhombus to the given position
     * 
     * @param[in] center
     *  The position of the center to set
     */
    void SetPosition(sf::Vector2f const& center);

    /**
     * Moves the rhombus by some delta vector
     * 
     * @param[in] delta
     *  vector by which to move the rhombus
     */
    void Move(sf::Vector2f const& delta);

    /**
     * Returns the length of the horizontal diagonal
     * 
     * @return horizontal diagonal
     */
    float GetHorizontal() const;

    /**
     * Sets the length of the horizontal diagonal
     * 
     * @param[in] horizontal
     *  length value to set
     */
    void SetHorizontal(float horizontal);

    /**
     * Changes length of the horizontal diagonal by some delta
     * 
     * @param[in] delta
     *  amount by which to change the diagonal
     */
    void ChangeHorizontal(float delta);

    /**
     * Returns the length of the vertical diagonal
     * 
     * @return vertical diagonal
     */
    float GetVertical() const;

    /**
     * Sets the length of the vertical diagonal
     * 
     * @param[in] vertical
     *  length value to set
     */
    void SetVertical(float vertical);

    /**
     * Changes length of the vertical diagonal by some delta
     * 
     * @param[in] delta
     *  amount by which to change the diagonal
     */
    void ChangeVertical(float delta);

  private: /* functions */

    /**
     * Updates positions of rhombus' vertices,
     * according to the current center and diagonals
     */
    void UpdateVertices();

  private: /* variables */
    
    /// Lengths of the horizontal and vertical diagonals
    float _horizontal, _vertical;

    /// Center of the rhombus, where diagonals intersect
    sf::Vector2f _center;
};