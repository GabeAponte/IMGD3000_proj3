//
// Explosion.h
//

#pragma once

#include "Object.h"

class Explosion : public df::Object {

protected:

	int timeToLive; // Rate of which to play explosion

	// Handles the step event
	void step();

public:

	// Constructor
	Explosion();

	// Handles events
	int eventHandler(const df::Event* p_e);
};
