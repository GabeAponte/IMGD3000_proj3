//
// Bullet.cpp
//

// Engine includes.
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"

// Game includes.
#include "../header_files/Bullet.h"
#include "../header_files/Enemy.h"

using namespace df;

Bullet::Bullet() {

  // Link to "bullet" sprite.
  setSprite("bullet");

  // Set other object properties.
  setType("Bullet");
}

// Handle event.
// Return 0 if ignored, else 1.
int Bullet::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::OUT_EVENT) {
    out();
    return 1;
  }

  if (p_e->getType() == df::COLLISION_EVENT) {
    const df::EventCollision *p_collision_event = dynamic_cast <const df::EventCollision *> (p_e);
    hit(p_collision_event);
    return 1;
  }

  // If get here, have ignored this event.
  return 0;
}

// If Bullet moves outside world, mark self for deletion.
void Bullet::out() {
  WM.markForDelete(this);
}

// If Bullet hits Enemy, mark Enemy and Bullet for deletion.
void Bullet::hit(const df::EventCollision *p_collision_event) {
  if ((p_collision_event -> getObject1() -> getType() == "Saucer") || 
      (p_collision_event -> getObject2() -> getType() == "Saucer")) {
    WM.markForDelete(p_collision_event->getObject1());
    WM.markForDelete(p_collision_event->getObject2());
  }
}
