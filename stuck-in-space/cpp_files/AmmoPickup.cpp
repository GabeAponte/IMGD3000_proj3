// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// Gabriel Aponte
// gaaponte@wpi.edu

//
// AmmoExplosion.cpp
// Visual effect for pickup up an ammo box
//

#include "../header_files/AmmoPickup.h"

AmmoPickup::AmmoPickup(df::Vector position) : Explosion("ammo-pickup") {
	// Set position
	setPosition(position);
}