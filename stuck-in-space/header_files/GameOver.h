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
	int timeToLive;
	df::Music* p_music;
	void step();

public:
	GameOver();
	~GameOver();
	int eventHandler(const df::Event* p_e);
	int draw();
};
