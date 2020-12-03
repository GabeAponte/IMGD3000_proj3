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
	int wavesCompleted;
	string playerName;
	std::vector<ScoresIOStreamer::Score*> allScores;
	int keyRepeatWait;
	bool showTextCursor;
	int textCursorWait;
	int eventHandler(const df::Event* p_e);
	int draw();
	string trim(string s);
public:
	InputPlayerName(int wave);

};

