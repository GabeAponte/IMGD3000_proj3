//
// Hero.cpp
//

// Engine includes.
#include <Utility.h>
#include <EventMouse.h>
#include <EventStep.h>
#include <EventView.h>
#include <GameManager.h>
#include <DisplayManager.h>
#include <ResourceManager.h>
#include <WorldManager.h>

#include <iostream>

// Game includes.
#include "../header_files/Bullet.h"
#include "../header_files/Explosion.h"
#include "../header_files/GameOver.h"
#include "../header_files/EventOverloadShield.h"
#include "../header_files/EventPlayerDeath.h"
#include "../header_files/EventAmmo.h"
#include "../header_files/Hero.h"

using namespace df;

Hero::Hero() {

    // Link to "ship" sprite.
    setSprite("player");
    setBox(Box(Vector(-HITBOX_WIDTH/2,-HITBOX_HEIGHT/2), HITBOX_WIDTH, HITBOX_HEIGHT)); // custom collision box
    setAnimationState(false);

    // Set object type.
    setType("Hero");

    // Set starting location to center of screen.
    setPosition(Vector(WM.getBoundary().getHorizontal()/2, WM.getBoundary().getVertical()/2));
    
    // Set to middle altitude
    setAltitude(3);

    // Create reticle for firing bullets.
    p_reticle = new Reticle();
    p_reticle->draw();

    // Set attributes that control actions.
    currentWeapon = W_MISSILE;
    fireCooldown = 0;
    lives = 1;
    shieldIntegrity = 100;

    // Initialize weapon names
    weaponName[W_MISSILE] =     "MISSILE";
    weaponName[W_LASER] =       "LASER";
    weaponName[W_SPREAD] =      "SPREAD";
    weaponName[W_BOMB] =        "BOMB";
    weaponName[W_PLASMA] =      "PLASMA";
    weaponName[W_RAPID] =       "RAPID";
    // Initialize weapon ammo counts
    weaponAmmo[W_MISSILE] =     0;
    weaponAmmo[W_LASER] =       0;
    weaponAmmo[W_SPREAD] =      0;
    weaponAmmo[W_BOMB] =        0;
    weaponAmmo[W_PLASMA] =      0;
    weaponAmmo[W_RAPID] =       0;
    // Initialize weapon cooldowns
    weaponCooldown[W_MISSILE] = 15;
    weaponCooldown[W_LASER] =   15;
    weaponCooldown[W_SPREAD] =  20;
    weaponCooldown[W_BOMB] =    20;
    weaponCooldown[W_PLASMA] =  30;
    weaponCooldown[W_RAPID] =   5;
    // Initialize weapon sounds
    weaponSound[W_MISSILE] =    "fire";
    weaponSound[W_LASER] =      "fire";
    weaponSound[W_SPREAD] =     "fire";
    weaponSound[W_BOMB] =       "fire";
    weaponSound[W_PLASMA] =     "fire";
    weaponSound[W_RAPID] =      "fire";
    // TODO: maybe condense these into a map to a struct?
}

Hero::~Hero() {

    // Mark Reticle for deletion.
    WM.markForDelete(p_reticle);

    // Create GameOver object.
    new GameOver;

    // Make big explosion.
    for (int i = -8; i <= 8; i += 5) {
        for (int j = -5; j <= 5; j += 3) {
            df::Vector temp_pos = this->getPosition();
            temp_pos.setX(this->getPosition().getX() + i);
            temp_pos.setY(this->getPosition().getY() + j);
            Explosion* p_explosion = new Explosion;
            p_explosion->setPosition(temp_pos);
        }
    }

    // Declare that the player died
    EventPlayerDeath epd = EventPlayerDeath();
    WM.onEvent(&epd);
}

// Handle event.
// Return 0 if ignored, else 1.
int Hero::eventHandler(const df::Event* p_e) {

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
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

// Take appropriate action according to mouse action.
void Hero::mouse(const df::EventMouse* p_mouse_event) {

    // Pressed button?
    if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
        (p_mouse_event->getMouseButton() == df::Mouse::LEFT))
        fire(p_mouse_event->getMousePosition());
}

