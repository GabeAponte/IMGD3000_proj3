// Gabriel Aponte
// gaaponte@wpi.edu

//
// Enemy.h
// Handles the logic for a Basic Enemy
//

#pragma once

#include "Object.h"
#include "EventCollision.h"
#include "../header_files/WaveController.h"

#define FIRE_COOLDOWN 75
#define SHOOTER_STOP_RADIUS    325 // The radial distance from the center of the screen (in pixels) at which the shooter stops to attack
#define SHOOTER_STOP_YDISTANCE 225 // The vertical distance... (see above)  

class Enemy : public df::Object {

private:

	float realSpeed;		// Speed value
	int hitPoints;			// HP - health value
	enemy_type type;		// Type of enemy (Enum from WaveController)
	bool killedByPlayer;    // Indicates if playee destoyed this enemy
	bool canMove;			// Toggles movement
	bool canZigZag;			// Toggles zig zag movement for 'tricky' enemy
	bool canFire;			// Toggles the fire ability for 'shooter enemy
	int fireCooldown;		// Rate of fire value
	int stepCounter;		// Tracks the step events this enemy has experienced
	int rotationIndex;		// Tracks which rotation to apply when zig zaging
	bool wasHit;			// Tracks if the enemy was hit (used to change sprite of 'tough' enemy)
	int hitCooldown;		// Rate at which to flicker the sprite chnage for 'tough' enemy
	int takeDamage;			// Toggles the removal of a hit point;

	// Handle collision events between player and bullets
	void hit(const df::EventCollision* p_collision_event);

	// Set the velocity to be towards the player
	void targetHero(df::Vector position);

	// Applies the zig zag movement for 'tricky' enemy
	void applyZigZagMovement();

	// Fires and EnemyBullet for 'shooter' enemy
	void fire();

public:

	// Constructor that sets the start position and the enemy type
	Enemy(df::Vector start_pos, enemy_type e_type);
	~Enemy();

	// Handles events
	int eventHandler(const df::Event* p_e);

	// Set/get the enemy's real speed (df speed is unreliable)
	void setRealSpeed(float new_speed);
	float getRealSpeed() const;
};
