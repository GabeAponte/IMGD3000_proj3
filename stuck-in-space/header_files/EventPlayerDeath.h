// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// EventPlayerDeath.h
// Indicates that the player has died
//

#pragma once
#include <Event.h>

const std::string PLAYER_DEATH_EVENT = "playerdeath";

class EventPlayerDeath : public df::Event {
public:
	EventPlayerDeath();
};
