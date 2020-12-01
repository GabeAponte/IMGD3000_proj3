//
// Hero.cpp
//

// Engine includes.
#include "EventMouse.h"
#include "EventStep.h"
#include "EventView.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "../header_files/Bullet.h"
#include "../header_files/Explosion.h"
#include "../header_files/GameOver.h"
#include "../header_files/Hero.h"
#include "../header_files/EventOverloadShield.h"

using namespace df;

Hero::Hero() {

    // Link to "ship" sprite.
    setSprite("ship");

    // Set object type.
    setType("Hero");

    // Set starting location to center of screen.
    setPosition(Vector(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2));

    // Create reticle for firing bullets.
    p_reticle = new Reticle();
    p_reticle->draw();

    // Set attributes that control actions.
    fire_slowdown = 15;
    fire_countdown = fire_slowdown;
    lives = 1;
    shield_integrity = 100;
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

    switch (p_keyboard_event->getKey()) {
    case df::Keyboard::Q:        // quit
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            WM.markForDelete(this);
        break;

    case df::Keyboard::SPACE:   // space
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            overloadShield();
        break;
    default:
        break;
    };

    return;
}

// Fire bullet towards target.
void Hero::fire(df::Vector target) {

  // See if time to fire.
  if (fire_countdown > 0)
    return;
  fire_countdown = fire_slowdown;

  // Fire Bullet towards target.
  Bullet* bullet = new Bullet();

  // Set bullet velocity
  df::Vector v = target - getPosition();
  v.normalize();
  v.scale(1);
  bullet->setVelocity((v));

  // Set bullet starting position
  bullet->setPosition(getPojectileStart(target));

  // Play "fire" sound.
  df::Sound *p_sound = RM.getSound("fire");
  p_sound->play();
}

// Decrease rate restriction counters.
void Hero::step() {

  // Fire countdown.
  fire_countdown--;
  if (fire_countdown < 0)
    fire_countdown = 0;
}

// Send "overloadShield" event to all objects.
void Hero::overloadShield() {

  // Check if nukes left.
  if (shield_integrity == 0) 
    return;

  if (shield_integrity > 15) {
    shield_integrity -= 15;

    // Send "view" event do decrease shield interested ViewObjects.
    df::EventView ev("Shield Integrity %", -15, true);
    WM.onEvent(&ev);
  }
  else {
      shield_integrity = 0;
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

    if ((target.getX() < this->getPosition().getX() + 7) && (target.getX() > this->getPosition().getX() - 7)) {
        if (target.getY() > this->getPosition().getY()) {
            xStart = 0;
            yStart = 2;
        }
        else if (target.getY() < this->getPosition().getY()) {
            xStart = 0;
            yStart = -2;
        }
    }

    else if (target.getX() > this->getPosition().getX()) {
        xStart = 3;
        yStart = 0;
    }
    else if (target.getX() < this->getPosition().getX()) {
        xStart = -3;
        yStart = 0;
    }

    return df::Vector(this->getPosition().getX() + xStart, this->getPosition().getY() + yStart);
}

/*
* Hero was hit, so remove shield health
*/
void Hero::hit(const df::EventCollision* p_collision_event) {

    // Check for saucer collision and update the hero / game
    if (((p_collision_event->getObject1()->getType()) == "Saucer")
        || ((p_collision_event->getObject2()->getType()) == "Saucer")) {


        // Decrease the shield integrety by at most 10, only if it isn't already 0.
        if (shield_integrity < 10) {
            shield_integrity = 0;
            df::EventView ev("Shield Integrity %", 0, false);
            WM.onEvent(&ev);
        }
        else if (shield_integrity != 0) {
            shield_integrity -= 10;
            df::EventView ev("Shield Integrity %", -10, true);
            WM.onEvent(&ev);
        }

        // Colision did not kill the hero
        if (shield_integrity != 0 || (shield_integrity == 0 && lives == 1)) {

            // Delete only the saucer
            if (p_collision_event->getObject1()->getType() == "Saucer") {
                WM.markForDelete(p_collision_event->getObject1());
            }
            if (p_collision_event->getObject2()->getType() == "Saucer") {
                WM.markForDelete(p_collision_event->getObject2());
            }
        }

        // Check hero still alive
        if (shield_integrity == 0) {
            if(lives == 0) {
                 // Delete the hero and the saucer
                WM.markForDelete(p_collision_event->getObject1());
                WM.markForDelete(p_collision_event->getObject2());
            } 
            else {
                // Hero will die next hit
                lives = 0;
            }
        }
    }
}
