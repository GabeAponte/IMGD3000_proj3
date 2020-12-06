// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// Ammo.h
// An ammo pickup, with different weapon types assignable
//

#pragma once

#include <EventCollision.h>
#include <Object.h>
#include "../header_files/Hero.h"

#define DECAY_TIME 210

class Ammo : public df::Object {

private:
	player_weapon ammoType; // The type of ammo the pickup will provide
	char ammoChar;          // The character id of ammo type
	int ammoValue;          // The amount of ammo to pickup
	int decayTimer;         // The timer determining when the ammo despawns

	// Handle decay timer
	void step();

	// Handle collision with Bullet
	void hit(const df::EventCollision* p_collision_event);

public:

	// Constructor that requires initial values
	Ammo(df::Vector position, player_weapon ammo_type, int ammo_value);

	// Handle events
	int eventHandler(const df::Event* p_e);

	// Draw (OVERRIDE)
	int draw();
};
