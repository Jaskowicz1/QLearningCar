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

    /*

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    sf::Texture texture;
    if (!texture.loadFromFile("Car.jpg"))
        return 0;
    sf::Sprite sprite(texture);

    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {

            window.clear();

            Main::moving = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                Main::moveY += 1;
                Main::moving = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                Main::moveY -= 1;
                Main::moving = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                Main::moveX += 1;
                Main::moving = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                Main::moveX -= 1;
                Main::moving = true;
            }

            if (Main::moving) {

                std::cout << "Moving..." << std::endl;

                std::cout << "MoveX: " << Main::moveX << std::endl;
                std::cout << "MoveY: " << Main::moveY << std::endl;

                if (Main::moveX > 0) {
                    Main::moveX -= 1;
                }
                else if (Main::moveX < 0) {
                    Main::moveX += 1;
                }

                if (Main::moveY > 0) {
                    Main::moveY -= 1;
                }
                else if (Main::moveY < 0) {
                    Main::moveY += 1;
                }
            }

            sprite.move(Main::moveX, Main::moveY);

            window.draw(sprite);

            window.display();

            
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //window.clear();
    }

    return 0;
    */
}