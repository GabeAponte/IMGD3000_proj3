//
// Bullet.h
//

#pragma once

#include <EventCollision.h>
#include <Object.h>
#include "../header_files/Hero.h"
#include "../header_files/Bullet.h"

class Bomb : public Bullet {

private:
	player_weapon weaponType;

	void hit(const df::EventCollision* p_collision_event);

public:
	Bomb();

	// Handle events
	int eventHandler(const df::Event* p_e);
};
