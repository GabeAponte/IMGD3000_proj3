//
// Enemy.cpp
//
 
// System includes.
#include <stdlib.h>		// for rand()

// Engine includes.
#include "EventCollision.h"
#include "EventOut.h"
#include "EventView.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
 
// Game includes.
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
  setSpeed(.20);
  setPosition(start_pos);
  targetHero(start_pos);
  setSolidness(SOFT);
}

Enemy::~Enemy() {
  // Declare that the enemy died
  EventEnemyDeath eed(getPosition());
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

  // If Enemy on Enemy, ignore.
  if ((p_collision_event -> getObject1() -> getType() == "Saucer") &&
      (p_collision_event -> getObject2() -> getType() == "Saucer"))
    return;

  // If Bullet, create explosion and make new Enemy.
  if ((p_collision_event -> getObject1() -> getType() == "Bullet") ||
      (p_collision_event -> getObject2() -> getType() == "Bullet")) {

    // Create an explosion.
    Explosion *p_explosion = new Explosion;
    p_explosion -> setPosition(this -> getPosition());

    // Play "explode" sound
    df::Sound *p_sound = RM.getSound("explode");
    p_sound->play();
  }
}

// Set the direction of the enemy to point at the player (center of screen)
void Enemy::targetHero(df::Vector position)
{
    df::Vector dir = (Vector(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2) - position);
    dir.normalize();
    setDirection(dir);
}

// Generate random starting point for enemy 
df::Vector Enemy::randStartPos()
{
    df::Vector temp_pos;

    // Get world boundaries.
    int world_horiz = (int)WM.getBoundary().getHorizontal();
    int world_vert = (int)WM.getBoundary().getVertical();

    // x is off right side of window.
    temp_pos.setX((float)(world_horiz + rand() % world_horiz + 3));

    // y is in vertical range.
    temp_pos.setY(rand() % (world_vert - 4) + 4.0f);

    // If collision, move right slightly until empty space.
    df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
    while (!collision_list.isEmpty()) {
        temp_pos.setX(temp_pos.getX() + 3);
        collision_list = WM.getCollisions(this, temp_pos);
    }

    return temp_pos;
}
