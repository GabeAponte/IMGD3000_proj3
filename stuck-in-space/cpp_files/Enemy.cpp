// Gabriel Aponte
// gaaponte@wpi.edu

//
// InputPlayerName.h
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

using namespace df;

Enemy::Enemy(df::Vector start_pos) {

  // Setup "saucer" sprite.
  setSprite("saucer");

  // Set object type.
  setType("Saucer");

  // Set speed
  setRealSpeed(.20);
  setPosition(start_pos);
  targetHero(start_pos);
  setSolidness(SOFT);
  
  killedByPlayer = false;
}

Enemy::~Enemy() {
  // Declare that the enemy died
  EventEnemyDeath eed(getPosition(), killedByPlayer);
  WM.onEvent(&eed);
}

// Handle event.
// Return 0 if ignored, else 1.
int Enemy::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::COLLISION_EVENT) {
    const df::EventCollision *p_collision_event = dynamic_cast <df::EventCollision const *> (p_e);
    hit(p_collision_event);
    return 1;
  }

  if (p_e->getType() == OVERLOAD_EVENT) {
 
    // Create explosion.
    Explosion *p_explosion = new Explosion;
    p_explosion -> setPosition(this -> getPosition());

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
  // Freeze in place
  if (p_e->getType() == PLAYER_DEATH_EVENT) {
      setVelocity(Vector());
      return 1;
  }
 
  // If get here, have ignored this event.
  return 0;
}

// Called with Enemy collides.
void Enemy::hit(const df::EventCollision *p_collision_event) {
  // If Bullet, create explosion and mark as killed by player
  if ((p_collision_event -> getObject1() -> getType() == "Bullet") ||
      (p_collision_event -> getObject2() -> getType() == "Bullet")) {

    // Create an explosion.
    Explosion *p_explosion = new Explosion;
    p_explosion -> setPosition(this -> getPosition());

    // Play "explode" sound
    df::Sound *p_sound = RM.getSound("explode");
    p_sound->play();

    killedByPlayer = true;
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


// Set/get the enemy's real speed (df speed is unreliable)
void Enemy::setRealSpeed(float new_speed)
{
    realSpeed = new_speed;
}
float Enemy::getRealSpeed() const
{
    return realSpeed;
}