// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// Laser.cpp
// Special piercing bullet
//

#include <DisplayManager.h>
#include <EventOut.h>
#include <EventStep.h>
#include "../header_files/Laser.h"

using namespace df;

Laser::Laser(df::Vector position) {

	// Set other object properties.
	setType("Bullet");

	// Set SOFT
	setSolidness(SOFT);

	// Set the weapon type
	weaponType = W_LASER;

	// Set position
	setPosition(position);
	prevPos1 = position;
	prevPos2 = position;
}

// Handle event.
// Return 0 if ignored, else 1.
int Laser::eventHandler(const df::Event* p_e) 
{
	// Step handler
	if (p_e->getType() == STEP_EVENT) {
		prevPos2 = prevPos1;
		prevPos1 = getPosition() - getVelocity();
		return 1;
	}
	
	// Out of bounds handler
	if (p_e->getType() == OUT_EVENT) {
		out();
		return 1;
	}

	// Colisions handler
	if (p_e->getType() == COLLISION_EVENT) {
		const EventCollision* p_collision_event = dynamic_cast <const EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	// If get here, we have ignored this event.
	return 0;
}

// Draws the lazer
int Laser::draw()
{
	DM.drawCh(prevPos2, '.', INDIGO);
	DM.drawCh(prevPos1, 'o', INDIGO);
	DM.drawCh(getPosition(), 'O', INDIGO);
	return 0;
}