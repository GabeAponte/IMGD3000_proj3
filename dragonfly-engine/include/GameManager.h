// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

#pragma once
#include <stdarg.h>
#include "Clock.h"
#include "Manager.h"

#define DEFAULT_FRAME_TIME 33	// in ms

namespace df {

	// Two-letter access macro
	#define GM GameManager::getInstance()

	class GameManager : public Manager {

	private:
		GameManager();								// No constructing
		GameManager(const GameManager&);			// No copying
		GameManager& operator=(const GameManager&);	// No assigning

		Clock* time_clock;			// reference to the game manager's clock
		bool game_over = true;		// whether the game has ended
		long int step_count = 0;	// tracks the number of steps elapsed
		int frame_time = DEFAULT_FRAME_TIME; // frame time in ms
		int overflow_time = 0;		// extra time spent in one step

	public:
		~GameManager();

		// Return singleton instance
		static GameManager& getInstance();

		int startUp();		// OVERRIDE
		void shutDown();	// OVERRIDE
		
		// Handle the game loop
		void run();

		// Set the game over state (defaults to true)
		// The game loop won't run while game_over is true
		void setGameOver(bool new_state = true);

		/// Return the game over state
		bool getGameOver() const;

		// Return the frame time
		int getFrameTime() const;

		// Return the current step count
		long int getStepCount() const;
	};
}