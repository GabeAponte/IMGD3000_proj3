// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// EventEnemyDeath.h
// Indicates an enemy died and records their location of death
//

#pragma once
#include <Event.h>
#include <Vector.h>

const std::string ENEMY_DEATH_EVENT =  "enemydeath";

class EventEnemyDeath : public df::Event {
 private:
    EventEnemyDeath(); // inaccessible
    df::Vector m_death_position;
 public:
    EventEnemyDeath(df::Vector death_position);

    // Get the death position
    df::Vector getPosition();
};
