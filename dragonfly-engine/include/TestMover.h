// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// A object used for collision testing that moves with a constant velocity from a specified point

#pragma once
#include "Object.h"

namespace df {

	class TestMover : public Object {

	private:
		TestMover();
		bool wall_hit = false;	// Whether this collided with a wall object
		Object* obj_hit = NULL;	// The object collided with 

	public:
		TestMover(Vector pos);
		~TestMover();

		int eventHandler(const Event* p_e);	// OVERRIDE
		int draw();							// OVERRIDE
	};
}
