#include "../header_files/ScoresIOStreamer.h"

ScoresIOStreamer::ScoresIOStreamer()
{
}

// Singleton implementation to only have one instance of the leaderboard
ScoresIOStreamer& ScoresIOStreamer::getInstance()
{
    static ScoresIOStreamer leaderboard;
    return leaderboard;
};


void ScoresIOStreamer::writeNewScore(int score, string player)
{
    ofstream file(LEADERBOARD_TXT, ios::app);
    file << score << " " << player << "\n";
    file.close();
}

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

    std::sort(allScores.begin(), allScores.end(), &compareByScore);

    file.close();
}

vector<ScoresIOStreamer::Score*> ScoresIOStreamer::getAllScores()
{
    readLeaderboardFile();
    return allScores;
}

bool ScoresIOStreamer::compareByScore(const Score* a, const Score* b)
{
    return a->score > b->score;
}

