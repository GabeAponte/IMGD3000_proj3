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

	// Check if there is a bomb on screen already
	if (activeBomb != NULL) {

		// Detonate existing bomb
		activeBomb->explode();

		// Remove self
		WM.markForDelete(this);
	}
	else {

		// There is no bomb, so store self as the active bomb
		activeBomb = this;

		// Setup as bomb
		setSprite("w_bomb");
		setType("Bullet");
	}

	// Set to SOFT
	setSolidness(SOFT);

	// Set the weapon type
	weaponType = W_BOMB;
}

Bomb::~Bomb() {

	activeBomb = NULL;
}

// Handle event.
// Return 0 if ignored, else 1.
int Bomb::eventHandler(const df::Event* p_e) 
{
	// Out of bounds handler
	if (p_e->getType() == OUT_EVENT) {
		out();
		return 1;
	}

	// Collisions handler
	if (p_e->getType() == COLLISION_EVENT) {
		const EventCollision* p_collision_event = dynamic_cast <const EventCollision*> (p_e);
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

		explode();
	}
}

// Detonates the bomb
void Bomb::explode()
{
	// Delete this projectile object
	WM.markForDelete(this);

	// Spawn a big explosion
	new BombExplosion(getPosition() + getVelocity());
}

// Remotely detonate the current bomb, if present
void Bomb::detonate()
{
	if (activeBomb != NULL) {
		activeBomb->explode();
	}
}

// Check if there is an active bomb
bool Bomb::isActive()
{
	return activeBomb != NULL;
}