// Gabriel Aponte
// gaaponte@wpi.edu

//
// InputPlayerName.h
// Handles the InputPlayerName display
//

#pragma once

#include <Object.h>
#include <Vector.h>
#include "../header_files/ScoresIOStreamer.h"

#define KEY_REPEAT_INITIALWAIT 16
#define KEY_REPEAT_WAIT 4
#define TEXT_CURSOR_WAIT 15

class InputPlayerName : public df::Object {

private:

	int wavesCompleted;		// Value of the last wave survived
	string playerName;		// Value of the current player
	int keyRepeatWait;      // Indicates the rate at which to register repeated keys
	bool showTextCursor;	// Bool that toggles showing the text cursor
	int textCursorWait;     // Indiactes the rate at which to show the text cursor

	// Handles events
	int eventHandler(const df::Event* p_e);

	// Draws the InputPlayerName display
	int draw();

	// Trims the leading and trailing whitespaces of a string
	string trim(string s);

public:

	// Constructor
	InputPlayerName(int wave);
};

