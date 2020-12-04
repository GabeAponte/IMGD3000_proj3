// Gabriel Aponte
// gaaponte@wpi.edu

//
// ScoresIOStreamer.cpp
// Handles the input and output for the leaderboard file
//

#include "../header_files/ScoresIOStreamer.h"

ScoresIOStreamer::ScoresIOStreamer()
{
}

// Singleton implementation to only have one instance of the streamer
ScoresIOStreamer& ScoresIOStreamer::getInstance()
{
    static ScoresIOStreamer leaderboard;
    return leaderboard;
};

// Writes a new player's score to the leaderboard file
void ScoresIOStreamer::writeNewScore(int score, string player)
{
    ofstream file(LEADERBOARD_TXT, ios::app);
    file << score << " " << player << "\n";
    file.close();
}

// Reads in all the players and scores from the leaderboard file
void ScoresIOStreamer::readLeaderboardFile()
{
    allScores.clear();
    ifstream file(LEADERBOARD_TXT);

    Score* currentLine = new Score();
    while (file >> currentLine->score >> ws && getline(file, currentLine->player)) {
        Score* temp = new Score();
        temp->player = currentLine->player;
        temp->score = currentLine->score;
        allScores.push_back(temp);
    }

    // Sort by highest to lowest
    std::sort(allScores.begin(), allScores.end(), &compareByScore);

    file.close();
}

// Comparator that sorts the scores by highest to lowest 
bool ScoresIOStreamer::compareByScore(const Score* a, const Score* b)
{
    return a->score > b->score;
}

// Gets all the players and their scores
vector<ScoresIOStreamer::Score*> ScoresIOStreamer::getAllScores()
{
    readLeaderboardFile();
    return allScores;
}
