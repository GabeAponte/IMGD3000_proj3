// Gabriel Aponte
// gaaponte@wpi.edu

//
// Enemy.cpp
// Handles the logic for a Basic Enemy
//

#include <stdlib.h>
#include "EventCollision.h"
#include "EventOut.h"
#include "EventView.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "../header_files/Velocity.h"
#include "../header_files/Explosion.h"
#include "../header_files/Points.h"
#include "../header_files/Enemy.h"
#include "../header_files/EventEnemyDeath.h"
#include "../header_files/EventPlayerDeath.h"
#include "../header_files/EventOverloadShield.h"
#include <iostream>
#include <DisplayManager.h>
#include "../header_files/EnemyBullet.h"

using namespace df;

Enemy::Enemy(df::Vector start_pos, enemy_type e_type) {

	// Set object type.
	setType("Enemy");
	type = e_type;

	// Set type diffrences
	setEnemyTypeSpeed();
	setEnemyTypeSprite();
	setEnemyTypeHitPoints();

	// Initialize shared vars
	setSolidness(SOFT);
	setPosition(start_pos);
	killedByPlayer = false;
	targetHero(start_pos);
	fireCooldown = 0;
	stopMoving = false;
	canFire = false;
}

Enemy::~Enemy() {
	// Declare that the enemy died
	EventEnemyDeath eed(getPosition(), killedByPlayer);
	WM.onEvent(&eed);
}

// Handle event.
// Return 0 if ignored, else 1.
int Enemy::eventHandler(const df::Event* p_e) {

	// Collision event handler
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	//Overload event handler
	if (p_e->getType() == OVERLOAD_EVENT) {

		// Create explosion.
		Explosion* p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());

		// Delete self.
		WM.markForDelete(this);

		killedByPlayer = true;

		return 1;
	}

	// Out of bounds event handler
	if (p_e->getType() == df::OUT_EVENT) {
		WM.markForDelete(this);
		return 1;
	}

	// Player death event handler
	// Freeze in place and stop fire
	if (p_e->getType() == PLAYER_DEATH_EVENT) {
		setVelocity(Vector());
		canFire = false;
		return 1;
	}

	// Step event
	// Change direction of trickey based on step
	// Stop motion and fire for shooter
	if (p_e->getType() == STEP_EVENT) {

		if (type == E_SHOOTER) {

			if (distance(DM.spacesToPixels(getPosition()), DM.spacesToPixels(Vector(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2))) < 350 && !stopMoving)
			{
				setVelocity(Vector());
				stopMoving = true;
				canFire = true;
			}

			// Fire weapon
			if (fireCooldown > 0)
			{
				fireCooldown--;
			}
			else if (canFire) {
				fire();
			}

		}
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// Called with Enemy collides.
void Enemy::hit(const df::EventCollision* p_collision_event) {

	// If Bullet, reduce health and/or die
	if ((p_collision_event->getObject1()->getType() == "Bullet") ||
		(p_collision_event->getObject2()->getType() == "Bullet")) {

		hit_points--;

		if (hit_points <= 0) {

			// Create an explosion.
			Explosion* p_explosion = new Explosion;
			p_explosion->setPosition(this->getPosition());

			// Play "explode" sound
			df::Sound* p_sound = RM.getSound("explode");
			p_sound->play();

			killedByPlayer = true;

			WM.markForDelete(this);
		}
	}
}

// Set the direction of the enemy to point at the player (center of screen)
void Enemy::targetHero(df::Vector position)
{
	df::Vector dir = (Vector(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2) - position);
	dir = convertToDragonfly(dir);
	dir.normalize();
	dir.scale(realSpeed);
	dir = convertToReal(dir);
	setVelocity(dir);
}

// Sets the speed based of teh type of enemy
void Enemy::setEnemyTypeSpeed()
{
	switch (type)
	{
	case E_BASIC:
	{
		setRealSpeed(.35);
		break;
	}
	case E_TOUGH:
	{
		setRealSpeed(.30);
		break;
	}
	case E_FAST:
	{
		setRealSpeed(1);
		break;
	}
	case E_TRICKY:
	{
		setRealSpeed(.8);
		break;
	}
	case E_SPIRAL:
	{
		setRealSpeed(.35);
		break;
	}
	case E_SWARM:
	{
		setRealSpeed(.25);
		break;
	}
	case E_SHOOTER:
	{
		setRealSpeed(1);
		break;
	}
	}
}

// Sets the sprite based off the type of enemy
void Enemy::setEnemyTypeSprite()
{
	switch (type)
	{
	case E_BASIC:
	{
		setSprite("basic-enemy");
		break;
	}
	case E_TOUGH:
	{
		setSprite("tough-enemy");
		break;
	}
	case E_FAST:
	{
		setSprite("fast-enemy");
		break;
	}
	case E_TRICKY:
	{
		setSprite("tricky-enemy");
		break;
	}
	case E_SPIRAL:
	{
		setSprite("spiral-enemy");
		break;
	}
	case E_SWARM:
	{
		setSprite("swarm-enemy");
		break;
	}
	case E_SHOOTER:
	{
		setSprite("shooter-enemy");
		break;
	}
	}
}

// Sets the hit points based off the type of enemy
void Enemy::setEnemyTypeHitPoints()
{
	switch (type)
	{
	case E_BASIC:
	{
		hit_points = 1;
		break;
	}
	case E_TOUGH:
	{
		hit_points = 3;
		break;
	}
	case E_FAST:
	{
		hit_points = 1;
		break;
	}
	case E_TRICKY:
	{
		hit_points = 1;
		break;
	}
	case E_SPIRAL:
	{
		hit_points = 1;
		break;
	}
	case E_SWARM:
	{
		hit_points = 1;
		break;
	}
	case E_SHOOTER:
	{
		hit_points = 1;
		break;
	}
	}
}

// Fires a bullet from the Shooter type enemy
void Enemy::fire()
{
	// Update cooldown
	fireCooldown = 75;

	// Play appropriate fire sound for the current weapon
	//df::Sound* p_sound = RM.getSound("getone");
	//p_sound->play();

	// Calculate bullet velocity
	df::Vector v = Vector(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2) - getPosition(); // calculate aim vector
	v = convertToDragonfly(v);      // adjust aim for screen coordinates
	v.normalize();                  // convert aim to direction
	v.scale(1);                     // apply bullet speed
	v = convertToReal(v);           // adjust velocity for screen coordinates

	 // Fire Missile towards target
	EnemyBullet* bullet = new EnemyBullet();
	bullet->setVelocity(v);
	bullet->setPosition(getPosition());
	return;
}

// Set/get the enemy's real speed (df speed is unreliable)
void Enemy::setRealSpeed(float new_speed)
{
	realSpeed = new_speed;
}
float Enemy::getRealSpeed() const
{
	return realSpeed;
}