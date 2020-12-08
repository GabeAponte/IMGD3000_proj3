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

	// Set type differences
	hitPoints = 1;
	switch (type)
	{
	case E_BASIC:
	{
		setSprite("basic-enemy");
		setRealSpeed(.4);
		break;
	}
	case E_TOUGH:
	{
		setSprite("tough-enemy");
		setRealSpeed(.30);
		hitPoints = 3;
		break;
	}
	case E_FAST:
	{
		setSprite("fast-enemy");
		setBox(Box(Vector(-2.5, -1.5), 5, 3));
		setRealSpeed(1.2);
		break;
	}
	case E_TRICKY:
	{
		setSprite("tricky-enemy");
		setRealSpeed(0.7);
		break;
	}
	case E_SWARM:
	{
		setSprite("swarm-enemy");
		setBox(Box(Vector(-3.5, -2), 7, 4));
		setAnimationIndex(rand() % 4);
		setRealSpeed(.25);
		break;
	}
	case E_SHOOTER:
	{
		setSprite("shooter-enemy");
		setRealSpeed(1);
		break;
	}
	}

	// Initialize shared vars
	setSolidness(SOFT);
	setAltitude(3);
	setPosition(start_pos);
	targetHero(start_pos);
	canFire = false;
	fireCooldown = FIRE_COOLDOWN/2;
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

		// Check if damage needs to be taken and then reset toogle if so
		if (takeDamage) {
			hitPoints--;
			takeDamage = false;
		}

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
			Vector pixel_position = DM.spacesToPixels(getPosition());
			Vector pixel_center = DM.spacesToPixels(Vector(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2));
			if (canMove && abs(pixel_position.getY()-pixel_center.getY()) < SHOOTER_STOP_YDISTANCE && distance(pixel_position, pixel_center) < SHOOTER_STOP_RADIUS) {

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

		// Remove hitpoints
		takeDamage = true;

		std::cout << "hit" << "\n";

		// Set wasHit to true for 'tough' so that sprite updates and play tough hit sound if still has health
		if (type == E_TOUGH) {
			wasHit = true;

			if (hitPoints > 0) {
				// Play tough-hit sound
				df::Sound* p_sound = df::RM.getSound("tough-hit");
				p_sound->play();
			}
		}

		
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
	fireCooldown = FIRE_COOLDOWN;

	// Play enemy bullet sound
	df::Sound* p_sound = df::RM.getSound("enemy-bullet");
	p_sound->play();

	// Calculate bullet velocity
	df::Vector v = Vector(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2) - getPosition(); // calculate aim vector
	v = convertToDragonfly(v);      // adjust aim for screen coordinates
	v.normalize();                  // convert aim to direction
	v.scale(0.5);                     // apply bullet speed
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