// Gabriel Aponte
// gaaponte@wpi.edu

//
// Leaderboard.cpp
// Handles the leaderboard display
//

#include <ResourceManager.h>
#include <EventKeyboard.h>
#include <WorldManager.h>
#include <DisplayManager.h>
#include <GameManager.h>
#include "..\header_files\GameStart.h"
#include "..\header_files\Leaderboard.h"

using namespace df;

Leaderboard::Leaderboard() {

	// Initialize vars
	allScores = LEADERBOARD.getAllScores();
	latestScore = NULL;

	// Set altitude and center the position
	setAltitude(MAX_ALTITUDE);
	setPosition(Vector(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2));
}

// Constructor that takes in the latest player and their score
Leaderboard::Leaderboard(string playerName, int score) {

	// Initialize vars
	LEADERBOARD.writeNewScore(score, playerName);
	allScores = LEADERBOARD.getAllScores();
	latestPlayer = playerName;
	latestScore = score;

	// Set altitude and center the position
	setAltitude(MAX_ALTITUDE);
	setPosition(Vector(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2));
}

// Function that handles events
int Leaderboard::eventHandler(const df::Event* p_e)
{
	// Handles keyboard events
	if (p_e->getType() == KEYBOARD_EVENT) {
		EventKeyboard* p_keyboard_event = (EventKeyboard*) p_e;
		if (p_keyboard_event->getKeyboardAction() == KEY_PRESSED)

			switch (p_keyboard_event->getKey()) {

		    // Enter key and return to leave the leaderboard
			case Keyboard::RETURN: {
				Sound* p_sound = RM.getSound("select");
				p_sound->play();
				new GameStart();
				WM.markForDelete(this);
			}
				break;
			// Escape key to quit the game
			case Keyboard::ESCAPE:
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
	float mid_x = WM.getView().getCorner().getX() + WM.getView().getHorizontal() / 2;
	float bottom_y = WM.getView().getCorner().getY() + WM.getView().getVertical();
	DM.drawString(Vector(mid_x, 3), "\\===\\  L E A D E R B O A R D  /===/", CENTER_JUSTIFIED);
	DM.drawString(Vector(mid_x - 25, 6), "Waves Survived:", CENTER_JUSTIFIED);
	DM.drawString(Vector(mid_x + 20, 6), "Player Name:", CENTER_JUSTIFIED);
	DM.drawString(Vector(mid_x, bottom_y-3), "RETURN: [Enter]", CENTER_JUSTIFIED);
	DM.drawString(Vector(mid_x, bottom_y-2), "QUIT: [Esc]", CENTER_JUSTIFIED);

	int index = 1;
	float y_position = 8.0;

	// Draw up to 15 of the top scores
	bool player_on_board = false;
	std::vector<ScoresIOStreamer::Score*>::iterator it;
	for (it = allScores.begin(); it != allScores.end() && index <= 15; it++) {

		// Score color will be light gray
		Color player_color = Color::LTGRAY;

		// If drawing current round's score, use a different color
		if (latestScore != NULL && latestScore == (*it)->score && latestPlayer == (*it)->player)
		{
			player_color = Color::YELLOW;
			player_on_board = true;
		}

		DM.drawString(Vector(mid_x - 25, y_position), std::to_string((*it)->score), CENTER_JUSTIFIED, player_color);
		DM.drawString(Vector(mid_x + 20, y_position), (*it)->player, CENTER_JUSTIFIED, player_color);
		y_position += 1.5;
		index++;
	}

	// Check if this leaderboard is being drawn after a player dies
	if (latestPlayer != "") {
		// Toggle the display of a lower score if it is not present in the top 15
		if (!player_on_board)
		{
			// Draws the lastest bad score underneath the top 15 in red
			DM.drawString(Vector(mid_x - 25, bottom_y - 5), std::to_string(latestScore), CENTER_JUSTIFIED, Color::RED);
			DM.drawString(Vector(mid_x + 20, bottom_y - 5), latestPlayer, CENTER_JUSTIFIED, Color::RED);
		}
	}

	return 0;
}
