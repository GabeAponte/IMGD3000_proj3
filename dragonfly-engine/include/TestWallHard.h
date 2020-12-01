// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// A simple object that acts as a solid wall

#pragma once
#include "Object.h"

namespace df {

	class TestWallHard : public Object {

	private:
		TestWallHard();
		Object* obj_hit;

	public:
		TestWallHard(Vector pos);
		~TestWallHard();

		int eventHandler(const Event* p_e);	// OVERRIDE
		int draw();							// OVERRIDE
	};
}