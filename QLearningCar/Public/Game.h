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
#include "Console.h"

class Game {

public:

	Game();
	virtual ~Game();

	void pollEvents();
	void update();
	void render();
	void RenderStats();

	void ProcessMouse();

	const bool isRunning()
	{
		return this->window->isOpen();
	}

	sf::Clock clock;

	float fastestTime = 0;
	float lastTime = 0;

	inline static bool showFPS;
	inline static bool showStats;
	inline static bool showCheckpoints;
	inline static bool showSensors;

private:

	sf::RenderWindow* window;
	sf::Event ev;

	sf::Font font;
	sf::Text timeText;
	sf::Text checkpointText;
	sf::Text fastestTimeText;
	sf::Text lastTimeText;
	sf::Text fpsText;

	sf::Clock fpsClock;

	sf::Texture trackTexture;
	sf::Texture trackOutsideTexture;
	sf::Sprite trackSprite;
	sf::Sprite trackOutsideSprite;

	std::unique_ptr<Car> car;
	std::vector<Wall*> walls;
	std::vector<Checkpoint*> Checkpoints;
	std::vector<Checkpoint*> CheckpointsReached;
	
	void initVariables();
	void initWindow();

	void initCar();
	void initWorld();
	void initWalls();
	void initCheckpoints();

	void updateFPS();

	int wallPos1x = -999999;
	int wallPos1y = -999999;
	int wallPos2x = -999999;
	int wallPos2y = -999999;

	bool SetWalls = false;

	float fpstime = 0.f;

	Console* console;
};