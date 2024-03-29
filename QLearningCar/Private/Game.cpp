#include "../Public/Game.h"
#include "../Public/Collision.h"

void Game::initVariables()
{
	console = new Console();

	std::string timingText;

	// Read from the text file
	std::ifstream TimesFile("times.txt");

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(TimesFile, timingText)) {
		if (fastestTime == 0) {
			fastestTime = std::stof(timingText);
		}
		else {
			lastTime = std::stof(timingText);
		}
	}
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Car Project - Archie Jaskowicz");
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initCar()
{
	car = std::make_unique<Car>();
	clock.restart();
}

void Game::initWorld()
{
	std::cout << "Loading world..." << std::endl;

	if (!trackTexture.loadFromFile("RaceTrack.png")) {
		// Throw "error".
		std::cout << "Can not load race track." << std::endl;
		return;
	}

	if (!trackOutsideTexture.loadFromFile("RaceTrackOutside.png")) {
		// Throw "error".
		std::cout << "Can not load the outside of the race track." << std::endl;
		return;
	}

	trackSprite.setTexture(trackTexture);
	trackOutsideSprite.setTexture(trackOutsideTexture);
}

void Game::initWalls()
{
	std::string wallText;

	// Read from the text file
	std::ifstream WallFile("walls.txt");

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(WallFile, wallText)) {
		// Output the text from the file
		std::vector<int> positions;

		std::stringstream ss(wallText);

		for (int i; ss >> i;) {
			positions.push_back(i);
			if (ss.peek() == ',')
				ss.ignore();
		}

		walls.push_back(new Wall(sf::Vector2f(positions[0], positions[1]), sf::Vector2f(positions[2], positions[3])));
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
	this->initVariables();
	this->initWindow();
	this->initWorld();
	this->initCar();
	//this->initWalls();
	this->initCheckpoints();

	// Possibly move all this font stuff into a different function as it takes a lot of room
	// and I'd like to minimise just this one area?

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
	lastTimeText.setFont(font);
	lastTimeText.setFillColor(sf::Color::Red);
	fpsText.setFont(font);
	fpsText.setFillColor(sf::Color::Green);

	timeText.setCharacterSize(18);
	checkpointText.setCharacterSize(18);
	fastestTimeText.setCharacterSize(18);
	lastTimeText.setCharacterSize(18);
	fpsText.setCharacterSize(18);
	timeText.setPosition(0, 40);
	checkpointText.setPosition(0, 60);
	fastestTimeText.setPosition(0, 80);
	lastTimeText.setPosition(0, 100);
	fpsText.setPosition(1160, 100);
}

Game::~Game()
{
	// if game leaves scope, window dies (ending session).
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
				else if (ev.key.code == sf::Keyboard::Tab)
					console->showConsole = console->showConsole ? false : true; // toggles console.
				break;
			case sf::Event::TextEntered:
				if (console->showConsole) {
					if (std::isprint(ev.text.unicode))
					{
						console->UpdateConsoleText(ev.text.unicode);
						return;
					}
					else if (ev.text.unicode == 13) {
						console->ExecuteCommand();
					}
					else if (ev.text.unicode == 8) {
						console->DeleteLetter();
					}
				}
				break;
			case sf::Event::MouseButtonPressed:
				this->ProcessMouse();
				break;
		}
	}
}

void Game::update()
{
	this->updateFPS();
	this->pollEvents();
	this->RenderStats();

	if(!car)
		return;

	if (console && !console->showConsole) {
		this->car->doMovement();
	}

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

			if (!Collision::PixelPerfectTest(checkpoint->checkpointSprite, this->car->sprite))
				return;

			if (!checkpoint->reached) {
				CheckpointsReached.push_back(checkpoint);
				checkpoint->reached = true;
				return;
			}

			if(!checkpoint->StartFinish || CheckpointsReached.size() != Checkpoints.size())
				return;

			for (Checkpoint* checkpoint : CheckpointsReached) {
				checkpoint->reached = false;
			}

			if (fastestTime == 0 || fastestTime > clock.getElapsedTime().asSeconds()) {
				fastestTime = clock.getElapsedTime().asSeconds();
			}

			lastTime = clock.getElapsedTime().asSeconds();

			std::ofstream timesFile("times.txt");

			timesFile << fastestTime << std::endl << lastTime << std::endl;

			timesFile.close();

			clock.restart();
			CheckpointsReached.clear();
		}
	}
}

