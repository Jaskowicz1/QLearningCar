#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Checkpoint {

public:

	Checkpoint(std::string FileName);

	sf::Texture checkpointTexture;
	sf::Sprite checkpointSprite;

	bool reached = false;
	float timeReached = 0.f; // Possibly use?

	bool StartFinish = false;
};