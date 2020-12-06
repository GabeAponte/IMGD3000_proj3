// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// Bomb.cpp
// Variation of Bomb that destroys a lot of enemies at once on impact
//

#include <EventOut.h>
#include <WorldManager.h>
#include "../header_files/Enemy.h"
#include "../header_files/BombExplosion.h"
#include "../header_files/Bomb.h"

using namespace df;

Bomb::Bomb() {

	// Link to bomb sprite.
	setSprite("w_bomb");

	// Set other object properties.
	setType("Bullet");

	setSolidness(SOFT);

	// Set the weapon type
	weaponType = W_BOMB;
}

// Handle event.
// Return 0 if ignored, else 1.
int Bomb::eventHandler(const df::Event* p_e) 
{
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// If Bomb hits Enemy, mark Enemy and Bomb for deletion.
void Bomb::hit(const df::EventCollision* p_collision_event) 
{
	// Check if collided with an Enemy or enemy Bomb
	if ((p_collision_event->getObject1()->getType() == "Enemy") || (p_collision_event->getObject2()->getType() == "Enemy")
		|| (p_collision_event->getObject1()->getType() == "EnemyBullet") || (p_collision_event->getObject2()->getType() == "EnemyBullet")) {

		// Delete this projectile object
		WM.markForDelete(this);

		// Spawn a big explosion
		new BombExplosion(getPosition()+getVelocity());
	}
}