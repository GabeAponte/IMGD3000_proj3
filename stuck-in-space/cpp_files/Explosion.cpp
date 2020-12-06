// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// Gabriel Aponte
// gaaponte@wpi.edu

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

	// Link to "explosion" sprite and regulate animation
	if (setSprite("explosion") == 0) {
		timeToLive = getAnimation().getSprite()->getFrameCount();
	}
	else {
		timeToLive = 0;
	}

	// Set type
	setType("Explosion");

	// Set to SOFT
	setSolidness(df::SPECTRAL);
}

// Handle event.
// Return 0 if ignored, else 1.
int Explosion::eventHandler(const df::Event* p_e) 
{
	// Step handler
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// Count down until explosion finished.
void Explosion::step() 
{
	// Decrement rate
	timeToLive--;

	// Check if explosion is over
	if (timeToLive <= 0) {
		df::WM.markForDelete(this);
	}
}
