// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// Star.cpp
//

#include <Utility.h>
#include <DisplayManager.h>
#include <EventOut.h>
#include <EventStep.h>
#include <WorldManager.h>
#include "../header_files/Star.h"

using namespace df;

Star::Star() {

	// Set sprite to star chars
	std::string sprite = "star" + toString(rand() % 3);
	setSprite(sprite);

	// Set type
	setType("Star");

	// Set to spectral

	// Set velocity and altitude
	setSolidness(df::SPECTRAL);
	setVelocity(Vector(0,(float) -(1+ rand() % 3)/200));
	setAltitude(0);	// Make Stars in the background.

	// Set start position randomly and the animation index
	df::Vector p((float)(rand() % (int) WM.getBoundary().getHorizontal()),
		(float)(rand() % (int) WM.getBoundary().getVertical()));
	setPosition(p);
	setAnimationIndex(rand() % 3);
}

// Handle event.
// Return 0 if ignored, else 1.
int Star::eventHandler(const df::Event* p_e) 
{
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// If Star moved off window, move back to top.
void Star::out() 
{
	df::Vector p((float)(rand() % (int) WM.getBoundary().getHorizontal()), WM.getBoundary().getVertical());
	setPosition(p);
}
