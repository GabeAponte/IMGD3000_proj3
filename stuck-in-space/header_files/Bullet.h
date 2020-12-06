// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// Bullet.h
//

#pragma once

#include <EventCollision.h>
#include <Object.h>
#include "../header_files/Hero.h"

class Bullet : public df::Object {

protected:
	player_weapon weaponType;

	void out();
	void hit(const df::EventCollision* p_collision_event);

public:
	Bullet(player_weapon weapon_type = W_MISSILE);

	// Handle events
	int eventHandler(const df::Event* p_e);

	// Get weapon type for bullet
	player_weapon getWeaponType();
};