// Take appropriate action according to key pressed.
void Hero::kbd(const df::EventKeyboard* p_keyboard_event) {

    // handle key press events
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
    {
        switch (p_keyboard_event->getKey()) {
        // Q : Quit
        case df::Keyboard::Q:
            GM.setGameOver();
            break;
        // Space : Overload Shield
        case df::Keyboard::SPACE:
            overloadShield();
            break;
        // 1-6 : Switch Weapon
        case df::Keyboard::NUM1:
            currentWeapon = W_MISSILE;
            break;
        case df::Keyboard::NUM2:
            currentWeapon = W_LASER;
            break;
        case df::Keyboard::NUM3:
            currentWeapon = W_SPREAD;
            break;
        case df::Keyboard::NUM4:
            currentWeapon = W_BOMB;
            break;
        case df::Keyboard::NUM5:
            currentWeapon = W_PLASMA;
            break;
        case df::Keyboard::NUM6:
            currentWeapon = W_RAPID;
            break;
        default:
            break;
        };
    }
    return;
}

// Fire bullet towards target.
void Hero::fire(df::Vector target) {

    // See if ready to fire
    if (fireCooldown > 0)
        return;

    // Update ammo (and skip firing if empty)
    if (currentWeapon != W_MISSILE)
    {
        if (weaponAmmo[currentWeapon] <= 0)
        {
            // Play warning sound to indicate out of ammo
            /*
            df::Sound* p_sound = RM.getSound("no_ammo");
            p_sound->play();
            */
            return;
        }
        else
        {
            weaponAmmo[currentWeapon] -= 1;
        }
    }

    // Update cooldown
    fireCooldown = weaponCooldown[currentWeapon];

    // Play appropriate fire sound for the current weapon
    df::Sound* p_sound = RM.getSound(weaponSound[currentWeapon]);
    p_sound->play();

    // Calculate bullet velocity
    df::Vector v = target - getPosition();
    v.normalize();
    v.scale(1);

    // Create and position weapon attack
    switch (currentWeapon)
    {
    case W_MISSILE:
    {
        // Fire Missile towards target
        Bullet* bullet = new Bullet();
        bullet->setVelocity((v));
        bullet->setPosition(getPojectileStart(target));
        return;
    }
    case W_LASER:
    {
        // Fire Laser towards target
        /*
        Laser* laser = new Bullet();
        laser->setVelocity((v));
        laser->setPosition(getPojectileStart(target));
        */
        return;
    }
    case W_SPREAD:
    {
        // Fire Spread of 4 bullets towards target
        // PROCEDURE:
        // 1. get angle from player to target
        // 2. calculate offsets from angle based on i
        // 3. generate Spread bullet objects and send them in the appropriate directions
        for (float i = 0; i < 4; i++)
        {
            /*
            float angle = target_angle - offset + i*offset_step;
            Spread* spread = new Spread();
            laser->setVelocity((v));
            laser->setPosition(getPojectileStart(target));
            */
        }
        return;
    }
    case W_BOMB:
    {
        // Fire Bomb towards target, exploding on impact
        /*
        Bomb* bomb = new Bomb();
        bomb->setVelocity((v));
        bomb->setPosition(getPojectileStart(target));
        */
        return;
    }
    case W_PLASMA:
    {
        // Fire a slow orb of Plasma towards target, dealing damage over time
        /*
        Plasma* plasma = new Plasma();
        plasma->setVelocity((v));
        plasma->setPosition(getPojectileStart(target));
        */
        return;
    }
    case W_RAPID:
    {
        // Rapid-fire light bullets towards target with a short
        /*
        Rapid* rapid = new Rapid();
        rapid->setVelocity((v));
        rapid->setPosition(getPojectileStart(target));
        */
        return;
    }
    default:
        return;
    }
}

// Decrease rate restriction counters.
void Hero::step() {

  // Fire countdown.
  fireCooldown--;
  if (fireCooldown < 0)
    fireCooldown = 0;

  // Update sprite
  updateSprite();
}

