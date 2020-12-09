// Gabriel Aponte
// gaaponte@wpi.edu

//
// InputPlayerName.h
// Handles the InputPlayerName display
//

#include <regex>
#include <string>
#include <DisplayManager.h>
#include <WorldManager.h>
#include <EventKeyboard.h>
#include <EventStep.h>
#include <ResourceManager.h>
#include "..\header_files\Leaderboard.h"
#include "..\header_files\InputPlayerName.h"

using namespace df;

InputPlayerName::InputPlayerName(int wave) {

	// Initialize vars
	wavesCompleted = wave;
	playerName = "";
	keyRepeatWait = 0;
	showTextCursor = true;
	textCursorWait = TEXT_CURSOR_WAIT;

	// Set altitude to max and position to center screen
	setAltitude(MAX_ALTITUDE);
	setPosition(Vector(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2));
}

// Function that handles events
int InputPlayerName::eventHandler(const df::Event* p_e)
{
	// Handle keyboard input for name entry
	if (p_e->getType() == KEYBOARD_EVENT) {

		EventKeyboard* p_keyboard_event = (EventKeyboard*) p_e;
		bool key_pressed = p_keyboard_event->getKeyboardAction() == KEY_PRESSED;
		bool key_held = p_keyboard_event->getKeyboardAction() == KEY_DOWN && keyRepeatWait <= 0;
		if (key_pressed || key_held)
		{
			if (key_pressed)
			{
				keyRepeatWait = KEY_REPEAT_INITIALWAIT;
			}
			else
			{
				keyRepeatWait = KEY_REPEAT_WAIT;
			}
			switch (p_keyboard_event->getKey()) {
			case Keyboard::RETURN: {

				// Return key will bring player to the leaderboard
				Sound* p_sound = RM.getSound("select");
				p_sound->play();

				if (trim(playerName) != "") {
					new Leaderboard(trim(playerName), wavesCompleted);
					WM.markForDelete(this);
				}
				else {
					new Leaderboard("ANONYMOUS", wavesCompleted);
					WM.markForDelete(this);
				}
			}
				break;

			case(Keyboard::A):
				if (playerName.size() < 36)
					playerName += "A";
				break;
			case(Keyboard::B):
				if (playerName.size() < 36)
					playerName += "B";
				break;
			case(Keyboard::C):
				if (playerName.size() < 36)
					playerName += "C";
				break;
			case(Keyboard::D):
				if (playerName.size() < 36)
					playerName += "D";
				break;
			case(Keyboard::E):
				if (playerName.size() < 36)
					playerName += "E";
				break;
			case(Keyboard::F):
				if (playerName.size() < 36)
					playerName += "F";
				break;
			case(Keyboard::G):
				if (playerName.size() < 36)
					playerName += "G";
				break;
			case(Keyboard::H):
				if (playerName.size() < 36)
					playerName += "H";
				break;
			case(Keyboard::I):
				if (playerName.size() < 36)
					playerName += "I";
				break;
			case(Keyboard::J):
				if (playerName.size() < 36)
					playerName += "J";
				break;
			case(Keyboard::K):
				if (playerName.size() < 36)
					playerName += "K";
				break;
			case(Keyboard::L):
				if (playerName.size() < 36)
					playerName += "L";
				break;
			case(Keyboard::M):
				if (playerName.size() < 36)
					playerName += "M";
				break;
			case(Keyboard::N):
				if (playerName.size() < 36)
					playerName += "N";
				break;
			case(Keyboard::O):
				if (playerName.size() < 36)
					playerName += "O";
				break;
			case(Keyboard::P):
				if (playerName.size() < 36)
					playerName += "P";
				break;
			case(Keyboard::Q):
				if (playerName.size() < 36)
					playerName += "Q";
				break;
			case(Keyboard::R):
				if (playerName.size() < 36)
					playerName += "R";
				break;
			case(Keyboard::S):
				if (playerName.size() < 36)
					playerName += "S";
				break;
			case(Keyboard::T):
				if (playerName.size() < 36)
					playerName += "T";
				break;
			case(Keyboard::U):
				if (playerName.size() < 36)
					playerName += "U";
				break;
			case(Keyboard::V):
				if (playerName.size() < 36)
					playerName += "V";
				break;
			case(Keyboard::W):
				if (playerName.size() < 36)
					playerName += "W";
				break;
			case(Keyboard::X):
				if (playerName.size() < 36)
					playerName += "X";
				break;
			case(Keyboard::Y):
				if (playerName.size() < 36)
					playerName += "Y";
				break;
			case(Keyboard::Z):
				if (playerName.size() < 36)
					playerName += "Z";
				break;
			case(Keyboard::SPACE):
				if (playerName.size() < 36)
					playerName += " ";
				break;
			case(Keyboard::BACKSPACE):
				if (playerName != "")
					playerName.pop_back();
				break;
			default:
				break;
			}
		}
		return 1;
	}
	if (p_e->getType() == STEP_EVENT) {

		// Update text repeat timer
		if (keyRepeatWait > 0)
		{
			keyRepeatWait--;
		}

		// Toggle whether text cursor displays
		textCursorWait--;
		if (textCursorWait < 0)
		{
			textCursorWait = TEXT_CURSOR_WAIT;
			showTextCursor = !showTextCursor;
		}
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// Function that draws the InputPlayerName display
int InputPlayerName::draw()
{
	// Toggle wave vs waves
	std::string plural = "s";
	if (wavesCompleted == 1)
	{
		plural = "";
	}

	// Toggle cursor
	std::string text_cursor = " ";
	if (showTextCursor)
	{
		text_cursor = "_";
	}

	DM.drawString(Vector(DM.getHorizontal() / 2, 8), "You survived " + std::to_string(wavesCompleted) + " wave" + plural + ".", CENTER_JUSTIFIED, Color::YELLOW);
	DM.drawString(Vector(DM.getHorizontal() / 2, 10), "Enter your name and press enter to save your score:", CENTER_JUSTIFIED, Color::YELLOW);
	DM.drawString(Vector(DM.getHorizontal() / 2, 12), playerName + text_cursor, CENTER_JUSTIFIED, Color::ORANGE);

	return 0;
}

// Function that trims the leading and trailing whitespaces of a string
string InputPlayerName::trim(string s) 
{
	regex e("^\\s+|\\s+$");
	return regex_replace(s, e, "");
}
