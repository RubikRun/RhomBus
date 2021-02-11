#pragma once

#include <SFML/Graphics.hpp>

#include "RhomBusEntity/RhomBusEntity.h"

namespace RhomBus
{

/**
 * A class for easily creating and running the Game.
 */
class Game
{

  public:

    /**
     * Sets up a new game.
     */
    Game();

    /**
     * Runs the game.
     */
    void Run();

    /**
     * Cleans up after the game has ended.
     */
    ~Game();

  private: /* functions */

    /// Updates the game for the next frame.
    void Update();

    /// Draws the game to the window
    void Draw();

  private: /* variables */

    /// The window where the game is rendered
    sf::RenderWindow _window;

    /// RhomBus as an entity object
    RhomBusEntity _rhomBus;
};

} // namespace RhomBus