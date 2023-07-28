#include "../Public/Wall.h"
#include <iostream>


Wall::Wall(sf::Vector2f point1, sf::Vector2f point2)
{
	rectangle.setPosition(sf::Vector2f(point1.x, point1.y));
	float calc = sqrt((std::pow((point2.x - point1.x), 2) + std::pow((point2.y - point1.y), 2)));
	rectangle.setSize(sf::Vector2f(20, calc));
	rectangle.setRotation((atan2(point2.y - point1.y, point2.x - point1.x) * (180 / 3.1415926535)) - 90);

	rectangle.setFillColor(sf::Color::Red);
}

bool Wall::CheckCollision(Car* car)
{
	/*
			* obstacle.GetPosition().x < p.getPlayerPosition().x + p.getPlayerSize().x &&
	obstacle.GetPosition().x + obstacle.GetSize().x > p.getPlayerPosition().x &&
	obstacle.GetPosition().y < p.getPlayerPosition().y + p.getPlayerSize().x &&
	obstacle.GetSize().y + obstacle.GetPosition().y > p.getPlayerPosition().y
			*/
	return rectangle.getPosition().x < car->sprite.getPosition().x + car->sprite.getScale().x && 
		rectangle.getPosition().x + rectangle.getScale().x > car->sprite.getPosition().x &&
		rectangle.getPosition().y < car->sprite.getPosition().y + car->sprite.getScale().x &&
		rectangle.getScale().y + rectangle.getPosition().y > car->sprite.getPosition().y;
}
