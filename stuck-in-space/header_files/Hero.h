//
// Hero.h
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
  int fireCooldown;
  int shieldIntegrity;
  int lives;
  std::map<player_weapon, std::string> weaponName;
  std::map<player_weapon, int> weaponAmmo;
  std::map<player_weapon, int> weaponCooldown;
  std::map<player_weapon, std::string> weaponSound;
  player_weapon currentWeapon;
  void mouse(const df::EventMouse *p_mouse_event);
  void kbd(const df::EventKeyboard *p_keyboard_event);
  void fire(df::Vector target, df::Vector origin);
  void step();
  void overloadShield();
  void hit(const df::EventCollision* p_collision_event);

  // Update the player's sprite based on the reticle location
  void updateSprite();

  void setProjectileStart(int index);

  df::Vector projectileStart;

 public:
  Hero();
  ~Hero();
  int eventHandler(const df::Event *p_e); // OVERRIDE
  int draw(); // OVERRIDE
};
