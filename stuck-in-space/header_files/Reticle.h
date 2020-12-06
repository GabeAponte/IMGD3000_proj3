// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// Gabriel Aponte
// gaaponte@wpi.edu

//
// Reticle.h
//

#pragma once

#include "Object.h"

#define RETICLE_CHAR '+'

class Reticle : public df::Object {

public:

	// Constructor 
	Reticle();

	// Draws the recticle
	int draw(void);

	// Handles events
	int eventHandler(const df::Event* p_e);
};
