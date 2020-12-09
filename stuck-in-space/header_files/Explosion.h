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

	int timeToLive; // Duration to show explosion

	// Handles the step event
	void step();

public:

	// Constructor
	Explosion(std::string type="explosion");

	// Handles events
	int eventHandler(const df::Event* p_e);
};
