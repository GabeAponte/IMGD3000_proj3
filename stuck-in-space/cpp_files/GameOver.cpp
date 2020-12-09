// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// Gabriel Aponte
// gaaponte@wpi.edu

//
// Handles GameOver functionality
//

#include <EventStep.h>
#include <GameManager.h>
#include <LogManager.h>
#include <ResourceManager.h>
#include <WorldManager.h>
#include "../header_files/GameOver.h"
#include "../header_files/GameStart.h"
#include "../header_files/WaveController.h"
#include "../header_files/InputPlayerName.h"
#include "../header_files/MusicPlayer.h"

using namespace df;

GameOver::GameOver() {

	// Set type
	setType("GameOver");

	// Link to "message" sprite.
	if (setSprite("gameover") == 0) {
		timeToLive = getAnimation().getSprite()->getFrameCount() * 6;
	}
	else {
		timeToLive = 0;
	}

	// Put in center of window.
	setLocation(CENTER_CENTER);

	// Play hero died sound.
	Sound* p_sound = RM.getSound("hero-died");
	p_sound->play();

	// Gets how many waves the player cleared before dying
	setWavesSurvived();

	// Delete wave controller
	WM.deleteObjectsOfType("WaveController");
}

// When done, game over so shut down.
GameOver::~GameOver() {

	// Play game music
	MUSICPLAYER.playMusic();

	// Allow the player to record their score
	new InputPlayerName(wavesSurvived);
}

// Handle event.
// Return 0 if ignored, else 1.
int GameOver::eventHandler(const Event* p_e) 
{
	// Step handler
	if (p_e->getType() == STEP_EVENT) {
		step();
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// Count down to end of message.
void GameOver::step() 
{
	// Decrement rate
	timeToLive--;

	// Check if animation done
	if (timeToLive <= 0) {

		// Mark self for deletion
		WM.markForDelete(this);
	}
}

// Override default draw so as not to display "value".
int GameOver::draw() 
{
	Object::draw();
	return 0;
}

// Sets the value for wavesSurvived
void GameOver::setWavesSurvived()
{
	// Get the wave controller
	ObjectList ol = WM.objectsOfType("WaveController");
	ObjectListIterator oli(&ol);
	WaveController* p_wc = dynamic_cast <WaveController*> (oli.currentObject());

	// Display results and let player input highscores
	if (p_wc != nullptr)
	{
		wavesSurvived = p_wc->getWaveNumber() - 1;
	}
}
