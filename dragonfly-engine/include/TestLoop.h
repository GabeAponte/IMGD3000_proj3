// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

#pragma once
#include "Clock.h"
#include "Object.h"

namespace df {
	
	class TestLoop : public Object {

	private:
		Clock* m_timer;

	public:
		TestLoop();
		~TestLoop();

		int eventHandler(const Event* p_e);	// OVERRIDE
		int draw();							// OVERRIDE
	};
}
