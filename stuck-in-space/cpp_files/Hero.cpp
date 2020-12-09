// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// Gabriel Aponte
// gaaponte@wpi.edu

//
// Handles the Hero functionality
//

#include <iostream>
#include <Utility.h>
#include <EventMouse.h>
#include <EventStep.h>
#include <GameManager.h>
#include <DisplayManager.h>
#include <ResourceManager.h>
#include <WorldManager.h>
#include "../header_files/Velocity.h"
#include "../header_files/Bullet.h"
#include "../header_files/Bomb.h"
#include "../header_files/Laser.h"
#include "../header_files/Explosion.h"
#include "../header_files/GameOver.h"
#include "../header_files/EventOverloadShield.h"
#include "../header_files/EventPlayerDeath.h"
#include "../header_files/EventAmmo.h"
#include "../header_files/Hero.h"
#include "../header_files/EventShake.h"

using namespace df;

Hero::Hero() {

	// Link to "player" sprite.
	setSprite("player");
	setAnimationState(false);

	// Set custom collision box
	applyHitbox();

	// Set object type.
	setType("Hero");

	// Set starting location to center of screen.
	setPosition(WM.getBoundary().getCorner() + Vector(WM.getBoundary().getHorizontal() / 2, (WM.getBoundary().getVertical() / 2) - 1));

	// Set altitude
	setAltitude(MAX_ALTITUDE-1);

	// Enable collision checking without velocity
	setAlwaysCollide(true);

	// Create reticle for firing bullets.
	p_reticle = new Reticle();

	// Load sprites
	hudStatus = RM.getSprite("hud-status");
	hudWeapons = RM.getSprite("hud-weapons");
	hudSelectAnim = Animation();
	hudSelectAnim.setSprite(RM.getSprite("hud-selection"));

	// Set attributes that control actions.
	currentWeapon = W_MISSILE;
	canFire = false;
	fireCooldown = 0;
	overloadCooldown = 0;
	showOverloadCooldown = 0;
	hitCooldown = 0;
	changeWeaponCooldown = 0;
	lives = LIVES;
	shieldIntegrity = SHIELD_INTEGRITY;
	projectileStart = getPosition();
	shieldOverloaded = false;
	wasHit = false;
	noAmmoCooldown = 0;
	warningBlink = false;
	warningBlinkTimer = WARNING_BLINK_TIMER;

	// Initialize weapon names
	weaponName[W_MISSILE] = "MISSILE";
	weaponName[W_LASER] = "LASER";
	weaponName[W_SPREAD] = "SPREAD";
	weaponName[W_BOMB] = "BOMB";
	weaponName[W_PLASMA] = "PLASMA";
	weaponName[W_RAPID] = "RAPID";

	// Initialize weapon ammo counts
	weaponAmmo[W_MISSILE] = 0; // should always be 0
	weaponAmmo[W_LASER] = 3;
	weaponAmmo[W_SPREAD] = 0;
	weaponAmmo[W_BOMB] = 00;
	weaponAmmo[W_PLASMA] = 0;
	weaponAmmo[W_RAPID] = 0;

	// Initialize weapon ammo pickup timers
	weaponAmmoPickup[W_MISSILE] = 0;
	weaponAmmoPickup[W_LASER] = 0;
	weaponAmmoPickup[W_SPREAD] = 0;
	weaponAmmoPickup[W_BOMB] = 0;
	weaponAmmoPickup[W_PLASMA] = 0;
	weaponAmmoPickup[W_RAPID] = 0;

	// Initialize weapon cooldowns
	weaponCooldown[W_MISSILE] = 15;
	weaponCooldown[W_LASER] = 20;
	weaponCooldown[W_SPREAD] = 20;
	weaponCooldown[W_BOMB] = 20;
	weaponCooldown[W_PLASMA] = 35;
	weaponCooldown[W_RAPID] = 4;

	// Initialize weapon sounds
	weaponSound[W_MISSILE] = "missile";
	weaponSound[W_LASER] = "laser";
	weaponSound[W_SPREAD] = "spread";
	weaponSound[W_BOMB] = "bomb";
	weaponSound[W_PLASMA] = "plasma";
	weaponSound[W_RAPID] = "rapid";
}

