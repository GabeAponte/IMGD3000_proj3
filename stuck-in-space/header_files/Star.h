// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// Star.h
//

#pragma once

#include "Object.h"

class Star : public df::Object {

private:

	// Out of bounds event handler
	void out();

public:

	// Constructor
	Star();

	// Handles events
	int eventHandler(const df::Event* p_e);
};
