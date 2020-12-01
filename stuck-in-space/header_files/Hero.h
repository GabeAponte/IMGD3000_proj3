//
// Hero.h
//

#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventCollision.h"
#include "Object.h"
#include "Reticle.h"

class Hero : public df::Object {

 private:
  Reticle *p_reticle;
  int fire_slowdown;
  int fire_countdown;
  int shield_integrity;
  int lives;
  void mouse(const df::EventMouse *p_mouse_event);
  void kbd(const df::EventKeyboard *p_keyboard_event);
  void fire(df::Vector target);
  void step();
  void overloadShield();
  df::Vector getPojectileStart(df::Vector target);
  void hit(const df::EventCollision* p_collision_event);

 public:
  Hero();
  ~Hero();
  int eventHandler(const df::Event *p_e);
};
