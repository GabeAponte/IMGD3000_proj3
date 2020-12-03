#pragma once

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string LEADERBOARD_TXT = "leaderboard.txt";

#define LEADERBOARD ScoresIOStreamer::getInstance()

class ScoresIOStreamer
{
    public:

        struct Score
        {
            string player;
            int score = 0;
        };

        static ScoresIOStreamer& getInstance();
        void writeNewScore(int score, string player);
        void readLeaderboardFile();
        vector<Score*> getAllScores();

    private:
        ScoresIOStreamer();                      // Private since a singleton.
        ScoresIOStreamer(ScoresIOStreamer const&);    // Don't allow copy.
        void operator=(ScoresIOStreamer const&); // Don't allow assignment.
        vector<Score*> allScores;
        static bool compareByScore(const Score* a, const Score* b);
};

