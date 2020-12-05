// Gabriel Aponte
// gaaponte@wpi.edu

//
// Enemy.h
// Handles the logic for a Basic Enemy
//

#pragma once

#include "Object.h"
#include "EventCollision.h"
#include "../header_files/WaveController.h"

class Enemy : public df::Object {

private:
	float realSpeed;
	int hit_points;
	int fireCooldown;
	enemy_type type;
	bool killedByPlayer;
	bool stopMoving;
	bool canFire;
	void hit(const df::EventCollision* p_collision_event);
	void targetHero(df::Vector position);
	void setEnemyTypeSpeed();
	void setEnemyTypeSprite();
	void setEnemyTypeHitPoints();
	void fire();

public:
	Enemy(df::Vector start_pos, enemy_type e_type);
	~Enemy();
	int eventHandler(const df::Event* p_e);

	// Set/get the enemy's real speed (df speed is unreliable)
	void setRealSpeed(float new_speed);
	float getRealSpeed() const;
};
