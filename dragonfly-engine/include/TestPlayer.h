// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// A simple object controllable with WASD or Arrows

#pragma once
#include "Object.h"

namespace df {

	class TestPlayer : public Object {

	private:
		bool oob_state = false;

	public:
		TestPlayer();
		~TestPlayer();

		int eventHandler(const Event* p_e);	// OVERRIDE
		int draw();							// OVERRIDE
	};
}