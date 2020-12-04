//
// Bullet.cpp
//

#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"

#include "../header_files/Enemy.h"
#include "../header_files/Bullet.h"

using namespace df;

Bullet::Bullet() {
    // Link to "bullet" sprite.
    setSprite("bullet");

    // Set other object properties.
    setType("Bullet");

    setSolidness(SOFT);

    // Set the weapon type (defaults to W_MISSILE)
    weaponType = W_MISSILE;
}
Bullet::Bullet(player_weapon weapon_type) {
    // Link to "bullet" sprite.
    setSprite("bullet");

    // Set other object properties.
    setType("Bullet");

    // Set the weapon type
    // NOTE: All weapon attacks should have the "Bullet" type to allow general collision
    // TODO: modify this per weapon type
    weaponType = weapon_type;
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
    Object* other_object;
    // Check if first object was an enemy
    if (p_collision_event->getObject1()->getType() == "Saucer")
    {
        other_object = p_collision_event->getObject1();
    }
    // Check if second object was an enemy
    else if (p_collision_event->getObject2()->getType() == "Saucer")
    {
        other_object = p_collision_event->getObject2();
    }
    // No enemy hit, so don't proceed
    else
    {
        return;
    }
    
    // Delete the enemy hit
    // TODO: change to hurting the target
    WM.markForDelete(other_object);
    
    // Delete this projectile object unless weapon type is piercing
    if (weaponType != W_LASER && weaponType != W_PLASMA)
    {
        WM.markForDelete(this);
    }
}


// Get bullet type
player_weapon Bullet::getWeaponType()
{
    return weaponType;
}