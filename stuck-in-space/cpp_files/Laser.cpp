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
int Laser::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		prevPos2 = prevPos1;
		prevPos1 = getPosition() - getVelocity();
		return 1;
	}
	
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	// If get here, we have ignored this event.
	return 0;
}

int Laser::draw()
{
	DM.drawCh(prevPos2, '.', VIOLET);
	DM.drawCh(prevPos1, 'o', VIOLET);
	DM.drawCh(getPosition(), 'O', VIOLET);
	return 0;
}