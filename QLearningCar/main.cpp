#include <SFML/Graphics.hpp>
#include <iostream>
#include "main.h"

using namespace Main;

int main()
{
    game = new Game();

    while (game->isRunning()) {
        game->update();

        game->render();
    }

    return 0;
}