#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Car {

public:

	Car();

#pragma region SFMLstuff

	// SFML stuff
	// This is "fine".

	sf::Texture texture;
	sf::Sprite sprite;

	sf::Font font;
	sf::Text accelerationText;
	sf::Text rotationText;

	void Update();
	void RenderStats();

#pragma endregion

#pragma region CarInfo

	const int startX = 157;
	const int startY = 466;

	const float maxSpeed = 2.f;
	const float minSpeed = -2.f;

	const float maxRotation = 2.f;
	const float minRotation = -2.f;

#pragma endregion

	void doMovement();

private:

	void initRender();
	void initText();

#pragma region CarStats

	float speed = 0.f;
	float rotate = 0.f;

	bool moving = false;

#pragma endregion

	// Convert degrees to radians.
	float toRadians(float rotation) {
		return rotation * (3.1415926535f / 180.f);
	}

};