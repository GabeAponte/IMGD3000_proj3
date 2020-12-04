// Gabriel Aponte
// gaaponte@wpi.edu

//
// Leaderboard.cpp
// Handles the leaderboard display
//

#include <EventKeyboard.h>
#include <WorldManager.h>
#include <DisplayManager.h>
#include <GameManager.h>
#include "..\header_files\GameStart.h"
#include "..\header_files\Leaderboard.h"

using namespace df;

Leaderboard::Leaderboard()
{
    // Initialize vars
    allScores = LEADERBOARD.getAllScores();
    setAltitude(MAX_ALTITUDE);
    latestScore = NULL;
    displayLatestBadScore = false;
}

// Constructor that takes in the latest player and their score
Leaderboard::Leaderboard(string playerName, int score)
{
    // Initialize vars
    LEADERBOARD.writeNewScore(score, playerName);
    allScores = LEADERBOARD.getAllScores();
    setAltitude(MAX_ALTITUDE);
    latestPlayer = playerName;
    latestScore = score;
    displayLatestBadScore = false;
}

// Function that handles events
int Leaderboard::eventHandler(const df::Event* p_e)
{
    // Handles keyboard events
    if (p_e->getType() == df::KEYBOARD_EVENT) {
        df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*) p_e;
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            switch (p_keyboard_event->getKey()) {

            // Escape key to leave the leaderboard
            case df::Keyboard::ESCAPE:
                new GameStart();
                df::WM.markForDelete(this);
                break;
            // Q key to end the game
            case df::Keyboard::Q:
                GM.setGameOver();
                break;
            default:
                break;
            }
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

// Function that draws the leaderboard
int Leaderboard::draw()
{
    DM.drawString(Vector(DM.getHorizontal() / 2, 3), "Leaderboards:", df::CENTER_JUSTIFIED, df::Color::YELLOW);
    DM.drawString(Vector(DM.getHorizontal() / 2 - 20, 6), "Waves Survived:", df::CENTER_JUSTIFIED, df::Color::YELLOW);
    DM.drawString(Vector(DM.getHorizontal() / 2 + 20, 6), "Player Name:", df::CENTER_JUSTIFIED, df::Color::YELLOW);
    DM.drawString(Vector(3, 1.5), "'ESC' for main menue", df::LEFT_JUSTIFIED, df::Color::RED);
    
    int index = 1;
    float xPosition = 8.0;

    // Draw up to 15 of the top scores
    std::vector<ScoresIOStreamer::Score*>::iterator it;
    for (it = allScores.begin(); it != allScores.end() && index <= 15; it++) {
        DM.drawString(Vector(DM.getHorizontal() / 2 - 20, xPosition), std::to_string((*it)->score), df::CENTER_JUSTIFIED, df::Color::GREEN);
        DM.drawString(Vector(DM.getHorizontal() / 2 + 20, xPosition), (*it)->player, df::CENTER_JUSTIFIED, df::Color::GREEN);
        xPosition += 1.5;
        index++;

        // Check if this leaderboard is being drawn after a player dies
        if (latestScore != NULL) {

            // Check if there are at least 15 scores already drawn
            if (index == 15 && registerLatestBadScore) {

                // Set the 15th player and scores
                lastTopScore = (*it)->score;
                lastTopPlayer = (*it)->player;

                // No need to last player in list again register again
                registerLatestBadScore = false;
            }

            // Toggle the display of a lower score if it is not present in the top 15
            if (latestScore < lastTopScore || (latestScore == lastTopScore && lastTopPlayer != latestPlayer)) {
                displayLatestBadScore = true;
            }
        }

        // Draws the lastest bad score underneath the top 15 in red
        if (displayLatestBadScore) {
            DM.drawString(Vector(DM.getHorizontal() / 2 - 20, DM.getVertical() - 4), std::to_string(latestScore), df::CENTER_JUSTIFIED, df::Color::RED);
            DM.drawString(Vector(DM.getHorizontal() / 2 + 20, DM.getVertical() - 4), latestPlayer, df::CENTER_JUSTIFIED, df::Color::RED);
        }
    }

    return 0;
}
