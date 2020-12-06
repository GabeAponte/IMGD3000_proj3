// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// EventEnemyDeath.cpp
// Indicates an enemy died and records their location of death
//

#include "../header_files/EventEnemyDeath.h"

EventEnemyDeath::EventEnemyDeath(df::Vector death_position, bool killed_by_player) {
	setType(ENEMY_DEATH_EVENT);
	deathPosition = death_position;
	killedByPlayer = killed_by_player;
}


// Get the death position
df::Vector EventEnemyDeath::getPosition() const
{
	return deathPosition;
}


// Get whether the player killed the enemy
bool EventEnemyDeath::getDidPlayerKill() const
{
	return killedByPlayer;
}