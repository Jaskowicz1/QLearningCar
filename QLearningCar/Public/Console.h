#pragma once
#include <vector>
#include "Command.h"
#include <string>
#include <SFML/Graphics.hpp>

class Console {

public:

	Console();

	void ExecuteCommand();

	bool showConsole = false;

	void DisplayConsole(sf::RenderWindow* window);

	void UpdateConsoleText(const std::string& letter);

	void UpdateConsoleText(sf::Uint32 letter);

	void ClearConsoleText();

	void DeleteLetter();

private:

	std::vector<Command*> Commands;

	std::string CurrentConsoleInput;

	sf::Font font;
	sf::Text consoleText;
	sf::RectangleShape rectangle;

};