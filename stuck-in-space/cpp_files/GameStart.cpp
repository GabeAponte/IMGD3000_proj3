// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// Gabriel Aponte
// gaaponte@wpi.edu

//
// Handles GameStart functionality
//

#include "Color.h"
#include "Music.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "../header_files/GameStart.h"
#include "../header_files/Hero.h"
#include "../header_files/Points.h"
#include "../header_files/Enemy.h"
#include "../header_files/WaveController.h"
#include "../header_files/Leaderboard.h"
#include "../header_files/MusicPlayer.h"

using namespace df;

GameStart::GameStart() {

	// Delete left over game objects
	WM.deleteObjectsOfType("Enemy");
	WM.deleteObjectsOfType("Ammo");

	// Set type
	setType("GameStart");

	// Link to "gamestart" sprite.
	setSprite("gamestart");

	// Put in center of screen.
	setLocation(CENTER_CENTER);

	// Play game music.
	MUSICPLAYER.playMusic();
}

// Handle event.
// Return 0 if ignored, else 1.
int GameStart::eventHandler(const df::Event* p_e) 
{
	// Keyboard handler
	if (p_e->getType() == KEYBOARD_EVENT) {
		EventKeyboard* p_keyboard_event = (EventKeyboard*) p_e;
		if (p_keyboard_event->getKeyboardAction() == KEY_PRESSED)
			switch (p_keyboard_event->getKey()) {

			// Enter : Play (P also supported)
			case Keyboard::RETURN:
			case Keyboard::P:
				start();
				break;

			// Escape : Quit
			case Keyboard::ESCAPE:
				GM.setGameOver();
				break;

			// L : Show Leaderboard
			case Keyboard::L: {
				Sound* p_sound = RM.getSound("select");
				p_sound->play();
				new Leaderboard();
				WM.markForDelete(this);
			}
				break;
			default:
				break;
			}
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// Starts the game
void GameStart::start() 
{
	// Pause game music.
	MUSICPLAYER.pauseMusic();

	// Play game start sound
	Sound* p_sound = RM.getSound("game-start");
	p_sound->play();

	// Create Wave Controller
	new WaveController;

	// Create hero.
	new Hero;

	// When game starts, destroy this object.
	WM.markForDelete(this);
}

// Override default draw so as not to display "value".
int GameStart::draw() 
{
	Object::draw();
	return 0;
}
