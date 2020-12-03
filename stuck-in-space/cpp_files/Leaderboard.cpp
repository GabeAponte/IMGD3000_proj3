#include "..\header_files\Leaderboard.h"
#include <EventKeyboard.h>
#include <WorldManager.h>
#include "../header_files/GameStart.h"
#include <DisplayManager.h>
#include <GameManager.h>

using namespace df;

Leaderboard::Leaderboard()
{
    allScores = LEADERBOARD.getAllScores();
    setAltitude(MAX_ALTITUDE);
    latestScore = NULL;
    displayLatestBadScore = false;
}

Leaderboard::Leaderboard(string playerName, int score)
{
    LEADERBOARD.writeNewScore(score, playerName);
    allScores = LEADERBOARD.getAllScores();
    setAltitude(MAX_ALTITUDE);
    latestPlayer = playerName;
    latestScore = score;
    displayLatestBadScore = false;
}

int Leaderboard::eventHandler(const df::Event* p_e)
{
    if (p_e->getType() == df::KEYBOARD_EVENT) {
        df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*) p_e;
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            switch (p_keyboard_event->getKey()) {
            case df::Keyboard::ESCAPE: 			// Leave leaderboard
                new GameStart();
                df::WM.markForDelete(this);
                break;
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

int Leaderboard::draw()
{
    DM.drawString(Vector(DM.getHorizontal() / 2, 3), "Leaderboards:", df::CENTER_JUSTIFIED, df::Color::YELLOW);
    DM.drawString(Vector(DM.getHorizontal() / 2 - 20, 6), "Waves Survived:", df::CENTER_JUSTIFIED, df::Color::YELLOW);
    DM.drawString(Vector(DM.getHorizontal() / 2 + 20, 6), "Player Name:", df::CENTER_JUSTIFIED, df::Color::YELLOW);
    DM.drawString(Vector(3, 1.5), "'ESC' for main menue", df::LEFT_JUSTIFIED, df::Color::RED);
    
    int index = 1;
    float xPosition = 8.0;

    std::vector<ScoresIOStreamer::Score*>::iterator it;
    for (it = allScores.begin(); it != allScores.end() && index <= 15; it++) {
        DM.drawString(Vector(DM.getHorizontal() / 2 - 20, xPosition), std::to_string((*it)->score), df::CENTER_JUSTIFIED, df::Color::GREEN);
        DM.drawString(Vector(DM.getHorizontal() / 2 + 20, xPosition), (*it)->player, df::CENTER_JUSTIFIED, df::Color::GREEN);
        xPosition += 1.5;
        index++;

        if (latestScore != NULL) {

            if (index == 15 && registerLatestBadScore) {
                lastTopScore = (*it)->score;
                lastTopPlayer = (*it)->player;
                registerLatestBadScore = false;
            }

            if (latestScore < lastTopScore || (latestScore == lastTopScore && lastTopPlayer != latestPlayer)) {
                displayLatestBadScore = true;
            }
        }

        if (displayLatestBadScore) {
            DM.drawString(Vector(DM.getHorizontal() / 2 - 20, DM.getVertical() - 4), std::to_string(latestScore), df::CENTER_JUSTIFIED, df::Color::RED);
            DM.drawString(Vector(DM.getHorizontal() / 2 + 20, DM.getVertical() - 4), latestPlayer, df::CENTER_JUSTIFIED, df::Color::RED);
        }
    }

    return 0;
}
