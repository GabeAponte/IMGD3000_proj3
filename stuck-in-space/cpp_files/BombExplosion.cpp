// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// BombExplosion.cpp
// Short-lived explosion 
//

#include <iostream>
#include <EventStep.h>
#include <GameManager.h>
#include <LogManager.h>
#include <ResourceManager.h>
#include <WorldManager.h>
#include "../header_files/BombExplosion.h"

using namespace df;

BombExplosion::BombExplosion(df::Vector spawn_position) : Bullet(W_BOMB) {

	// Link to "bomb-explosion" sprite and regulate animation
	if (setSprite("bomb-explosion") == 0)
	{
		timeToLive = getAnimation().getSprite()->getFrameCount() * 2;

		// Use a big hitbox
		setBox(Box(Vector(-9.5, -4.5), 19, 9));
	}
	else {
		timeToLive = 0;
	}

	// Play explosion sound
	Sound* p_sound = RM.getSound("bomb-explosion");
	p_sound->play();

	// Set initial spawn position
	setPosition(spawn_position);

	// Set to always collide 
	setAlwaysCollide(true);
}

// Handle event.
// Return 0 if ignored, else 1.
int BombExplosion::eventHandler(const df::Event* p_e)
{
	// Step handler
	if (p_e->getType() == STEP_EVENT) {
		step();
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// Count down until explosion finished.
void BombExplosion::step()
{
	// Decrement timer
	timeToLive--;

	// Check if explosion is over
	if (timeToLive <= 0) {
		WM.markForDelete(this);
	}
}
