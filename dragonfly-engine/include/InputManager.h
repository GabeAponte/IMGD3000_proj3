#pragma once
#include <map>
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Manager.h"

namespace df {

	// Two-letter access macro
	#define IM InputManager::getInstance()

	class InputManager : public Manager {

	private:
		InputManager();							// Private (a singleton)
		InputManager(InputManager const&);		// Don't allow copy
		void operator=(InputManager const&);	// Don't allow assignment
		sf::RenderWindow* m_p_window;
		std::map<sf::Keyboard::Key, Keyboard::Key> m_key_map;
		std::map<sf::Mouse::Button, Mouse::Button> m_mouse_map;
		Vector m_mouse_position;

	public:
		~InputManager();

		// Get the one and only instance of the InputManager .
		static InputManager & getInstance();

		// Get window ready to capture input
		// Return 0 if ok, else return −1.
		int startUp();
		
		// Revert back to normal window mode
		void shutDown();
		
		// Get input from the keyboard and mouse
		// Pass event along to all Objects
		void getInput();

		// Check whether a key is defined in Dragonfly
		bool keyDefined(sf::Keyboard::Key key) const;

		// Check whether a mouse button is defined in Dragonfly
		bool mouseButtonDefined(sf::Mouse::Button button) const;
	};
}