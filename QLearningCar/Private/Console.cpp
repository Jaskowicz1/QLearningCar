#include "../Public/Console.h"
#include "../Public/ShowFPSCommand.h";
#include "../Public/ShowStatsCommand.h";
#include "../Public/ShowCheckpointsCommand.h";

Console::Console()
{
	Commands.push_back(new ShowFPSCommand());
	Commands.push_back(new ShowStatsCommand());
	Commands.push_back(new ShowCheckpointsCommand());

	if (!font.loadFromFile("Arial.ttf"))
	{
		std::cout << "Can not load Arial font." << std::endl;
		return;
	}

	rectangle.setFillColor(sf::Color(50, 50, 50, 150));
	rectangle.setSize(sf::Vector2f(1280, 50));
	rectangle.setPosition(sf::Vector2f(0, 670));
	consoleText.setFont(font);
	consoleText.setPosition(sf::Vector2f(10, 680));
	consoleText.setFillColor(sf::Color::Red);
	consoleText.setCharacterSize(22);
}

void Console::ExecuteCommand()
{
	std::string CommandName = CurrentConsoleInput;

	for (Command* command : Commands) {
		if (CommandName == command->getCommandName()) {
			command->ProcessCommand();
			ClearConsoleText();
			return;
		}
	}

	ClearConsoleText();
}

void Console::DisplayConsole(sf::RenderWindow* window)
{
	window->draw(rectangle);
	window->draw(consoleText);
}

void Console::UpdateConsoleText(const std::string& letter)
{
	CurrentConsoleInput += letter;
	consoleText.setString(CurrentConsoleInput);
}

void Console::UpdateConsoleText(const sf::Uint32 letter)
{
	int letter2 = letter;
	CurrentConsoleInput += static_cast<char>(letter2);
	consoleText.setString(CurrentConsoleInput);
}

void Console::ClearConsoleText()
{
	CurrentConsoleInput = "";
	consoleText.setString(CurrentConsoleInput);
}

void Console::DeleteLetter()
{
	// pop_back will error otherwise, so stop if empty.
	if (CurrentConsoleInput.size() == 0)
		return;

	CurrentConsoleInput.pop_back();
	consoleText.setString(CurrentConsoleInput);
}
