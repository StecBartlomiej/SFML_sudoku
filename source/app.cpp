#include "app.h"


App::App(): window_{}, sudoku_{}
{

}

void App::run()
{
    while (window_.isRunning()){
        window_.display();
        /// if left click !

        /// if right click !
    }
}

void App::handleEvents()
{
    sf::Vector2i mousePos{0, 0};
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {

    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {

    }

}
