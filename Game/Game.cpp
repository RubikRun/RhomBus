#include "Game.h"
#include <iostream>

#include <cmath>

namespace
{

int const SCREEN_WIDTH = 1920;
int const SCREEN_HEIGHT = 1080;

int const FRAMERATE_LIMIT = 60;

sf::Keyboard::Key const KEY_QUIT_GAME = sf::Keyboard::Escape;

// Gravitational acceleration in pixels/frame^2
float const GRAVITATIONAL_ACCELERATION = 1.f;

/* Air resistance constant for x-movement of RhomBus.
   (y-movement is considered handled by the gravitational acceleration)
   Meaning that the x-velocity of RhomBus will always have an opposing force,
   the air resistance, which is {this constant} * x-velocity */
float const AIR_RESISTANCE = 0.05f;

/* Ground friction constant for x-movement of RhomBus on the ground.
   (works together with air resistance when RhomBus is on the ground)
   Meaning that the x-velocity of RhomBus will have an opposing force,
   the ground friction, when on the ground, which is {this constant} * x-velocity */
float const GROUND_FRICTION = 0.04f;

} // namespace

namespace RhomBus
{

Game::Game()
    : _window( // Initialize window to be fullscreen
        sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
        "RhomBus",
        sf::Style::Fullscreen),
    _rhomBus({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2})
{
    // Set frame rate limit to not torture the GPU too much
    _window.setFramerateLimit(FRAMERATE_LIMIT);

    // Vertical sync for some monitors that get screen tearing
    _window.setVerticalSyncEnabled(true);
}

void Game::Run()
{
    /* The game loop.
       Updating and rendering until the player closes the game */
    while (_window.isOpen())
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            // If the player has pressed the quit key, we close the window
            if (event.type == sf::Event::KeyPressed
                && event.key.code == KEY_QUIT_GAME)
            {
                _window.close();
            }
        }

        // first clear previous frame
        _window.clear();
        // then update game for the next frame
        Update();
        // then draw the next frame
        Draw();
        // and render it on the window
        _window.display();
    }
}

Game::~Game()
{ /* nothing */ }

void Game::Update()
{
    /* RhomBus engine's power,
       meaning that the engine can increase RhomBus' velocity
       with that much pixels/frame^2 in a given direction */
    float const ENGINE_POWER = 2.f;

    // User input activates engine
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        _rhomBus.ApplyVelocityForce({ENGINE_POWER, 0.f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        _rhomBus.ApplyVelocityForce({-ENGINE_POWER, 0.f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        _rhomBus.ApplyVelocityForce({0.f, ENGINE_POWER});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        _rhomBus.ApplyVelocityForce({0.f, -ENGINE_POWER});
    }

    // Gravitational acceleration always affects RhomBus
    _rhomBus.ApplyVelocityForce({0, GRAVITATIONAL_ACCELERATION});

    /* We consider the lower end of the screen to be the ground,
       so if the next position of RhomBus would be beneath the ground,
       the ground applies to the RhomBus the same force that the RhomBus applies to the ground,
       but in the opposite direction,
       resulting in the y-velocity of the RhomBus staying at 0, when at ground level. */
    if (_rhomBus.GetNextPosition().y + _rhomBus.GetCenterHeight() >= SCREEN_HEIGHT)
    {
        _rhomBus.ApplyVelocityForce({0, -_rhomBus.GetVelocity().y});
    }

    // Applying air resistance proportiaonal to the x-velocity, but in the opposite direction
    _rhomBus.ApplyVelocityForce({-_rhomBus.GetVelocity().x * AIR_RESISTANCE, 0});

    // If the RhomBus is on the ground, we apply ground friction as well
    if (ceil(_rhomBus.GetPosition().y + _rhomBus.GetCenterHeight()) >= SCREEN_HEIGHT)
    {
        _rhomBus.ApplyVelocityForce({-_rhomBus.GetVelocity().x * GROUND_FRICTION, 0});
    }

    /* At this point all physics affecting the RhomBus' velocity are applied,
       and we can update its position for the next frame */
    _rhomBus.Update();
}

void Game::Draw()
{
    _rhomBus.Draw(_window);
}

} // namespace RhomBus