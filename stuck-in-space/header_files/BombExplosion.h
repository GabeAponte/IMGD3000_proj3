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
	BombExplosion(df::Vector spawn_position);
};
