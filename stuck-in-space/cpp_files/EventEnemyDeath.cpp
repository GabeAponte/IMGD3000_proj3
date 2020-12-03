// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// EventEnemyDeath.cpp
// Indicates an enemy died and records their location of death
//

#include "../header_files/EventEnemyDeath.h"

// inaccessible
EventEnemyDeath::EventEnemyDeath() {};

// this constructor is required
EventEnemyDeath::EventEnemyDeath(df::Vector death_position) {
    setType(ENEMY_DEATH_EVENT);
    m_death_position = death_position;
}

// Get the death position
df::Vector EventEnemyDeath::getPosition()
{
    return m_death_position;
}