Hero::~Hero() {

	// Make sure background is black
	DM.setBackgroundColor(BLACK);

	// Create GameOver object.
	new GameOver;

	// Make big explosion.
	for (int i = -2; i <= 2; i++) {
		for (int j = -2; j <= 2; j++) {
			if (abs(i) != 2 || abs(j) != 2)
			{
				df::Vector temp_pos = this->getPosition();
				temp_pos.setX(this->getPosition().getX() + i * 7);
				temp_pos.setY(this->getPosition().getY() + j * 3);
				Explosion* p_explosion = new Explosion;
				p_explosion->setPosition(temp_pos);
			}
		}
	}

	// Declare that the player died
	EventPlayerDeath epd = EventPlayerDeath();
	WM.onEvent(&epd);
}

// Handle event.
// Return 0 if ignored, else 1.
int Hero::eventHandler(const df::Event* p_e) 
{
	// Keyboard event handler
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event = dynamic_cast <const df::EventKeyboard*> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}

	// Mouse event handler
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
		mouse(p_mouse_event);
		return 1;
	}

	// Step event handler
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	// Collision event handler
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	// Ammo event handler
	if (p_e->getType() == AMMO_EVENT) {
		const EventAmmo* p_ammo_event = dynamic_cast <EventAmmo const*> (p_e);
		weaponAmmo[p_ammo_event->getAmmoType()] += p_ammo_event->getAmmoValue();
		weaponAmmoPickup[p_ammo_event->getAmmoType()] = AMMO_PICKUP_TIMER;
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// Take appropriate action according to mouse action.
void Hero::mouse(const df::EventMouse* p_mouse_event) 
{
	// Pressed button?
	if (p_mouse_event->getMouseButton() == df::Mouse::LEFT)
	{
		if (p_mouse_event->getMouseAction() == df::CLICKED)
		{
			canFire = true;
		}
		else if (p_mouse_event->getMouseAction() == df::RELEASED)
		{
			canFire = false;
		}
	}

	// Scrolled?
	if (p_mouse_event->getMouseAction() == df::SCROLLED)
	{
		// Skip if on cooldown
		if (changeWeaponCooldown > 0)
		{
			return;
		}

		float scroll = p_mouse_event->getMouseScroll();
		if (scroll > 0)
		{
			previousWeapon();
			changeWeaponCooldown = SCROLL_COOLDOWN;
		}
		else if (scroll < 0)
		{
			nextWeapon();
			changeWeaponCooldown = SCROLL_COOLDOWN;
		}
	}
}

// Take appropriate action according to key pressed.
void Hero::kbd(const df::EventKeyboard* p_keyboard_event) 
{
	// handle key press events
	if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {

		switch (p_keyboard_event->getKey()) {

		// Escape : Quit
		case df::Keyboard::ESCAPE:
			GM.setGameOver();
			break;

		// Space : Overload Shield
		case df::Keyboard::SPACE:
			overloadShield();
			break;

		// 1-6 : Switch Weapon
		case df::Keyboard::NUM1:
			changeWeapon(W_MISSILE);
			break;
		case df::Keyboard::NUM2:
			changeWeapon(W_LASER);
			break;
		case df::Keyboard::NUM3:
			changeWeapon(W_SPREAD);
			break;
		case df::Keyboard::NUM4:
			changeWeapon(W_BOMB);
			break;
		case df::Keyboard::NUM5:
			changeWeapon(W_PLASMA);
			break;
		case df::Keyboard::NUM6:
			changeWeapon(W_RAPID);
			break;

		// A : Previous Weapon (also supports Left Arrow)
		case df::Keyboard::A:
		case df::Keyboard::LEFTARROW:
			previousWeapon();
			break;

		// D : Next Weapon (also supports Right Arrow)
		case df::Keyboard::D:
		case df::Keyboard::RIGHTARROW:
			nextWeapon();
			break;
		default:
			break;
		}
	}
	return;
}

// Fire bullet towards target.
void Hero::fire(df::Vector target, df::Vector origin) 
{
	// Update ammo (and skip firing if empty)
	if (currentWeapon != W_MISSILE) {

		if (weaponAmmo[currentWeapon] <= 0) {

			// Play warning sound to indicate out of ammo
			if (noAmmoCooldown <= 0) {

				df::Sound* p_sound = RM.getSound("out-of-ammo");
				p_sound->play();

				noAmmoCooldown = 15;
			}
			return;
		} 
		else {
			weaponAmmo[currentWeapon] -= 1;
		}
	}

	// Update cooldown
	fireCooldown = weaponCooldown[currentWeapon];

	// Play appropriate fire sound for the current weapon
	// Only play bomb sound if not detonating an active bomb
	if (currentWeapon != W_BOMB) {
		df::Sound* p_sound = RM.getSound(weaponSound[currentWeapon]);
		p_sound->play();
	} 
	else if (!Bomb::isActive()) {
		df::Sound* p_sound = RM.getSound(weaponSound[currentWeapon]);
		p_sound->play();
	}

	// Calculate bullet velocity
	df::Vector aim = target - origin;      // calculate aim vector
	df::Vector v = makeRealVector(aim, 2); // convert to game vector

	// Create and position weapon attack
	switch (currentWeapon) {

	case W_MISSILE:
	{
		// Fire Missile towards target
		Bullet* p_bullet = new Bullet();
		p_bullet->setSprite("w_bullet");
		p_bullet->setVelocity(v);
		p_bullet->setPosition(origin);
		return;
	}
	case W_LASER:
	{
		// Fire Laser towards target
		Laser* p_laser = new Laser(origin);
		df::Vector laser_vel = v;
		laser_vel.scale(2);
		p_laser->setVelocity(laser_vel);
		return;
	}
	case W_SPREAD:
	{
		// Fire Spread of 4 bullets towards target
		df::Vector pixel_aim = DM.spacesToPixels(aim);
		for (int i = 0; i < 4; i++)
		{
			Bullet* p_spread = new Bullet(W_SPREAD);
			p_spread->setSprite("w_spread");
			df::Vector spread_vel = rotateVector(pixel_aim, SPREAD_SPACING * (i - 1.5));
			spread_vel.normalize();
			spread_vel.scale(2);
			p_spread->setVelocity(convertToReal(spread_vel));
			p_spread->setPosition(origin);
		}
		return;
	}
	case W_BOMB:
	{
		// Refund ammo if only detonating existing bomb
		if (Bomb::isActive())
		{
			weaponAmmo[W_BOMB]++;
		}

		// Fire Bomb towards target, exploding on impact
		Bomb* p_bomb = new Bomb();
		df::Vector bomb_vel = v;
		bomb_vel.scale(.5);
		p_bomb->setVelocity(bomb_vel);
		p_bomb->setPosition(origin);
		return;
	}
	case W_PLASMA:
	{
		// Fire a slow orb of Plasma towards target, dealing damage over time
		Bullet* p_plasma = new Bullet(W_PLASMA);
		p_plasma->setSprite("w_plasma");
		df::Vector plasma_vel = v;
		plasma_vel.scale(0.3);
		p_plasma->setVelocity(plasma_vel);
		p_plasma->setPosition(origin);
		return;
	}
	case W_RAPID:
	{
		// Rapid-fire light bullets towards target
		Bullet* p_rapid = new Bullet(W_RAPID);
		p_rapid->setSprite("w_rapid");
		p_rapid->setVelocity(v);
		p_rapid->setPosition(origin);
		return;
	}
	default:
		return;
	}
}

// Decrease rate restriction counters.
void Hero::step()
{
	// Update mouse scroll cooldown
	if (changeWeaponCooldown > 0) {
		changeWeaponCooldown--;
	}

	// Update ammo display timers
	for (std::map<player_weapon, int>::iterator it = weaponAmmoPickup.begin(); it != weaponAmmoPickup.end(); it++)
	{
		if (it->second > 0)
		{
			it->second--;
		}
	}

	// Update shield warning timer
	if (shieldIntegrity <= 0)
	{
		warningBlinkTimer--;
		if (warningBlinkTimer <= 0)
		{
			warningBlink = !warningBlink;
			warningBlinkTimer = WARNING_BLINK_TIMER;
		}
	}

	// If hero was hit, set the sprite color
	if (wasHit) {
		setSprite("player-hit");
		hitCooldown--;
	}

	if (hitCooldown == 0) {
		if (shieldIntegrity > 0) {
			setSprite("player");
		}
		else {
			setSprite("player-no-shield");
		}
		hitCooldown = HIT_COOLDOWN;
		wasHit = false;
	}

	// Reset the custom collision box
	applyHitbox();

	// Flash the screen if the shield was overloaded
	if (shieldOverloaded)
	{
		if (overloadCooldown > 0) {
			overloadCooldown--;
		}
		if (overloadCooldown == 0) {
			DM.setBackgroundColor(df::BLACK);
			shieldOverloaded = false;
		}
	}
	if (showOverloadCooldown > 0) {
		showOverloadCooldown--;
	}

	// Fire weapon
	if (fireCooldown > 0) {
		fireCooldown--;
	}

	if (canFire) {

		// Fire bullet as normal
		if (fireCooldown <= 0)
		{
			fire(p_reticle->getPosition(), projectileStart);
		}

		// Check if bomb needs to be exploded
		else if (currentWeapon == W_BOMB && fireCooldown < weaponCooldown[W_BOMB] - BOMB_DETONATE_WAIT)
		{
			Bomb::detonate();
		}
	}

	// Control no ammo sound cooldown rate every step
	if (noAmmoCooldown > 0) {
		noAmmoCooldown--;
	}

	// Update sprite
	updateSprite();
}

// Send "overloadShield" event to all objects.
void Hero::overloadShield() {

	// Check can overload
	if (overloadCooldown > 0) {
		return;
	}

	// Check if shields left.
	if (shieldIntegrity <= 0)
	{
		// Alert player that they are out of shields
		df::Sound* p_sound = RM.getSound("shield-error");
		p_sound->play();
		return;
	}

	// Mark shield overloaded and flash the screen
	shieldOverloaded = true;
	overloadCooldown = OVERLOAD_COOLDOWN;
	showOverloadCooldown = SHOW_OVERLOAD_COOLDOWN;
	DM.setBackgroundColor(df::TEAL);

	// If shields are greater than 15, reduce by 15 
	if (shieldIntegrity > 15)
	{
		shieldIntegrity -= 15;
	}
	// Shield is less than 15 so set to zero and set lives to zero
	else {
		shieldIntegrity = 0;
		lives = 0;
		setSprite("player-no-shield");
		applyHitbox();
	}

	// Create "overload" event and send to interested Objects.
	EventOverloadShield overload;
	WM.onEvent(&overload);

	// Play shield overload sound
	df::Sound* p_sound = df::RM.getSound("shield-overload");
	p_sound->play();
}

// Change the player's currently-equipped weapon
void Hero::changeWeapon(player_weapon new_weapon)
{

	// Play switch weapon sound
	df::Sound* p_sound = RM.getSound("switch-weapon");
	p_sound->play();

	currentWeapon = new_weapon;
}

// Switch to the previous weapon
void Hero::previousWeapon()
{
	changeWeapon((player_weapon)((((int)currentWeapon) + WEAPON_COUNT - 1) % WEAPON_COUNT));
}

// Switch to the next weapon
void Hero::nextWeapon()
{
	changeWeapon((player_weapon)((((int)currentWeapon) + 1) % WEAPON_COUNT));
}

// Update the player's sprite based on the reticle location
void Hero::updateSprite()
{
	float xPos = getPosition().getX();
	float xReticle = p_reticle->getPosition().getX();
	int new_index = 2;

	if (xReticle < xPos - FAR_LOOK_THRESHOLD)
	{
		new_index = 0;
	}
	else if (xReticle < xPos - NEAR_LOOK_THRESHOLD)
	{
		new_index = 1;
	}
	else if (xReticle > xPos + FAR_LOOK_THRESHOLD)
	{
		new_index = 4;
	}
	else if (xReticle > xPos + NEAR_LOOK_THRESHOLD)
	{
		new_index = 3;
	}

	this->setAnimationIndex(new_index);
}

// Function for when a hero was hit, so remove shield and/or health
void Hero::hit(const df::EventCollision* p_collision_event) {

	// Check for enemy collision and update the hero / game
	if ((p_collision_event->getObject1()->getType() == "Enemy")
		|| (p_collision_event->getObject2()->getType() == "Enemy")
		|| (p_collision_event->getObject1()->getType() == "EnemyBullet")
		|| (p_collision_event->getObject2()->getType() == "EnemyBullet")) {

		// Shake screen
		EventShake es = EventShake();
		WM.onEvent(&es);

		// Set wasHit so that sprite color changes
		wasHit = true;

		// Decrease the shield integrety by at most 10, only if it isn't already 0.
		if (shieldIntegrity > 10) {
			shieldIntegrity -= 10;
		}
		else {
			shieldIntegrity = 0;
		}

		// Colision did not kill the hero
		if (shieldIntegrity != 0 || (shieldIntegrity == 0 && lives == 1)) {

			// Play shield hit sound
			df::Sound* p_sound = df::RM.getSound("shield-hit");
			p_sound->play();

			// Delete only the enemy
			if (p_collision_event->getObject1()->getType() == "Enemy") {
				WM.markForDelete(p_collision_event->getObject1());
			}
			if (p_collision_event->getObject2()->getType() == "Enemy") {
				WM.markForDelete(p_collision_event->getObject2());
			}
		}

		// Check hero still alive
		if (shieldIntegrity <= 0) {
			setSprite("player-no-shield");
			applyHitbox();
			if (lives <= 0)
			{
				// Delete the hero and the enemy
				WM.markForDelete(p_collision_event->getObject1());
				WM.markForDelete(p_collision_event->getObject2());

				// Mark Reticle for deletion.
				WM.deleteObjectsOfType("Reticle");
			}
			else
			{
				// Hero will die next hit
				lives = 0;
			}
		}
	}
}

// Set to a custom hitbox
void Hero::applyHitbox()
{
	setBox(Box(Vector(-HITBOX_WIDTH / 2, (-HITBOX_HEIGHT / 2)-0.25), HITBOX_WIDTH, HITBOX_HEIGHT));
}

// Draw the player and their ammo counts
int Hero::draw()
{
	float mid_x = WM.getView().getCorner().getX() + WM.getView().getHorizontal() / 2;
	float top_y = WM.getView().getCorner().getY();
	float bottom_y = top_y + WM.getView().getVertical();

	// Draw player
	Object::draw();
	
	// Draw HUD
	hudStatus->draw(0, Vector(mid_x, top_y+2));
	hudWeapons->draw(0, Vector(mid_x, bottom_y-3));

	// Draw shield integrity
	Color shield_color = df::CYAN;
	float shield_x_offset = 0;
	std::string shield_string = "SHIELD INTEGRITY: " + std::to_string(shieldIntegrity) + "%";
	if (showOverloadCooldown > 0)
	{
		shield_string = "!!! SHIELD OVERLOADED !!!";
		shield_color = df::YELLOW;
	}
	else if (shieldIntegrity <= 0)
	{
		if (warningBlink)
		{
			shield_color = df::CORAL;
		}
		else
		{
			shield_color = df::RED;
		}
	}
	DM.drawString(Vector(mid_x, top_y + 0.5), shield_string, CENTER_JUSTIFIED, shield_color);

	// Draw ammo readout
	int width = 10;
	
	for (int i = 0; i < WEAPON_COUNT; i++)
	{
		player_weapon weapon = static_cast<player_weapon>(i);
		float x_pos = (float)(mid_x - (WEAPON_COUNT - 1) * width / 2 + i * width -0.5);
		Color color = df::WHITE;

		// Draw selection indicator na duse selection color
		if (currentWeapon == weapon)
		{
			hudSelectAnim.draw(Vector(x_pos+0.5, bottom_y - 3.5));
			color = df::YELLOW;
		}
		if (weaponAmmoPickup[weapon] > 0)
		{
			color = df::ORANGE;
		}

		// Draw weapon name
		float x_offset = 0;
		std::string str = weaponName[weapon];
		if (str.length() % 2 == 0)
		{
			// Even strings need offset
			x_offset = 0.5;
		}
		DM.drawString(Vector(x_pos+x_offset, bottom_y - 2.5), str, CENTER_JUSTIFIED, color);

		// Draw weapon ammo
		std::string ammo_string = "---";
		if (weapon != W_MISSILE)
		{
			ammo_string = std::to_string(weaponAmmo[weapon]);
			
			// Make ammo count red if there is no ammo
			if (weaponAmmo[weapon] <= 0) {
				color = RED;
			}
		}
		if (ammo_string.length() % 2 == 0)
		{
			// Even strings need offset
			x_offset = 0.5;
		}
		else
		{
			x_offset = 0;
		}
		DM.drawString(Vector(x_pos+x_offset, bottom_y - 1.5), ammo_string, CENTER_JUSTIFIED, color);
	}

	return 0;
}