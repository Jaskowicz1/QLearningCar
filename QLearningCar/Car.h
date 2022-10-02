#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Car {

public:

	Car();

	sf::Texture texture;
	sf::Sprite sprite;

	sf::Font font;
	sf::Text accelerationText;
	sf::Text rotationText;

	void Update();
	void RenderStats();

	int startX = 157;
	int startY = 466;

	float maxSpeed = 2.f;
	float minSpeed = -2.f;

	float maxRotation = 2.f;
	float minRotation = -2.f;

private:

	void initRender();
	void initText();

	void doMovement();

	float speed = 0.f;
	float rotate = 0.f;

	bool moving = false;

	float toRadians(float rotation) {
		return rotation * (3.1415926535 / 180);
	}

};