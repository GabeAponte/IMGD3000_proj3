// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// Bullet.cpp
//

#include <iostream>

#include <LogManager.h>
#include <WorldManager.h>
#include <ResourceManager.h>
#include <EventOut.h>
#include "../header_files/Enemy.h"
#include "../header_files/Bullet.h"

using namespace df;

Bullet::Bullet(player_weapon weapon_type) {

	// Set other object properties.
	setType("Bullet");

	// Set to SOFT
	setSolidness(SOFT);

	// Set the weapon type
	// NOTE: All weapon attacks should have the "Bullet" type to allow general collision
	weaponType = weapon_type;
}

// Handle event.
// Return 0 if ignored, else 1.
int Bullet::eventHandler(const df::Event* p_e) 
{
	// Out of bounds handler
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	// Collisions handler
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// If Bullet moves outside world, mark self for deletion.
void Bullet::out() 
{
	WM.markForDelete(this);
}

// If Bullet hits Enemy, mark Enemy and Bullet for deletion.
void Bullet::hit(const df::EventCollision* p_collision_event) 
{
	// Check if collided with an Enemy or enemy bullet
	if ((p_collision_event->getObject1()->getType() == "Enemy") || (p_collision_event->getObject2()->getType() == "Enemy")
		|| (p_collision_event->getObject1()->getType() == "EnemyBullet") || (p_collision_event->getObject2()->getType() == "EnemyBullet")) {

		// Delete this projectile object unless weapon type is piercing
		if (weaponType != W_LASER && weaponType != W_PLASMA)
		{
			WM.markForDelete(this);
		}
	}
}

// Get bullet type
player_weapon Bullet::getWeaponType()
{
	return weaponType;
}