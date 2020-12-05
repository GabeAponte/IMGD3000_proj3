// Gabriel Aponte
// gaaponte@wpi.edu

//
// ScoresIOStreamer.h
// Handles the input and output for the leaderboard file
//

#pragma once

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Leaderboard txt file
const string LEADERBOARD_TXT = "leaderboard.txt";

// Shorthand to access the ScoresIOStreamer singleton implementation
#define LEADERBOARD ScoresIOStreamer::getInstance()

class ScoresIOStreamer
{
public:

	// Struct that stores the player name and their score
	struct Score
	{
		string player;
		int score = 0;
	};

	// Gets the single instance of this class
	static ScoresIOStreamer& getInstance();

	// Writes a new player's score to the leaderboard file
	void writeNewScore(int score, string player);

	// Reads in all the players and scores from the leaderboard file
	void readLeaderboardFile();

	// Gets all the players and their scores
	vector<Score*> getAllScores();

private:
	ScoresIOStreamer();                         // Private since a singleton.
	ScoresIOStreamer(ScoresIOStreamer const&);  // Don't allow copy.
	void operator=(ScoresIOStreamer const&);    // Don't allow assignment.

	// Vector that stores all the scores read in from a file
	vector<Score*> allScores;

	// Comparator that sorts the scores by highest to lowest 
	static bool compareByScore(const Score* a, const Score* b);
};