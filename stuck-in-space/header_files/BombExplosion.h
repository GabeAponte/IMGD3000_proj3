// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// BombExplosion.h
// Short-lived explosion 
//

#pragma once

#include "../header_files/Explosion.h"

class BombExplosion : public Explosion {

public:

	// Constructor with position of the bomb's spwan
	BombExplosion(df::Vector spawn_position);
};
