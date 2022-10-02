#include "Game.h"
#include "Collision.h"

void Game::initVariables()
{
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "QLearning Car Project - Archie Jaskowicz");
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initCar()
{
	car = new Car();
	clock.restart();
}

void Game::initWorld()
{
	std::cout << "Loading world..." << std::endl;

	if (!trackTexture.loadFromFile("RaceTrack.png")) {
		// Throw error.
		std::cout << "Can not load race track." << std::endl;
		return;
	}

	if (!trackOutsideTexture.loadFromFile("RaceTrackOutside.png")) {
		// Throw error.
		std::cout << "Can not load the outside of the race track." << std::endl;
		return;
	}

	trackSprite.setTexture(trackTexture);
	trackOutsideSprite.setTexture(trackOutsideTexture);
}

void Game::initWalls()
{
	std::string myText;

	// Read from the text file
	std::ifstream MyReadFile("walls.txt");

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(MyReadFile, myText)) {
		// Output the text from the file
		std::vector<int> positions;

		//std::cout << "Found a wall in the file... Loading wall.";

		std::stringstream ss(myText);

		for (int i; ss >> i;) {
			positions.push_back(i);
			if (ss.peek() == ',')
				ss.ignore();
		}

		walls.push_back(new Wall(sf::Vector2f(positions[0], positions[1]), sf::Vector2f(positions[2], positions[3])));

		//walls.push_back(new Wall(sf::Vector2f(positions[0], positions[1]), sf::Vector2f(positions[2], positions[3]),
		//	sf::Vector2f(positions[4], positions[5]), sf::Vector2f(positions[6], positions[7])));
	}
}

void Game::initCheckpoints()
{
	for (int i = 1; i < 19; i++) {
		Checkpoints.push_back(new Checkpoint("Checkpoint" + std::to_string(i) + ".png"));
	}

	Checkpoints[0]->StartFinish = true;
}

Game::Game()
{
	this->initWindow();
	this->initWorld();
	this->initCar();
	//this->initWalls();
	this->initCheckpoints();

	if(!font.loadFromFile("Arial.ttf"))
	{
		std::cout << "Can not load Arial font." << std::endl;
		return;
	}

	timeText.setFont(font);
	timeText.setFillColor(sf::Color::Red);
	checkpointText.setFont(font);
	checkpointText.setFillColor(sf::Color::Red);
	fastestTimeText.setFont(font);
	fastestTimeText.setFillColor(sf::Color::Red);

	timeText.setCharacterSize(18);
	checkpointText.setCharacterSize(18);
	fastestTimeText.setCharacterSize(18);
	timeText.setPosition(0, 40);
	checkpointText.setPosition(0, 60);
	fastestTimeText.setPosition(0, 80);
}

Game::~Game()
{
	delete this->window;
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::Escape)
					this->window->close();
				break;
			case sf::Event::MouseButtonPressed:
				this->ProcessMouse();
				break;
		}
	}
}

void Game::update()
{
	this->pollEvents();
	this->RenderStats();
	if (car) {
		this->car->Update();

		if (Collision::PixelPerfectTest(trackOutsideSprite, this->car->sprite)) {
			car->sprite.setPosition(car->startX, car->startY);
			car->sprite.setRotation(0);

			for (Checkpoint* checkpoint : CheckpointsReached) {
				checkpoint->reached = false;
			}

			clock.restart();

			CheckpointsReached.clear();
		} else 
		{
			for (Checkpoint* checkpoint : Checkpoints) {
				if (Collision::PixelPerfectTest(checkpoint->checkpointSprite, this->car->sprite)) {
					if (!checkpoint->reached) {
						CheckpointsReached.push_back(checkpoint);
						checkpoint->reached = true;
					} else 
					{
						if (checkpoint->StartFinish) {
							if (CheckpointsReached.size() == Checkpoints.size()) {
								for (Checkpoint* checkpoint : CheckpointsReached) {
									checkpoint->reached = false;
								}

								if (fastestTime == 0 || fastestTime > clock.getElapsedTime().asSeconds()) {
									fastestTime = clock.getElapsedTime().asSeconds();
								}

								clock.restart();
								CheckpointsReached.clear();
							}
						}
					}
				}
			}
		}
	}

		/*
		for (Wall* wall : walls) {

			if (Collision::PixelPerfectTest2(wall->rectangle, this->car->sprite)) {
				// do stuff...
				car->sprite.setPosition(car->startX, car->startY);
				car->sprite.setRotation(0);
			}
		}
		*/
}

