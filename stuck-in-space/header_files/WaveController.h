// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// WaveController.h
// Handles all logic for spawning enemies and advancing the wave
//

#pragma once

#include <map>
#include <Object.h>
#include <EventStep.h>
#include "../header_files/EventEnemyDeath.h"

#define START_DIFFICULTY    0	    // The starting difficulty.
#define DIFFICULTY_INCREASE 5		// The difficulty increase per wave (including the start of the first one)
#define WAVE_BEGIN_DELAY    75		// The downtime between one wave ending and the next starting
#define ENEMY_SPAWN_DELAY   15		// The delay before the first enemy of a wave appears
#define MAX_ENEMY_SPAWN_DELAY 60    // The maximum delay before the first enemy of a wave appears
#define SPAWN_X_OFFSET      8		// The horizontal distance off screen to spawn enemies at
#define SPAWN_Y_OFFSET      5		// The Vertical distance off screen to spawn enemies at
#define SIDE_SPAWN_CHANCE   0.85	// The probability that a spawned enemy will appear from the side of the screen
#define AMMO_QUOTA_FACTOR   0.1		// The factor the difficulty is multiplied by when calculating the ammo drop quota
#define AMMO_SPAWN_CHANCE   0.08	// The probability that an ammo pickup will spawn when an enemy dies
#define RAND_DICE_SIZE      100		// The size of the "die" rolled when choosing spawn chance (it picks a random int up to DICE_SIZE and divides it by DICE_SIZE)

// Enum values for all the possible enemy types
enum enemy_type {
	E_BASIC,
	E_TOUGH,
	E_FAST,
	E_TRICKY,
	E_SWARM,
	E_SHOOTER,
};

// Struct that holds information on all the enemies
struct enemy_data {
	enemy_type enemyType;
	int minDifficulty;
	int difficultyCost;
};

class WaveController : public df::Object {

private:

	bool disabled;		    // Set to true to shut down wave controller updates
	int waveNumber;			// The current wave the player is on
	int difficulty;			// The current value of enemy difficulties
	bool waveComplete;		// Whether the current wave is complete
	int waveBeginWait;	    // The delay before the next wave spawns
	int enemySpawnTotal;	// The total number of enemies to spawn this wave
	int enemySpawnCount;	// The number of enemies spawned so far this wave
	int enemyKillCount;		// The number of enemies killed so far this wave
	int enemySpawnWait;		// The delay before the next enemy spawns
	int ammoSpawnCount;		// The number of ammo boxes spawned this wave
	int ammoSpawnQuota;		// The minimum number of ammo boxes to spawn this wave
	int messageCooldown;    // The rate at which to show messages
	bool displayWaveEnd;	// Toogles the wave ended message
	bool displayWaveStart;  // Toggles the wave started message
	std::vector<enemy_type> enemySpawnList;		 // The list of enemies to spawn
	std::vector<struct enemy_data> enemyOptions; // Vector containg all enemy type spawn settings

	// Handle step event
	void step();

	// Handle enemy death event
	void enemyDead(const EventEnemyDeath* p_enemydeath_event);

	// Generate a new wave
	void beginWave();

	// Spawn an enemy if able
	void spawnEnemy();

	// Spawn an ammo drop at the location
	void spawnAmmo(df::Vector position);

	// Generate a random float from 0 to 1
	float randomPercent();

public:

	// Constructor / Deconstructors
	WaveController();
	~WaveController();

	// Handles events
	int eventHandler(const df::Event* p_e); // OVERRIDE

	// Get the current wave number
	int getWaveNumber();

	// Draws the current wave and wave ended/started messages
	int draw();
};
