// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// Gabriel Aponte
// gaaponte@wpi.edu

//
// Handles GameOver functionality
//

#pragma once

#include "ViewObject.h"

class GameOver : public df::ViewObject {

private:

	int timeToLive;			// Rate at which to show GameOver
	df::Music* p_music;		// GameOver music

	// Handles the step event
	void step();

public:

	// Constructor and Deconstructor
	GameOver();
	~GameOver();

	// Handles events
	int eventHandler(const df::Event* p_e);

	// Draws the GameOver sprite
	int draw();
};
