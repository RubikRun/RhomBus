#include "Game.h"

namespace
{

int const SCREEN_WIDTH = 1920;
int const SCREEN_HEIGHT = 1080;

int const FRAMERATE_LIMIT = 60;

sf::Keyboard::Key const KEY_QUIT_GAME = sf::Keyboard::Escape;

} // namespace

namespace RhomBus
{

Game::Game()
    : _window( // Initialize window to be fullscreen
        sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
        "GameName",
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
    float const speed = 0.1f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        _rhomBus.ApplyVelocityForce({0, -speed});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        _rhomBus.ApplyVelocityForce({0, speed});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        _rhomBus.ApplyVelocityForce({speed, 0});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        _rhomBus.ApplyVelocityForce({-speed, 0});
    }

    _rhomBus.Update();
}

void Game::Draw()
{
    _rhomBus.Draw(_window);
}

} // namespace RhomBus