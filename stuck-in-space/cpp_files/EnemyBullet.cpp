// Gabriel Aponte
// gaaponte@wpi.edu

//
// EnemyBullet.h
// Handles the logic for an Enemy bullet
//

#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "../header_files/EnemyBullet.h"
#include "../header_files/EventOverloadShield.h"

using namespace df;

EnemyBullet::EnemyBullet() {

	// Link to "enemy-bullet" sprite.
	setSprite("enemy-bullet");

	// Set other object properties.
	setType("EnemyBullet");

	// Set to SOFT
	setSolidness(TANGIBLE);
}

// Handle event.
// Return 0 if ignored, else 1.
int EnemyBullet::eventHandler(const df::Event* p_e) 
{
	// Out of bounds event handler
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	// Collisions event handler
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	// Overload event handler
	if (p_e->getType() == OVERLOAD_EVENT) {

		// Delete self.
		WM.markForDelete(this);
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// If EnemyBullet moves outside world, mark self for deletion.
void EnemyBullet::out() 
{
	WM.markForDelete(this);
}

// If EnemyBullet hits hero or hero's bullet, mark for deletion.
void EnemyBullet::hit(const df::EventCollision* p_collision_event) 
{
	bool hit_bullet = (p_collision_event->getObject1()->getType() == "Bullet") || (p_collision_event->getObject2()->getType() == "Bullet");
	
	// Check if collided with hero or a bullet
	if ((p_collision_event->getObject1()->getType() == "Hero") || (p_collision_event->getObject2()->getType() == "Hero") || hit_bullet) {

		if (hit_bullet)
		{
			// Play "counter-bullet" sound
			df::Sound* p_sound = RM.getSound("counter-bullet");
			p_sound->play();
		}
	
		WM.markForDelete(this);
	}
}