void Game::render()
{
	this->window->clear();
	this->window->draw(this->trackSprite);
	this->window->draw(this->trackOutsideSprite);

	if (showStats) {
		this->window->draw(this->car->accelerationText);
		this->window->draw(this->car->rotationText);
		this->window->draw(this->timeText);
		this->window->draw(this->checkpointText);
		this->window->draw(this->fastestTimeText);
		this->window->draw(this->lastTimeText);
	}

	if (showFPS) {
		this->window->draw(this->fpsText);
	}

	for (Wall* wall : walls) {
		this->window->draw(wall->rectangle);
	}
	
	if (showCheckpoints) {
		for (Checkpoint* checkpoint : Checkpoints) {
			this->window->draw(checkpoint->checkpointSprite);
		}
	}

	// Do car drawing last so it's ALWAYS above the objects.
	this->window->draw(this->car->sprite);

	if (console->showConsole) {
		console->DisplayConsole(window);
	}

	this->window->display();
}

void Game::RenderStats()
{
	timeText.setString("Time: " + std::to_string(clock.getElapsedTime().asSeconds()));
	checkpointText.setString("Checkpoint " + std::to_string(CheckpointsReached.size()) + "/" + std::to_string(Checkpoints.size()));
	fastestTimeText.setString("Fastest Time: " + std::to_string(fastestTime));
	lastTimeText.setString("Last Time: " + std::to_string(lastTime));
}

void Game::ProcessMouse()
{
	if(!SetWalls)
		return;

	// if first wall is invalid, set the first wall and then stop.
	if (wallPos1x == -999999)
	{
		wallPos1x = sf::Mouse::getPosition(*window).x;
		wallPos1y = sf::Mouse::getPosition(*window).y;
		
		return;
	}

	// Because first wall is now valid, we can assume we want to set the second wall.
	wallPos2x = sf::Mouse::getPosition(*window).x;
	wallPos2y = sf::Mouse::getPosition(*window).y;

	// Just in-case.
	if(wallPos2y == -999999)
		return;
	
	float calc = sqrt((std::pow((wallPos2x - wallPos1x), 2) + std::pow((wallPos2y - wallPos1y), 2)));

	// We don't want to override the file, we want to append to the file.
	std::ofstream wallsFile("walls.txt", std::ofstream::out | std::ofstream::app);

	wallsFile << wallPos1x << "," << wallPos1y << "," << wallPos2x << "," << wallPos2y << std::endl;

	walls.push_back(new Wall(sf::Vector2f(wallPos1x, wallPos1y), sf::Vector2f(wallPos2x, wallPos2y)));

	wallsFile.close();
}

void Game::updateFPS() {
	float fpsCounter = 1.f / fpsClock.restart().asSeconds();
	// Make whole number as an int but keep as float.
	fpsCounter = static_cast<int>(100 * fpsCounter + .5);
	// now divide by 100 so we have it to 2 decimal places.
	fpsCounter = (fpsCounter / 100);

	if (fpsCounter > 40) {
		fpsText.setFillColor(sf::Color::Green);
	}
	else if (fpsCounter <= 40 && fpsCounter > 20) {
		fpsText.setFillColor(sf::Color::Yellow);
	}
	else {
		fpsText.setFillColor(sf::Color::Red);
	}

	// _count checks if fps is 100 or more and limits the amount of decimal places shown
	// (22.25 will show as 22.250 if we stick to 6 as any further is 0 due to math above).s
	fpsText.setString("FPS: " + std::to_string(fpsCounter).substr(0, fpsCounter >= 100 ? 6 : 5));
}