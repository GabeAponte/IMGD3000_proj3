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
	df::Vector prevPos1;
	df::Vector prevPos2;
public:
	Laser(df::Vector position);

	// Handle events
	int eventHandler(const df::Event* p_e);
	// Draw full laser
	int draw();
};
