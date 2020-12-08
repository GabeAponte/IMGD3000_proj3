// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// BombExplosion.cpp
// Short-lived explosion 
//

#include <EventStep.h>
#include <GameManager.h>
#include <LogManager.h>
#include <ResourceManager.h>
#include <WorldManager.h>
#include "../header_files/BombExplosion.h"

BombExplosion::BombExplosion(df::Vector spawn_position) {

	// Link to "bomb-explosion" sprite and regulate animation
	if (setSprite("bomb-explosion") == 0)
	{
		timeToLive = getAnimation().getSprite()->getFrameCount() * 2;
		// use big hitbox
		setBox(df::Box(df::Vector(-9.5, -4.5), 19, 9));
	}
	else 
	{
		timeToLive = 0;
	}

	// Play explosion sound
	df::Sound* p_sound = df::RM.getSound("bomb-explosion");
	p_sound->play();

	// Set to type bullet
	setType("Bullet");

	// Set to be SOFT
	setSolidness(df::SOFT);

	// Set initial spawn position
	setPosition(spawn_position);
}