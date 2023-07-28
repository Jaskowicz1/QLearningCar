#pragma once
#include "Command.h"
#include "Game.h"
#include <string>

class ShowStatsCommand : public Command {

public:

	void ProcessCommand() override {
		Game::showStats = Game::showStats ? false : true;
	};

	std::string getCommandName() override {
		return "ShowStats";
	};
};