// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// A simple object that acts as a soft wall

#pragma once
#include "Color.h"
#include "Object.h"

namespace df {

	class TestWallSoft : public Object {

	private:
		TestWallSoft();
		Object* obj_hit;
		Color color = MIDBLUE;

	public:
		TestWallSoft(Vector pos);
		~TestWallSoft();

		int eventHandler(const Event* p_e);	// OVERRIDE
		int draw();							// OVERRIDE
	};
}