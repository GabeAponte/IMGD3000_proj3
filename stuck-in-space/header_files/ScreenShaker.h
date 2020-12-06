// Gabriel Aponte
// gaaponte@wpi.edu

//
// ScreenShaker.h
// Invisible object that will shake the screen
//

#pragma once

#include "Object.h"

class ScreenShaker : public df::Object {

public:

	// Constructor
	ScreenShaker();

private:

	int shakeIndex; // Indicates which velocity to apply to the shake
	bool canShake;  // Toggles the ability to shake the screen

	// Handles events
	int eventHandler(const df::Event* p_e);
};

