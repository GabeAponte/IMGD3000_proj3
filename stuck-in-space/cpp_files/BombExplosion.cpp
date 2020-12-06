// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// BombExplosion.cpp
// Short-lived explosion 
//
#include "EventStep.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "../header_files/BombExplosion.h"

BombExplosion::BombExplosion(df::Vector spawn_position) {

	// Link to "explosion" sprite.
	if (setSprite("bomb-explosion") == 0)
		timeToLive = getAnimation().getSprite()->getFrameCount()*2;
	else
		timeToLive = 0;

	setType("Bullet");

	setSolidness(df::SOFT);

	setPosition(spawn_position);
}