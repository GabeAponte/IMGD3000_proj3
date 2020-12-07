#pragma once
#include "Vector.h"
#include "Event.h"

namespace df {

	const std::string MSE_EVENT = "df::mouse";

	// Types of mouse actions Dragonfly recognizes
	enum EventMouseAction {
		UNDEFINED_MOUSE_ACTION = -1,
		CLICKED,	// mouse button was just pressed
		RELEASED,	// mouse button was just released
		PRESSED,	// mouse button is held down (inconsistent terminology with key press)
		MOVED,		// mouse was moved
		SCROLLED,	// mouse wheel was scrolled
	};

	// Keys Dragonfly recognizes
	namespace Mouse {

		enum Button {
			UNDEFINED_MOUSE_BUTTON = -1,
			LEFT, RIGHT, MIDDLE,
		};
	}

	class EventMouse : public Event {

	private:
		EventMouseAction m_mouse_action;
		Mouse::Button m_mouse_button;
		Vector m_mouse_xy;
		float m_mouse_scroll;

	public:
		EventMouse();
		~EventMouse();

		// Get/Set mouse event action
		void setMouseAction(EventMouseAction new_action);
		EventMouseAction getMouseAction() const;

		// Get/Set mouse button
		void setMouseButton(Mouse::Button new_button);
		Mouse::Button getMouseButton() const;

		// Get/Set mouse position
		void setMousePosition(Vector new_position);
		Vector getMousePosition() const;

		// Get/Set mouse scroll delta
		void setMouseScroll(float scroll_delta);
		float getMouseScroll() const;
	};
}