// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// Ammo.cpp
// An ammo pickup, with different weapon types assignable
//

#include <WorldManager.h>
#include <DisplayManager.h>
#include <EventStep.h>
#include "../header_files/EventAmmo.h"
#include "../header_files/Bullet.h"
#include "../header_files/Ammo.h"

using namespace df;

// inaccessible
Ammo::Ammo() {}

Ammo::Ammo(df::Vector position, player_weapon ammo_type, int ammo_value) {

  // Link to "Ammo" sprite.
  setSprite("ammo");

  // Set other object properties.
  setType("Ammo");

  // Set postion
  setPosition(position); 

  // Set altitude
  setAltitude(2);

  // Assign values
  ammoType = ammo_type;
  ammoValue = ammo_value;
  decayTimer = DECAY_TIME;

  // Set character based on ammo type
  switch (ammoType)
  {
  // No case for W_MISSILE (doesn't use ammo)
  case W_LASER:
      ammoChar = 'L';
      break;
  case W_BOMB:
      ammoChar = 'B';
      break;
  case W_SPREAD:
      ammoChar = 'S';
      break;
  case W_PLASMA:
      ammoChar = 'P';
      break;
  case W_RAPID:
      ammoChar = 'R';
      break;
  default:
      ammoChar = '?';
      break;
  }
}

// Handle event.
// Return 0 if ignored, else 1.
int Ammo::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::STEP_EVENT) {
    step();
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

// If ammo timer reaches 0, mark self for deletion.
void Ammo::step() {
    if (decayTimer > 0)
    {
        decayTimer--;
        if (decayTimer <= 0)
        {
            WM.markForDelete(this);
        }
    }
}

// If Bullet hits Ammo, mark both for deletion and collect Ammo
void Ammo::hit(const df::EventCollision *p_collision_event) {
    // Ignore hit if just spawned
    if (decayTimer > DECAY_TIME - 10)
    {
        return;
    }

    Object* other_object;
    // Check if first object was a bullet
    if (p_collision_event->getObject1()->getType() == "Bullet")
    {
        other_object = p_collision_event->getObject1();
    }
    // Check if second object was a bullet
    else if (p_collision_event->getObject2()->getType() == "Bullet")
    {
        other_object = p_collision_event->getObject2();
    }
    // No bullet hit, so don't proceed
    else
    {
        return;
    }

    // Remove this object
    WM.markForDelete(this);

    // report that ammo was collected
    EventAmmo ea(ammoType, ammoValue);
    WM.onEvent(&ea);
}


// Draw the ammo box and its identifying character
int Ammo::draw()
{
    // flicker if fading out
    if (decayTimer > 30 || (decayTimer/2) % 3 != 0)
    {
        Object::draw();
        DM.drawCh(getPosition() - Vector(0.5,0.5), ammoChar, ORANGE);
    }
    return 0;
}