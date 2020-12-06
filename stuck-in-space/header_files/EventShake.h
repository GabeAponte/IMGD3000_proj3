// Gabriel Aponte
// gaaponte@wpi.edu

//
// EventShake.h
// Indicates that the player has been hit and the screen should shake
//

#pragma once
#include <Event.h>

const std::string SHAKE_EVENT = "shake";

class EventShake : public df::Event {
public:
	EventShake();
};

