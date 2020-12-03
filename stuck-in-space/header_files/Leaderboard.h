
#pragma once

#include <Object.h>
#include <Vector.h>
#include "../header_files/ScoresIOStreamer.h"

class Leaderboard : public df::Object
{
	private:
		std::vector<ScoresIOStreamer::Score*> allScores;
		int eventHandler(const df::Event* p_e);
		int draw();
		int latestScore;
		string latestPlayer;

		int lastTopScore;
		string lastTopPlayer;
		bool registerLatestBadScore = true;
		bool displayLatestBadScore = false;
	public:
		Leaderboard();
		Leaderboard(string playerName, int score);
};


