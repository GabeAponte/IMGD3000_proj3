// Gabriel Aponte
// gaaponte@wpi.edu

//
// InputPlayerName.h
// Handles the InputPlayerName display
//

#include <DisplayManager.h>
#include <WorldManager.h>
#include <EventKeyboard.h>
#include <EventStep.h>
#include <regex>
#include <string>
#include "..\header_files\Leaderboard.h"
#include "..\header_files\InputPlayerName.h"

using namespace df;

InputPlayerName::InputPlayerName(int wave)
{
	// Initialize vars
	wavesCompleted = wave;
	playerName = "";
	keyRepeatWait = 0;
	showTextCursor = true;
	textCursorWait = TEXT_CURSOR_WAIT;
	setAltitude(MAX_ALTITUDE);
}

// Function that handles events
int InputPlayerName::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::KEYBOARD_EVENT) {

		// Handle keyboard input for name entry
		df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*) p_e;
		bool key_pressed = p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED;
		bool key_held = p_keyboard_event->getKeyboardAction() == df::KEY_DOWN && keyRepeatWait <= 0;
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
			case df::Keyboard::RETURN:

				// Return key will bring player to the leaderboard
				if (trim(playerName) != "") {
					new Leaderboard(trim(playerName), wavesCompleted);
					df::WM.markForDelete(this);
				}
				else {
					new Leaderboard("ANONYMOUS", wavesCompleted);
					df::WM.markForDelete(this);
				}

				break;

			case(df::Keyboard::A):
				if (playerName.size() < 36)
					playerName += "A";
				break;
			case(df::Keyboard::B):
				if (playerName.size() < 36)
					playerName += "B";
				break;
			case(df::Keyboard::C):
				if (playerName.size() < 36)
					playerName += "C";
				break;
			case(df::Keyboard::D):
				if (playerName.size() < 36)
					playerName += "D";
				break;
			case(df::Keyboard::E):
				if (playerName.size() < 36)
					playerName += "E";
				break;
			case(df::Keyboard::F):
				if (playerName.size() < 36)
					playerName += "F";
				break;
			case(df::Keyboard::G):
				if (playerName.size() < 36)
					playerName += "G";
				break;
			case(df::Keyboard::H):
				if (playerName.size() < 36)
					playerName += "H";
				break;
			case(df::Keyboard::I):
				if (playerName.size() < 36)
					playerName += "I";
				break;
			case(df::Keyboard::J):
				if (playerName.size() < 36)
					playerName += "J";
				break;
			case(df::Keyboard::K):
				if (playerName.size() < 36)
					playerName += "K";
				break;
			case(df::Keyboard::L):
				if (playerName.size() < 36)
					playerName += "L";
				break;
			case(df::Keyboard::M):
				if (playerName.size() < 36)
					playerName += "M";
				break;
			case(df::Keyboard::N):
				if (playerName.size() < 36)
					playerName += "N";
				break;
			case(df::Keyboard::O):
				if (playerName.size() < 36)
					playerName += "O";
				break;
			case(df::Keyboard::P):
				if (playerName.size() < 36)
					playerName += "P";
				break;
			case(df::Keyboard::Q):
				if (playerName.size() < 36)
					playerName += "Q";
				break;
			case(df::Keyboard::R):
				if (playerName.size() < 36)
					playerName += "R";
				break;
			case(df::Keyboard::S):
				if (playerName.size() < 36)
					playerName += "S";
				break;
			case(df::Keyboard::T):
				if (playerName.size() < 36)
					playerName += "T";
				break;
			case(df::Keyboard::U):
				if (playerName.size() < 36)
					playerName += "U";
				break;
			case(df::Keyboard::V):
				if (playerName.size() < 36)
					playerName += "V";
				break;
			case(df::Keyboard::W):
				if (playerName.size() < 36)
					playerName += "W";
				break;
			case(df::Keyboard::X):
				if (playerName.size() < 36)
					playerName += "X";
				break;
			case(df::Keyboard::Y):
				if (playerName.size() < 36)
					playerName += "Y";
				break;
			case(df::Keyboard::Z):
				if (playerName.size() < 36)
					playerName += "Z";
				break;
			case(df::Keyboard::SPACE):
				if (playerName.size() < 36)
					playerName += " ";
				break;
			case(df::Keyboard::BACKSPACE):
				if (playerName != "")
					playerName.pop_back();
				break;
			default:
				break;
			}
		}
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT) {
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

	DM.drawString(Vector(DM.getHorizontal() / 2, 8), "You survived " + std::to_string(wavesCompleted) + " wave" + plural + ".", df::CENTER_JUSTIFIED, df::Color::YELLOW);
	DM.drawString(Vector(DM.getHorizontal() / 2, 10), "Enter your name and press enter to save your score:", df::CENTER_JUSTIFIED, df::Color::YELLOW);
	DM.drawString(Vector(DM.getHorizontal() / 2, 12), playerName + text_cursor, df::CENTER_JUSTIFIED, df::Color::ORANGE);

	return 0;
}

// Function that trims the leading and trailing whitespaces of a string
string InputPlayerName::trim(string s) {
	regex e("^\\s+|\\s+$");
	return regex_replace(s, e, "");
}