void Game::render()
{
	this->window->clear();
	this->window->draw(this->trackSprite);
	this->window->draw(this->trackOutsideSprite);
	this->window->draw(this->car->accelerationText);
	this->window->draw(this->car->rotationText);
	this->window->draw(this->timeText);
	this->window->draw(this->checkpointText);
	this->window->draw(this->fastestTimeText);

	for (Wall* wall : walls) {
		this->window->draw(wall->rectangle);
	}
	/*
	for (Checkpoint* checkpoint : Checkpoints) {
		this->window->draw(checkpoint->checkpointSprite);
	}
	*/
	this->window->draw(this->car->sprite);

	this->window->display();
}

void Game::RenderStats()
{
	timeText.setString("Time: " + std::to_string(clock.getElapsedTime().asSeconds()));
	checkpointText.setString("Checkpoint " + std::to_string(CheckpointsReached.size()) + "/" + std::to_string(Checkpoints.size()));
	fastestTimeText.setString("Fastest Time: " + std::to_string(fastestTime));
}

void Game::ProcessMouse()
{
	/* OLD walls code.
	if (SetWalls) {
		if (x1 == -999999)
			x1 = sf::Mouse::getPosition(*window).x;
		else if (x2 == -999999)
			x2 = sf::Mouse::getPosition(*window).x;
		else if (x3 == -999999)
			x3 = sf::Mouse::getPosition(*window).x;
		else
			x4 = sf::Mouse::getPosition(*window).x;

		if (y1 == -999999)
			y1 = sf::Mouse::getPosition(*window).y;
		else if (y2 == -999999)
			y2 = sf::Mouse::getPosition(*window).y;
		else if (y3 == -999999)
			y3 = sf::Mouse::getPosition(*window).y;
		else
			y4 = sf::Mouse::getPosition(*window).y;

		std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << " " << x4 << " " << y4 << " " << std::endl;

		if (x1 != -999999 && y1 != -999999 && x2 != -999999 && y2 != -999999 && x3 != -999999 && y3 != -999999 && x4 != -999999 && y4 != -999999) {

			std::ofstream wallsFile("walls.txt", std::ofstream::out | std::ofstream::app);

			wallsFile << x1 << "," << y1 << "," << x2 << "," << y2 << "," << x3 << "," << y3 << "," << x4 << "," << y4 << std::endl;

			walls.push_back(new Wall(sf::Vector2f(x1, y1), sf::Vector2f(x2, y2), sf::Vector2f(x3, y3), sf::Vector2f(x4, y4)));

			wallsFile.close();

			x1 = -999999, y1 = -999999, x2 = -999999, y2 = -999999, x3 = -999999, y3 = -999999, x4 = -999999, y4 = -999999;

			std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << " " << x4 << " " << y4 << " " << std::endl;
		}
	}
	*/

	if (SetWalls) {
		if (wallPos1x == -999999) {
			wallPos1x = sf::Mouse::getPosition(*window).x;
			wallPos1y = sf::Mouse::getPosition(*window).y;
		}
		else {
			wallPos2x = sf::Mouse::getPosition(*window).x;
			wallPos2y = sf::Mouse::getPosition(*window).y;
		}

		//rectangle.setPosition(sf::Vector2f(wallPos1x, wallPos1y));
		//rectangle.setFillColor(sf::Color::Cyan);

		if (wallPos2y != -999999) {
			float calc = sqrt((std::pow((wallPos2x - wallPos1x), 2) + std::pow((wallPos2y - wallPos1y), 2)));
			//rectangle.setSize(sf::Vector2f(20, calc));
			//rectangle.setRotation((atan2(wallPos2y - wallPos1y, wallPos2x - wallPos1x) * (180 / 3.1415926535)) - 90);

			std::ofstream wallsFile("walls.txt", std::ofstream::out | std::ofstream::app);

			wallsFile << wallPos1x << "," << wallPos1y << "," << wallPos2x << "," << wallPos2y << std::endl;

			walls.push_back(new Wall(sf::Vector2f(wallPos1x, wallPos1y), sf::Vector2f(wallPos2x, wallPos2y)));

			//wallsFile.close();

			//wallPos1x = -999999;
			//wallPos1y = -999999;
			//wallPos2x = -999999;
			//wallPos2y = -999999;
		}
		else {
			//rectangle.setSize(sf::Vector2f(20, 20));
		}
	}
}

const bool Game::isRunning()
{
	return this->window->isOpen();
}
