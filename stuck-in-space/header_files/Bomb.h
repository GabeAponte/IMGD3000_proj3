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
	// Handles collision events
	void hit(const df::EventCollision* p_collision_event);

	// Detonates the bomb
	void explode();

public:

	Bomb();
	~Bomb();

	// Handle events
	int eventHandler(const df::Event* p_e);

	// Remotely detonate the current bomb, if present
	static void detonate();

	// Check if there is an active bomb
	static bool isActive();
};

static Bomb* activeBomb = NULL;