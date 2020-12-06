// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// EventEnemyDeath.h
// Indicates an enemy died and records their location of death
//

#pragma once

#include <Event.h>
#include <Vector.h>

const std::string ENEMY_DEATH_EVENT = "enemydeath";

class EventEnemyDeath : public df::Event {

private:

	df::Vector deathPosition;	// Vector where the enemy died
	bool killedByPlayer;		// Indicates if the enemy died by the player

public:

	// Constructor that sets the death position and if the enemy was killed by a player
	EventEnemyDeath(df::Vector death_position, bool killed_by_player = false);

	// Get the death position
	df::Vector getPosition() const;

	// Get whether the player killed the enemy
	bool getDidPlayerKill() const;
};
