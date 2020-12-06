// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// Gabriel Aponte
// gaaponte@wpi.edu

//
// Handles the Hero functionality
//

#pragma once

#include <map>
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventCollision.h"
#include "Object.h"
#include "Reticle.h"

#define FAR_LOOK_THRESHOLD  8
#define NEAR_LOOK_THRESHOLD 3
#define HITBOX_WIDTH        9
#define HITBOX_HEIGHT       5
#define WEAPON_COUNT        6
#define SPREAD_SPACING      10  // The spacing (in degrees) between Spread bullets

// Enum to represent all possible player weapon types
enum player_weapon {
	W_MISSILE,
	W_LASER,
	W_SPREAD,
	W_BOMB,
	W_PLASMA,
	W_RAPID,
};

class Hero : public df::Object {

private:

	Reticle* p_reticle;				// Reticle displayed for aiming
	bool firing;					// Indicates if the player can fire their weapon
	int fireCooldown;				// The rate at which a weapon can fire
	bool shieldOverloaded;			// Indicates if the shield overload attack was used 
	int overloadCooldown;			// The rate at which to flash the screen for the shield overload event
	int shieldIntegrity;			// Value of the player's shields
	int lives;						// Value of the lives the player has (1)
	bool wasHit;					// Indicates if the player was hit by an enemy
	int hitCooldown;				// The rate at which to change the player sprite when hit
	player_weapon currentWeapon;	// The weapon current equiped 
	df::Vector projectileStart;		// The position a projectile will spawn from (based on sprite animation)
	std::map<player_weapon, std::string> weaponName;	// Maps the weapons to thier name
	std::map<player_weapon, int> weaponAmmo;			// Maps the weapons to their ammo counts
	std::map<player_weapon, int> weaponCooldown;		// Maps the weapons to their cooldown rates
	std::map<player_weapon, std::string> weaponSound;	// Maps the weapons to their audo sounds

	// Handle mouse events
	void mouse(const df::EventMouse* p_mouse_event);

	// Handle keyboard events
	void kbd(const df::EventKeyboard* p_keyboard_event);

	// Handles the shooting of all weapon types
	void fire(df::Vector target, df::Vector origin);

	// Handle step event
	void step();

	// Use Shield Overload ability
	void overloadShield();

	// Handle collision event
	void hit(const df::EventCollision* p_collision_event);

	// Change the player's currently-equipped weapon
	// Also adjusts the cooldown if active to prevent abusing it
	void changeWeapon(player_weapon new_weapon);

	// Update the player's sprite based on the reticle location
	void updateSprite();

	// Update the position the player's projectiles spawn from
	void setProjectileStart(int index);

public:

	// Constructor / Deconstructor
	Hero();
	~Hero();

	// Handles events (override)
	int eventHandler(const df::Event* p_e);

	// Handles drawing the hero (override)
	int draw();
};
