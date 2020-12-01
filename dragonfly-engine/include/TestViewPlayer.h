// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// A simple object controllable with WASD or Arrows

#pragma once
#include "Object.h"

namespace df {

	class TestViewPlayer : public Object {

	private:

	public:
		TestViewPlayer();
		~TestViewPlayer();

		int eventHandler(const Event* p_e);	// OVERRIDE
		int draw();							// OVERRIDE
	};
}