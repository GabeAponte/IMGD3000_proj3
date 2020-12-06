// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// Laser.h
// Special piercing bullet
//

#pragma once

#include <EventCollision.h>
#include <Object.h>
#include "../header_files/Hero.h"
#include "../header_files/Bullet.h"

class Laser : public Bullet {

private:

	df::Vector prevPos1; // Vector of last position
	df::Vector prevPos2; // Additional vector of last position
public:

	// Constructor that sets the last position
	Laser(df::Vector position);

	// Handle events
	int eventHandler(const df::Event* p_e);

	// Draw full laser
	int draw();
};
