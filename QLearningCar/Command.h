#pragma once
#include <string>

class Command {

public:

	virtual void ProcessCommand() {
		return;
	};

	virtual std::string getCommandName() {
		return "";
	};

};