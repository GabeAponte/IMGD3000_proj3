// Gabriel Aponte
// gaaponte@wpi.edu

//
// EventOverloadShield.h
// Indicates the player overloaded their shield, a special attack that costs shield
// integrity but wipes the screen of enemies.
//

#pragma once

#include <Event.h>

const std::string OVERLOAD_EVENT = "overload";

class EventOverloadShield : public df::Event {

public:

	// Constructor
	EventOverloadShield();
};
