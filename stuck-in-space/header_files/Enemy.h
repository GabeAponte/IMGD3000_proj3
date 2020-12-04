// Gabriel Aponte
// gaaponte@wpi.edu

//
// InputPlayerName.h
// Handles the logic for a Basic Enemy
//

#pragma once
 
#include "Object.h"
#include "EventCollision.h"
 
class Enemy : public df::Object {
 
 private:
  float realSpeed;
  void hit(const df::EventCollision *p_collision_event);
  void targetHero(df::Vector position);

 public:
  Enemy(df::Vector start_pos);
  ~Enemy();
  int eventHandler(const df::Event *p_e);
  
  // Set/get the enemy's real speed (df speed is unreliable)
  void setRealSpeed(float new_speed);
  float getRealSpeed() const;
};
