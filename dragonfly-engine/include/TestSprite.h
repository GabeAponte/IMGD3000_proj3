// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// An object used for sprite testing

#pragma once
#include "DisplayManager.h"
#include "Object.h"

namespace df {

	class TestSprite : public Object {

	private:
		Object* m_p_hit = nullptr; // tracks the current object collided with

	public:
		TestSprite();
		~TestSprite();

		int eventHandler(const Event* p_e);	// OVERRIDE
		int draw();							// OVERRIDE
	};
}