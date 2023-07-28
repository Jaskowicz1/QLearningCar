#pragma once
#include <SFML/Graphics.hpp>
#include "Car.h"

class Wall {

public:

	Wall(sf::Vector2f point1, sf::Vector2f point2);

	bool CheckCollision(Car* car);

	sf::RectangleShape rectangle;

private:

	sf::Vector2f FirstPoint;
	sf::Vector2f SecondPoint;

};