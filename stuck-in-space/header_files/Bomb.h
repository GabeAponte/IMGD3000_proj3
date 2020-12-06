// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// Bomb.h
// Special bullet that turns into an explosion on impact
//

#pragma once

#include <EventCollision.h>
#include <Object.h>
#include "../header_files/Hero.h"
#include "../header_files/Bullet.h"

class Bomb : public Bullet {

private:
	void hit(const df::EventCollision* p_collision_event);

public:
	Bomb();

	// Handle events
	int eventHandler(const df::Event* p_e);
};
