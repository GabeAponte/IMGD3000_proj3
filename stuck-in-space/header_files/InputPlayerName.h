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

class InputPlayerName : public df::Object
{
private:
	int wavesCompleted;		// Value of the last wave survived
	string playerName;		// Value of the current player
	std::vector<ScoresIOStreamer::Score*> allScores;	// Vector of all the scores 
	int keyRepeatWait;
	bool showTextCursor;	// Bool that toggles showing the text cursor
	int textCursorWait;

	// Function that handles events
	int eventHandler(const df::Event* p_e);

	// Function that draws the InputPlayerName display
	int draw();

	// Function that trims the leading and trailing whitespaces of a string
	string trim(string s);

public:

	// Constructor
	InputPlayerName(int wave);
};

