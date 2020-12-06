//
// Explosion.cpp
//

#include "EventStep.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "../header_files/Explosion.h"

Explosion::Explosion() {

	// Link to "explosion" sprite.
	if (setSprite("explosion") == 0)
		timeToLive = getAnimation().getSprite()->getFrameCount();
	else
		timeToLive = 0;

	setType("Explosion");

	setSolidness(df::SPECTRAL);
}

// Handle event.
// Return 0 if ignored, else 1.
int Explosion::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// Count down until explosion finished.
void Explosion::step() {
	timeToLive--;
	if (timeToLive <= 0)
		df::WM.markForDelete(this);
}
