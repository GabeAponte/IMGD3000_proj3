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
#include "../header_files/Bullet.h"
#include "../header_files/EventEnemyDeath.h"
#include "../header_files/EventPlayerDeath.h"
#include "../header_files/EventOverloadShield.h"
#include "../header_files/EnemyBullet.h"
#include "../header_files/Enemy.h"

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
		setRealSpeed(0.3);
		break;
	}
	case E_TOUGH:
	{
		setSprite("tough-enemy");
		setRealSpeed(0.2);
		hitPoints = 3;
		break;
	}
	case E_FAST:
	{
		setSprite("fast-enemy");
		setBox(Box(Vector(-2.5, -1.5), 5, 3));
		setRealSpeed(1);
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
		setRealSpeed(0.25);
		break;
	}
	case E_SHOOTER:
	{
		setSprite("shooter-enemy");
		setRealSpeed(0.8);
		break;
	}
	}

	// Initialize shared vars
	setSolidness(TANGIBLE);
	setAltitude(3);
	setPosition(start_pos);
	targetHero(start_pos);
	canFire = false;
	fireCooldown = FIRE_COOLDOWN/2;
	canMove = true;
	canZigZag = false;
	stepCounter = 0;
	rotationIndex = 0;
	hitCooldown = 3;
	killedByPlayer = false;
	canTakeDamage = false;
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
	if (p_e->getType() == COLLISION_EVENT) {
		const EventCollision* p_collision_event = dynamic_cast <EventCollision const*> (p_e);
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
	if (p_e->getType() == OUT_EVENT) {
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

		// Become vulnerable again every step
		if (!canTakeDamage) {
			canTakeDamage = true;
		}
		
		// If TOUGH, reset sprite after hit cooldown
		if (type == E_TOUGH) {

			if (hitCooldown > 0)
			{
				hitCooldown--;
				if (hitCooldown <= 0) {
					setSprite("tough-enemy");
				}
			}
		}

		// If shooter, stop movement once close enough to the center of the screen
		if (type == E_SHOOTER) {
			Vector pixel_position = DM.spacesToPixels(getPosition());
			Vector pixel_center = WM.getBoundary().getCorner() + DM.spacesToPixels(Vector(WM.getBoundary().getHorizontal() / 2, (WM.getBoundary().getVertical() / 2) - 2));
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
	
	// If get here, we have ignored this event.
	return 0;
}

// Called with Enemy collides, handles collisions
void Enemy::hit(const df::EventCollision* p_collision_event) 
{	
	bool first_bullet = (p_collision_event->getObject1()->getType() == "Bullet");
	bool second_bullet = (p_collision_event->getObject2()->getType() == "Bullet");
	// If Bullet, reduce health and/or die
	if (first_bullet || second_bullet) {

		if (canTakeDamage)
		{
			// Take damage
			hitPoints--;

			// Become invulnerable until next step
			canTakeDamage = false;

			// Let 'tough' update its sprite and play tough hit sound if still has health
			if (type == E_TOUGH) {

				// Instantly die to weapons its weak to
				Bullet* p_bullet;

				// Set a bullet object to compare the type with
				if (first_bullet) {
					p_bullet = dynamic_cast <Bullet*> (p_collision_event->getObject1());
				}
				else {
					p_bullet = dynamic_cast <Bullet*> (p_collision_event->getObject2());
				}

				// Laser and bomb will always destroy the tough enemy
				if (p_bullet->getWeaponType() == W_LASER || p_bullet->getWeaponType() == W_BOMB) {
					hitPoints = 0;
				}

				// Show damage taken
				if (hitPoints > 0) {

					// Play tough-hit sound
					Sound* p_sound = RM.getSound("tough-hit");
					p_sound->play();
					setSprite("tough-enemy-hit");
					hitCooldown = HIT_COOLDOWN;
				}
			}
			
			// Check if now dead
			if (hitPoints <= 0) {

				// Create an explosion.
				Explosion* p_explosion = new Explosion;
				p_explosion->setPosition(this->getPosition());

				// Play "explode" sound
				Sound* p_sound = RM.getSound("explode");
				p_sound->play();

				// Mark killed by player
				killedByPlayer = true;

				// Delete self
				WM.markForDelete(this);
			}
		}
	}
}

// Set the direction of the enemy to point at the player (center of screen)
void Enemy::targetHero(df::Vector position)
{
	Vector dir = WM.getBoundary().getCorner() + Vector(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2) - position;
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
	Vector v = convertToDragonfly(getVelocity());

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
	Sound* p_sound = RM.getSound("enemy-bullet");
	p_sound->play();

	// Calculate bullet velocity
	Vector v = WM.getBoundary().getCorner() + Vector(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2) - getPosition(); // calculate aim vector
	v = convertToDragonfly(v);      // adjust aim for screen coordinates
	v.normalize();                  // convert aim to direction
	v.scale(0.5);                   // apply bullet speed
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