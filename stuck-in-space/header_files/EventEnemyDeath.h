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
	EventEnemyDeath(); // inaccessible
	df::Vector deathPosition;
	bool killedByPlayer;
public:
	EventEnemyDeath(df::Vector death_position, bool killed_by_player = false);

	// Get the death position
	df::Vector getPosition() const;

	// Get whether the player killed the enemy
	bool getDidPlayerKill() const;
};
