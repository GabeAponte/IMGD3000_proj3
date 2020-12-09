// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// Gabriel Aponte
// gaaponte@wpi.edu

//
// Handles the Hero functionality
//

#pragma once

#include <map>
#include <Sprite.h>
#include <Animation.h>
#include <EventKeyboard.h>
#include <EventMouse.h>
#include <EventCollision.h>
#include <Object.h>
#include "..\header_files\Reticle.h"

#define LIVES				1
#define SHIELD_INTEGRITY	100
#define FAR_LOOK_THRESHOLD  8
#define NEAR_LOOK_THRESHOLD 3
#define HITBOX_WIDTH        10
#define HITBOX_HEIGHT       4
#define WEAPON_COUNT        6
#define SPREAD_SPACING      10  // The spacing (in degrees) between Spread bullets
#define SCROLL_COOLDOWN     3   // The number of steps to wait between detecting mouse scroll events
#define OVERLOAD_COOLDOWN   12   // The number of steps to wait between using Shield Overload ability
#define SHOW_OVERLOAD_COOLDOWN   25   // The number of steps to display that you used the Shield Overload ability
#define HIT_COOLDOWN		3   // The number of steps to wait before being able to take damage again after a hit
#define AMMO_PICKUP_TIMER	50  // The number of steps to display that an ammo type just got acquired
#define WARNING_BLINK_TIMER 30	// The number of steps to wait before toggling the color of a warning
#define BOMB_DETONATE_WAIT  10  // The delay between launching a bomb and being able to detonate it

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
	bool canFire;					// Indicates if the player can fire their weapon
	int fireCooldown;				// The rate at which a weapon can fire
	bool shieldOverloaded;			// Indicates if the shield overload attack was used
	int overloadCooldown;			// The rate at which to flash the screen for the shield overload event
	int showOverloadCooldown;		// How long to display that the player has overloaded shields
	int shieldIntegrity;			// Value of the player's shields
	int lives;						// Value of the lives the player has (1)
	bool wasHit;					// Indicates if the player was hit by an enemy
	int hitCooldown;				// The rate at which to change the player sprite when hit
	int noAmmoCooldown;             // The rate at which to play out of ammo sound
	player_weapon currentWeapon;	// The weapon current equiped 
	int changeWeaponCooldown;		// Cooldown between mouse scroll events
	bool warningBlink;				// Toggles the player's armor indicator when low
	int warningBlinkTimer;			// Cooldown between warningBlink toggling
	df::Vector projectileStart;		// The position a projectile will spawn from (based on sprite animation)
	std::map<player_weapon, std::string> weaponName;	// Maps the weapons to thier name
	std::map<player_weapon, int> weaponAmmo;			// Maps the weapons to their ammo counts
	std::map<player_weapon, int> weaponAmmoPickup;		// Maps the weapons to the timers for showing which ones got collected
	std::map<player_weapon, int> weaponCooldown;		// Maps the weapons to their cooldown rates
	std::map<player_weapon, std::string> weaponSound;	// Maps the weapons to their audo sounds
	df::Sprite* hudStatus;			// Sprite for status HUD
	df::Sprite* hudWeapons;			// Sprite for weapon HUD
	df::Animation hudSelectAnim;	// Animates HUD select sprite

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
	void changeWeapon(player_weapon new_weapon);

	// Switch to the next weapon
	void nextWeapon();

	// Switch to the previous weapon
	void previousWeapon();

	// Update the player's sprite based on the reticle location
	void updateSprite();

	// Set to a custom hitbox
	void applyHitbox();

public:

	// Constructor / Deconstructor
	Hero();
	~Hero();

	// Handles events (override)
	int eventHandler(const df::Event* p_e);

	// Handles drawing the hero (override)
	int draw();
};
