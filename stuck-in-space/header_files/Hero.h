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
#define SPREAD_SPACING      10  // the spacing (in degrees) between Spread bullets

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
  Reticle *p_reticle;

  bool firing;
  int fireCooldown;
  int shieldIntegrity;
  int lives;
  std::map<player_weapon, std::string> weaponName;
  std::map<player_weapon, int> weaponAmmo;
  std::map<player_weapon, int> weaponCooldown;
  std::map<player_weapon, std::string> weaponSound;
  player_weapon currentWeapon;
  df::Vector projectileStart; // the position projectiles currently spawn from
  
  void mouse(const df::EventMouse *p_mouse_event);
  void kbd(const df::EventKeyboard *p_keyboard_event);
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
  Hero();
  ~Hero();
  int eventHandler(const df::Event *p_e); // OVERRIDE
  int draw(); // OVERRIDE
};
