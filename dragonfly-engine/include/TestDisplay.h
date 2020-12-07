// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// An object that runs DisplayManager testing

#pragma once
#include "Object.h"

namespace df {

	class TestDisplay : public Object {

	private:
		bool show_message = true;
		bool toggle_color = false;
		Vector m_cursor;
		char m_cursor_char = '+';

	public:
		TestDisplay();
		~TestDisplay();

		int eventHandler(const Event* p_e);	// OVERRIDE
		int draw();							// OVERRIDE
	};
}