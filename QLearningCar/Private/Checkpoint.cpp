#include "../Public/Checkpoint.h"

Checkpoint::Checkpoint(const std::string& FileName)
{
	if (!checkpointTexture.loadFromFile(FileName)) {
		// Throw error.
		std::cout << "Can not load checkpoint: " << FileName << std::endl;
		return;
	}

	checkpointSprite.setTexture(checkpointTexture);
}
