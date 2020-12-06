// Gabriel Aponte
// gaaponte@wpi.edu

//
// Enemy.cpp
// Handles the logic for a Basic Enemy
//

#include <iostream>
#include <stdlib.h>
#include <DisplayManager.h>
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
	targetHero(start_pos);
	canFire = false;
	fireCooldown = 0;
	canMove = true;
	canZigZag = false;
	stepCounter = 0;
	rotationIndex = 0;
	wasHit = false;
	hitCooldown = 3;
	killedByPlayer = false;
}

Enemy::~Enemy() {

	// Declare that the enemy died
	EventEnemyDeath eed(getPosition(), killedByPlayer);
	WM.onEvent(&eed);
}

// Handle event.
// Return 0 if ignored, else 1.
int Enemy::eventHandler(const df::Event* p_e) 
{
	// Collision event handler
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	//Overload event handler
	if (p_e->getType() == OVERLOAD_EVENT) {

		// Create explosion
		Explosion* p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());

		// Delete self
		WM.markForDelete(this);

		// Mark killed by player
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
		canMove = false;
		return 1;
	}

	// Step event
	// Change direction of trickey based on step
	// Stop motion and fire for shooter
	// Regulate 'tough' sprite color
	if (p_e->getType() == STEP_EVENT) {

		// If tough, set sprite when hit
		if (type == E_TOUGH) {

			if (wasHit) {
				setSprite("tough-enemy-hit");
				hitCooldown--;
			}
			if (hitCooldown == 0) {
				setSprite("tough-enemy");
				hitCooldown = 3;
				wasHit = false;
			}
		}

		// If shooter, stop movement once close enough to the center of the screen
		if (type == E_SHOOTER) {

			if (distance(DM.spacesToPixels(getPosition()), DM.spacesToPixels(Vector(WM.getBoundary().getHorizontal() / 2, 
				WM.getBoundary().getVertical() / 2))) < 325 && canMove) {

				setVelocity(Vector()); // stop movement
				canMove = false;
				canFire = true; // set fire bool
			}

			// Fire weapon if cooldown allows
			if (fireCooldown > 0) {
				fireCooldown--;
			}
			else if (canFire) {
				fire();
			}
		}

		// Apply zig zag on step for tricky enemy
		if (type == E_TRICKY) {
			stepCounter++; // regulates rate of direction change

			// Check that the enemy has entered the world bounds
			if (boxIntersectsBox(Box(Vector(10, 3), 100, 30), getWorldBox(this)) && !canZigZag) {
				canZigZag = true;
			}

			// Apply zig zag movement if inside world bounds
			if (canZigZag && canMove) {
				applyZigZagMovement();
			}
		}
		return 1;
	}
	
	// If get here, have ignored this event.
	return 0;
}

// Called with Enemy collides, handles collisions
void Enemy::hit(const df::EventCollision* p_collision_event) 
{
	// If Bullet, reduce health and/or die
	if ((p_collision_event->getObject1()->getType() == "Bullet") ||
		(p_collision_event->getObject2()->getType() == "Bullet")) {

		// Set wasHit to true for 'tough' so that sprite updates
		if (type == E_TOUGH) {
			wasHit = true;
		}

		// Remove hitpoints
		hitPoints--;

		// Check if now dead
		if (hitPoints <= 0) {

			// Create an explosion.
			Explosion* p_explosion = new Explosion;
			p_explosion->setPosition(this->getPosition());

			// Play "explode" sound
			df::Sound* p_sound = RM.getSound("explode");
			p_sound->play();

			// Mark killed by player
			killedByPlayer = true;

			// Delete self
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
		setRealSpeed(1.5);
		break;
	}
	case E_TRICKY:
	{
		setRealSpeed(1);
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
		hitPoints = 1;
		break;
	}
	case E_TOUGH:
	{
		hitPoints = 3;
		break;
	}
	case E_FAST:
	{
		hitPoints = 1;
		break;
	}
	case E_TRICKY:
	{
		hitPoints = 1;
		break;
	}
	case E_SWARM:
	{
		hitPoints = 1;
		break;
	}
	case E_SHOOTER:
	{
		hitPoints = 1;
		break;
	}
	}
}

// Changes the veclocity of tricky to the current diagonal every 15 steps
// Last rotation will target enemy directly
void Enemy::applyZigZagMovement()
{
	df::Vector v = convertToDragonfly(getVelocity());

	if (stepCounter >= 15 && rotationIndex == 0) {
		v = rotateVector(v, 45);
		setVelocity(convertToReal(v));
		rotationIndex = 1;
		stepCounter = 0;
	}

	if (stepCounter >= 15 && rotationIndex == 1) {
		v = rotateVector(v, -90);
		setVelocity(convertToReal(v));
		stepCounter = 0;
		rotationIndex = 2;
	}

	if (stepCounter >= 15 && rotationIndex == 2) {
		v = rotateVector(v, 45);
		setVelocity(convertToReal(v));
		stepCounter = 0;
		rotationIndex = 3;
	}

	if (stepCounter >= 15 && rotationIndex == 3) {
		v = rotateVector(v, -90);
		setVelocity(convertToReal(v));
		rotationIndex = 4;
		stepCounter = 0;
	}

	if (stepCounter >= 15 && rotationIndex == 4) {
		v = rotateVector(v, 45);
		setVelocity(convertToReal(v));
		stepCounter = 0;
		rotationIndex = 5;
	}

	if (stepCounter >= 15 && rotationIndex == 5) {
		v = rotateVector(v, 90);
		setVelocity(convertToReal(v));
		stepCounter = 0;
		rotationIndex = 6;
	}

	if (stepCounter >= 15 && rotationIndex == 6) {
		targetHero(getPosition());
		stepCounter = 0;
		rotationIndex = 7;
	}
}

// Fires a bullet from the Shooter type enemy
void Enemy::fire()
{
	// Update cooldown
	fireCooldown = 75;

	// TODO: Play appropriate fire sound for the current weapon
	// df::Sound* p_sound = RM.getSound("getone");
	// p_sound->play();

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

// Set the enemy's real speed (df speed is unreliable)
void Enemy::setRealSpeed(float new_speed)
{
	realSpeed = new_speed;
}

// Get the enemy's real speed (df speed is unreliable)
float Enemy::getRealSpeed() const
{
	return realSpeed;
}