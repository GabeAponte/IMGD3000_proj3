// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// A simple sprite object controllable with WASD or Arrows

#pragma once
#include "Object.h"

namespace df {

	class TestSpritePlayer : public Object {

	private:

	public:
		TestSpritePlayer();
		~TestSpritePlayer();

		int eventHandler(const Event* p_e);	// OVERRIDE
		int draw();							// OVERRIDE
	};
}