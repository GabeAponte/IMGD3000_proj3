//
// Explosion.h
//

#pragma once

#include "Object.h"

class Explosion : public df::Object {

protected:
	int time_to_live;
	void step();

public:
	Explosion();
	int eventHandler(const df::Event* p_e);
};