// Send "overloadShield" event to all objects.
void Hero::overloadShield() {

  // Check if shields left.
  if (shieldIntegrity == 0) 
    return;

  if (shieldIntegrity > 15) {
    shieldIntegrity -= 15;

    // Send "view" event do decrease shield interested ViewObjects.
    df::EventView ev("Shield Integrity %", -15, true);
    WM.onEvent(&ev);
  }
  else {
      shieldIntegrity = 0;
      lives = 0;
      // Send "view" event do decrease shield interested ViewObjects.
      df::EventView ev("Shield Integrity %", 0, false);
      WM.onEvent(&ev);
  }
  
  // Create "overload" event and send to interested Objects.
  EventOverloadShield overload;
  WM.onEvent(&overload);

  // Play "overload" sound.
  df::Sound *p_sound = RM.getSound("nuke");
  p_sound->play();
}

// Get the vector position for where a weapon projectile should start from
df::Vector Hero::getPojectileStart(df::Vector target)
{
    int xStart = 0;
    int yStart = 0;
    Box thisBox = getWorldBox(this);
    if ((target.getX() > thisBox.getCorner().getX()) && (target.getX() < thisBox.getCorner().getX()+thisBox.getHorizontal())) {
        if (target.getY() > this->getPosition().getY()) {
            xStart = 0;
            yStart = 1 + HITBOX_HEIGHT/2;
        }
        else if (target.getY() < this->getPosition().getY()) {
            xStart = 0;
            yStart = -1 - HITBOX_HEIGHT/2;
        }
    }

    else if (target.getX() > this->getPosition().getX()) {
        xStart = 2 + HITBOX_WIDTH/2;
        yStart = 0;
    }
    else if (target.getX() < this->getPosition().getX()) {
        xStart = -2 - HITBOX_WIDTH/2;
        yStart = 0;
    }

    return df::Vector(this->getPosition().getX() + xStart, this->getPosition().getY() + yStart);
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


/*
* Hero was hit, so remove shield health
*/
void Hero::hit(const df::EventCollision* p_collision_event) {

    // Check for saucer collision and update the hero / game
    if (((p_collision_event->getObject1()->getType()) == "Saucer")
        || ((p_collision_event->getObject2()->getType()) == "Saucer")) {


        // Decrease the shield integrety by at most 10, only if it isn't already 0.
        if (shieldIntegrity < 10) {
            shieldIntegrity = 0;
            df::EventView ev("Shield Integrity %", 0, false);
            WM.onEvent(&ev);
        }
        else if (shieldIntegrity != 0) {
            shieldIntegrity -= 10;
            df::EventView ev("Shield Integrity %", -10, true);
            WM.onEvent(&ev);
        }

        // Colision did not kill the hero
        if (shieldIntegrity != 0 || (shieldIntegrity == 0 && lives == 1)) {

            // Delete only the saucer
            if (p_collision_event->getObject1()->getType() == "Saucer") {
                WM.markForDelete(p_collision_event->getObject1());
            }
            if (p_collision_event->getObject2()->getType() == "Saucer") {
                WM.markForDelete(p_collision_event->getObject2());
            }
        }

        // Check hero still alive
        if (shieldIntegrity <= 0) {
            if (lives <= 0) 
            {
                 // Delete the hero and the saucer
                WM.markForDelete(p_collision_event->getObject1());
                WM.markForDelete(p_collision_event->getObject2());
            } 
            else 
            {
                // Hero will die next hit
                lives = 0;
            }
        }
    }
}


// Draw the player and their ammo counts
int Hero::draw()
{
    // Draw player
    Object::draw();

    // Draw ammo
    // TODO: Polish this up visually
    int width = 8;
    for (int i = 0; i < WEAPON_COUNT; i++)
    {
        player_weapon weapon = static_cast<player_weapon>(i);
        float x_pos = (float) (DM.getHorizontal() / 2 - (WEAPON_COUNT-1) * width / 2 + i*width);

        // draw selection indicator
        if (currentWeapon == weapon)
        {
            DM.drawCh(Vector(x_pos,0), 'V', YELLOW);
        }
        // draw weapon name
        DM.drawString(Vector(x_pos, 1), weaponName[weapon], CENTER_JUSTIFIED, YELLOW);
        // draw weapon ammo
        std::string ammo_string = "---";
        if (weapon != W_MISSILE)
        {
            ammo_string = std::to_string(weaponAmmo[weapon]);
        }
        DM.drawString(Vector(x_pos, 2), ammo_string, CENTER_JUSTIFIED, YELLOW);
    }

    return 0;
}