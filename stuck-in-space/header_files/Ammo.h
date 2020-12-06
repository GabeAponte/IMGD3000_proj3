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
	player_weapon ammoType; // the type of ammo the pickup will provide
	char ammoChar;          // the character id of ammo type
	int ammoValue;          // the amount of ammo to pickup
	int decayTimer;         // the timer determining when the ammo despawns

	Ammo(); // inaccessible

	// Handle decay timer
	void step();

	// Handle collision with Bullet
	void hit(const df::EventCollision* p_collision_event);

public:
	// constructor requires initial values
	Ammo(df::Vector position, player_weapon ammo_type, int ammo_value);

	// Handle events
	int eventHandler(const df::Event* p_e);

	// Draw (OVERRIDE)
	int draw();
};
