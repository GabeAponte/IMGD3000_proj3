//
// Bullet.h
//

#include "EventCollision.h"
#include "Object.h"

class Bullet : public df::Object {

 private:
  void out();
  void hit(const df::EventCollision *p_collision_event);

 public:
  Bullet();
  int eventHandler(const df::Event *p_e);
};
