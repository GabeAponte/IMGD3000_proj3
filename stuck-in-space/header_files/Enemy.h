//
// Enemy.h
//

#pragma once
 
#include "Object.h"
#include "EventCollision.h"
 
class Enemy : public df::Object {
 
 private:
  void hit(const df::EventCollision *p_collision_event);
  void targetHero(df::Vector position);
  df::Vector randStartPos();

 public:
  Enemy(df::Vector start_pos);
  ~Enemy();
  int eventHandler(const df::Event *p_e);
};
