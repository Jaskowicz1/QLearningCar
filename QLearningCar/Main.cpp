#include <SFML/Graphics.hpp>
#include "Main.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    sf::Texture texture;
    if (!texture.loadFromFile("ball_image.jpg"))
        return 0;
    sf::Sprite sprite(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

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

        sprite.move(sf::Vector2f(Main::moveX, Main::moveY));

        window.draw(sprite);
        
        window.display();
    }

    return 0;
}