// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// Gabriel Aponte
// gaaponte@wpi.edu

//
// Explosion.h
//

#pragma once

#include "Object.h"

class Explosion : public df::Object {

protected:

	int timeToLive; // Rate at which to show explosion

	// Handles the step event
	void step();

public:

	// Constructor
	Explosion();

	// Handles events
	int eventHandler(const df::Event* p_e);
};
