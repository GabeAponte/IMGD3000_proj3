// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// Gabriel Aponte
// gaaponte@wpi.edu

//
// Handles GameStart functionality
//

#pragma once

#include "Music.h"
#include "ViewObject.h"

class GameStart : public df::ViewObject {

private:

	df::Music* p_music; // GameStart music

	// Handles starting the game
	void start();

public:

	// Constructor
	GameStart();

	// Handles events
	int eventHandler(const df::Event* p_e);

	// Draws the start menue
	int draw();

	// Plays the start music
	void playMusic();
};
