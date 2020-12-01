// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// A simple object that acts as a spectral wall

#pragma once
#include "Color.h"
#include "Object.h"

namespace df {

	class TestWallSpectral : public Object {

	private:
		TestWallSpectral();
		Object* obj_hit;
		Color color = GREY;

	public:
		TestWallSpectral(Vector pos);
		~TestWallSpectral();

		int eventHandler(const Event* p_e);	// OVERRIDE
		int draw();							// OVERRIDE
	};
}