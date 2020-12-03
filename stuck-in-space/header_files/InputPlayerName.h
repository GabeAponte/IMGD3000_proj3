#pragma once

#include <Object.h>
#include <Vector.h>
#include "../header_files/ScoresIOStreamer.h"

class InputPlayerName : public df::Object
{

private:
	int wavesCompleted;
	string playerName;
	std::vector<ScoresIOStreamer::Score*> allScores;
	int eventHandler(const df::Event* p_e);
	int draw();
	string trim(string s);
public:
	InputPlayerName(int wave);

};

