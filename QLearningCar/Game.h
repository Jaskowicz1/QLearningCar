#pragma once
#include <SFML/Graphics.hpp>
#include "Car.h"
#include "Wall.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <math.h>
#include "Checkpoint.h"

class Game {

public:

	Game();
	virtual ~Game();

	void pollEvents();
	void update();
	void render();
	void RenderStats();

	void ProcessMouse();

	const bool isRunning();

	sf::Clock clock;

	float fastestTime = 0;

private:

	sf::RenderWindow* window;
	sf::Event ev;

	sf::Font font;
	sf::Text timeText;
	sf::Text checkpointText;
	sf::Text fastestTimeText;

	sf::Texture trackTexture;
	sf::Texture trackOutsideTexture;
	sf::Sprite trackSprite;
	sf::Sprite trackOutsideSprite;

	Car* car;
	std::vector<Wall*> walls;
	std::vector<Checkpoint*> Checkpoints;
	std::vector<Checkpoint*> CheckpointsReached;
	
	void initVariables();
	void initWindow();

	void initCar();
	void initWorld();
	void initWalls();
	void initCheckpoints();

	int wallPos1x = -999999;
	int wallPos1y = -999999;
	int wallPos2x = -999999;
	int wallPos2y = -999999;

	bool SetWalls = false;

};