// Gabriel Aponte
// gaaponte@wpi.edu

//
// EnemyBullet.h
// Handles the logic for an Enemy bullet
//

#pragma once

#include <Object.h>
#include <EventCollision.h>

class EnemyBullet : public df::Object {

private:

	// Handles out of bounds event
	void out();

	// Handles collisions with the player and bullets
	void hit(const df::EventCollision* p_collision_event);

public:

	// Constructor
	EnemyBullet();

	// Handle events
	int eventHandler(const df::Event* p_e);
};
