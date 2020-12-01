// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// A simple object that moves with a constant velocity

#pragma once
#include "Object.h"

namespace df {

	class TestSlider : public Object {

	private:

	public:
		TestSlider();
		~TestSlider();

		int eventHandler(const Event* p_e);	// OVERRIDE
		int draw();							// OVERRIDE
	};
}
