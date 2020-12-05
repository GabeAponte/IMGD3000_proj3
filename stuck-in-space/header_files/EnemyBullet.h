// Gabriel Aponte
// gaaponte@wpi.edu

//
// EnemyBullet.h
// Handles the logic for an Enemy bullet
//

#pragma once

#include <EventCollision.h>
#include <Object.h>

class EnemyBullet : public df::Object {

private:
	void out();
	void hit(const df::EventCollision* p_collision_event);

public:
	EnemyBullet();

	// Handle events
	int eventHandler(const df::Event* p_e);
};
