// Gabriel Aponte
// gaaponte@wpi.edu

//
// Leaderboard.h
// Handles the leaderboard display
//

#pragma once

#include <Object.h>
#include <Vector.h>
#include "../header_files/ScoresIOStreamer.h"

class Leaderboard : public df::Object {

private:
	
	int latestScore;				// The value of the most recent recored score
	string latestPlayer;			// The value of the most recent recored player
	int lastTopScore;               // The value of the last score in the leaderboard list (15th)
	string lastTopPlayer;			// The value of the last player in the leaderboard list (15th) 
	bool registerLatestBadScore = true;			     // Bool that toggles recording of a low score (< 15th)
	bool displayLatestBadScore = false;				 // Bool that toggles displaying of a low score (< 15th)
	std::vector<ScoresIOStreamer::Score*> allScores; // Vector of all the scores 

	// Function that handles events
	int eventHandler(const df::Event* p_e);

	// Function that draws the leaderboard
	int draw();

public:

	// Constructor
	Leaderboard();

	// Constructor that takes in the latest player and their score
	Leaderboard(string playerName, int score);
};
