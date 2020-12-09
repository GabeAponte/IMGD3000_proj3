// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// BombExplosion.h
// Short-lived explosion 
//

#pragma once

#include "../header_files/Bullet.h"

class BombExplosion : public Bullet {

private:

	int timeToLive; // Duration to show explosion

	// Handles the step event
	void step();

public:

	// Constructor with position of the bomb's spwan
	BombExplosion(df::Vector spawn_position);

	// Handles events (OVERRIDE)
	int eventHandler(const df::Event* p_e);
};
