// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// EventAmmo.cpp
// Indicates that the player collected ammo for a certain weapon
//

#include "../header_files/EventAmmo.h"

// inaccessible
EventAmmo::EventAmmo() {};

// this constructor is required
EventAmmo::EventAmmo(player_weapon ammo_type, int ammo_value) {
	setType(AMMO_EVENT);
	ammoType = ammo_type;
	ammoValue = ammo_value;
}


// Get the type of ammo
player_weapon EventAmmo::getAmmoType() const
{
	return ammoType;
}


// Get the amount of ammo
int EventAmmo::getAmmoValue() const
{
	return ammoValue;
}
