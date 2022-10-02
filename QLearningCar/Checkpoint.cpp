#include "Checkpoint.h"

Checkpoint::Checkpoint(std::string FileName)
{
	if (!checkpointTexture.loadFromFile(FileName)) {
		// Throw error.
		std::cout << "Can not load race track." << std::endl;
		return;
	}

	checkpointSprite.setTexture(checkpointTexture);
}
