#include "Game.h"

namespace
{

int const SCREEN_WIDTH = 1920;
int const SCREEN_HEIGHT = 1080;

int const FRAMERATE_LIMIT = 30;

sf::Keyboard::Key const KEY_QUIT_GAME = sf::Keyboard::Escape;

MultiShape CreateRhomBusMultiShape()
{
    RhombusShape* body = new RhombusShape(600, 300);

    sf::CircleShape* leftTyre = new sf::CircleShape(80);
    leftTyre->setPosition({-230, 50});

    sf::CircleShape* rightTyre = new sf::CircleShape(80);
    rightTyre->setPosition({70, 50});

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
{
    _rhomBus.SetPosition(
        {(float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y}
    );

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        static_cast<RhombusShape*>(_rhomBus[0])->ChangeVertical(8);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        static_cast<RhombusShape*>(_rhomBus[0])->ChangeVertical(-8);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        static_cast<RhombusShape*>(_rhomBus[0])->ChangeHorizontal(8);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        static_cast<RhombusShape*>(_rhomBus[0])->ChangeHorizontal(-8);
    }
}

void Game::Draw()
{
    _rhomBus.Draw(_window);
}

} // namespace RhomBus