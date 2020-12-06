// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// EventAmmo.h
// Indicates that the player collected ammo for a certain weapon
//

#pragma once

#include <Event.h>
#include <Vector.h>
#include "../header_files/Hero.h"

const std::string AMMO_EVENT = "ammo";

class EventAmmo : public df::Event {

private:

	player_weapon ammoType; // Type of ammo pick up
	int ammoValue; // Amount of ammo

public:

	// Constructor requires initial values
	EventAmmo(player_weapon ammo_type, int ammo_value);

	// Get the type of ammo
	player_weapon getAmmoType() const;

	// Get the amount of ammo
	int getAmmoValue() const;
};
