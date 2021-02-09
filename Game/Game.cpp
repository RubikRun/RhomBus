#include "Game.h"

namespace
{

int const SCREEN_WIDTH = 1920;
int const SCREEN_HEIGHT = 1080;

int const FRAMERATE_LIMIT = 30;

sf::Keyboard::Key const KEY_QUIT_GAME = sf::Keyboard::Escape;

MultiShape CreateRhomBusMultiShape()
{
    sf::ConvexShape* body = new sf::ConvexShape(4);
    body->setPoint(0, {0, 50});
    body->setPoint(1, {80, 0});
    body->setPoint(2, {160, 50});
    body->setPoint(3, {80, 100});

    sf::CircleShape* leftTyre = new sf::CircleShape(25);
    leftTyre->setPosition({10, 60});

    sf::CircleShape* rightTyre = new sf::CircleShape(25);
    rightTyre->setPosition({100, 60});

    return MultiShape({
        body,
        leftTyre,
        rightTyre
    });
}

} // namespace

namespace RhomBus
{

Game::Game()
    : _window( // Initialize window to be fullscreen
        sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
        "GameName",
        sf::Style::Fullscreen),
    _rhomBus(CreateRhomBusMultiShape())
{
    // Set frame rate limit to not torture the GPU too much
    _window.setFramerateLimit(FRAMERATE_LIMIT);
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
{ /* nothing */ }

void Game::Draw()
{
    _rhomBus.Draw(_window);
}

} // namespace RhomBus