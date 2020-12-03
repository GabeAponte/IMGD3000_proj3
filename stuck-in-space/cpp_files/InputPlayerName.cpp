#include "..\header_files\InputPlayerName.h"
#include "..\header_files\Leaderboard.h"
#include <DisplayManager.h>
#include <WorldManager.h>
#include <EventKeyboard.h>
#include <regex>
#include <string>

using namespace df;

InputPlayerName::InputPlayerName(int wave)
{
	wavesCompleted = wave;
    playerName = "";
	setAltitude(MAX_ALTITUDE);
}

int InputPlayerName::eventHandler(const df::Event* p_e)
{
    if (p_e->getType() == df::KEYBOARD_EVENT) {
        df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*) p_e;
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            switch (p_keyboard_event->getKey()) {
            case df::Keyboard::RETURN: 			// Leave leaderboard

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
				if(playerName.size() < 36)
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
				if(playerName != "")
				playerName.pop_back();
				break;
            default:
                break;
            }
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

int InputPlayerName::draw()
{
	DM.drawString(Vector(DM.getHorizontal() / 2, 8), "You survived " + std::to_string(wavesCompleted) + " waves.", df::CENTER_JUSTIFIED, df::Color::YELLOW);
	DM.drawString(Vector(DM.getHorizontal() / 2, 10), "Enter your name and press enter to save your score:", df::CENTER_JUSTIFIED, df::Color::YELLOW);
	DM.drawString(Vector(DM.getHorizontal() / 2, 12), playerName, df::CENTER_JUSTIFIED, df::Color::GREEN);

	return 0;
}

string InputPlayerName::trim(string s) {
    regex e("^\\s+|\\s+$");   // remove leading and trailing spaces
    return regex_replace(s, e, "");
}
