// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// Bullet.h
//

#pragma once

#include <Object.h>
#include <EventCollision.h>
#include "../header_files/Hero.h"

class Bullet : public df::Object {

protected:

	player_weapon weaponType; // The type of this bullet

	// Handles the out of bounds events
	void out();

	// Handles the collision events
	void hit(const df::EventCollision* p_collision_event);

public:

	// Constructor with the type of weapon (missle by default);
	Bullet(player_weapon weapon_type = W_MISSILE);

	// Handle events
	int eventHandler(const df::Event* p_e);

	// Get weapon type for bullet
	player_weapon getWeaponType();
};
