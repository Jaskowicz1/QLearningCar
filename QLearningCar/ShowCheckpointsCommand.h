#pragma once
#include "Command.h"
#include "Game.h"
#include <string>

class ShowCheckpointsCommand : public Command {

public:

	void ProcessCommand() override {
		Game::showCheckpoints = Game::showCheckpoints ? false : true;
	};

	std::string getCommandName() override {
		return "ShowCheckpoints";
	};
};