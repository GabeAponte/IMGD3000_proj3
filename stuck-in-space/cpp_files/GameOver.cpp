// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// Gabriel Aponte
// gaaponte@wpi.edu

//
// Handles GameOver functionality
//

#include "EventStep.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "../header_files/GameOver.h"
#include "../header_files/GameStart.h"
#include "../header_files/WaveController.h"
#include "../header_files/InputPlayerName.h"

using namespace df;

GameOver::GameOver() {

	setType("GameOver");

	// Link to "message" sprite.
	if (setSprite("gameover") == 0)
		timeToLive = getAnimation().getSprite()->getFrameCount() * 15;
	else
		timeToLive = 0;

	// Put in center of window.
	setLocation(df::CENTER_CENTER);

	// Play "game over" sound.
	df::Sound* p_sound = RM.getSound("game over");
	p_sound->play();
}

// When done, game over so shut down.
GameOver::~GameOver() {
	// Clear view objects
	WM.deleteObjectsOfType("ViewObject");

	// Get the wave controller
	ObjectList ol = WM.objectsOfType("WaveController");
	ObjectListIterator oli(&ol);
	WaveController* p_wc = dynamic_cast <WaveController*> (oli.currentObject());

	// Display results and let player input highscores
	int wave = 1;
	if (p_wc != nullptr)
	{
		wave = p_wc->getWaveNumber() - 1;
	}
	new InputPlayerName(wave);

	// Delete wave controller
	WM.deleteObjectsOfType("WaveController");
}

// Handle event.
// Return 0 if ignored, else 1.
int GameOver::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// Count down to end of message.
void GameOver::step() {
	timeToLive--;
	if (timeToLive <= 0) {
		WM.markForDelete(this);
	}
}

// Override default draw so as not to display "value".
int GameOver::draw() {
	df::Object::draw();
	return 0;
}
