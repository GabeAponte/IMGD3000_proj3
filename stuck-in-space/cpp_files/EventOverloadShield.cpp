// Gabriel Aponte
// gaaponte@wpi.edu

//
// EventOverloadShield.cpp
// Indicates the player overloaded their shield, a special attack that costs shield
// integrity but wipes the screen of enemies.
//

#include "../header_files/EventOverloadShield.h"

EventOverloadShield::EventOverloadShield() {

	// Set type
	setType(OVERLOAD_EVENT);
}
