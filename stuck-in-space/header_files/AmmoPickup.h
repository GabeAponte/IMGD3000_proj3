// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// Gabriel Aponte
// gaaponte@wpi.edu

//
// AmmoExplosion.h
// Visual effect for pickup up an ammo box
//

#pragma once

#include "../header_files/Explosion.h"

class AmmoPickup : public Explosion {
public:
	AmmoPickup(df::Vector position);
};
