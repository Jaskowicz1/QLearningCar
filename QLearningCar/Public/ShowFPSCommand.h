#pragma once
#include "Command.h"
#include "Game.h"
#include <string>

class ShowFPSCommand: public Command {

public:

	void ProcessCommand() override {
		Game::showFPS = Game::showFPS ? false : true;
	};

	std::string getCommandName() override {
		return "ShowFPS";
	};
};