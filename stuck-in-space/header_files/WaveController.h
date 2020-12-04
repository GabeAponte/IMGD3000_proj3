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

#define START_DIFFICULTY    0   // the starting difficulty.
#define DIFFICULTY_INCREASE 5   // the difficulty increase per wave (including the start of the first one)
#define WAVE_BEGIN_DELAY    60  // the downtime between one wave ending and the next starting
#define ENEMY_SPAWN_DELAY   15  // the delay before the first enemy of a wave appears
#define MAX_ENEMY_SPAWN_DELAY 60
#define SPAWN_X_OFFSET      8   // the horizontal distance off screen to spawn enemies at
#define SPAWN_Y_OFFSET      5   // the Vertical distance off screen to spawn enemies at
#define SIDE_SPAWN_CHANCE   0.8 // the probability that a spawned enemy will appear from the side of the screen
#define AMMO_SPAWN_CHANCE   0.5 // the probability that an ammo pickup will spawn when an enemy dies
#define RAND_DICE_SIZE     100  // the size of the "die" rolled when choosing spawn chance (it picks a random int up to DICE_SIZE and divides it by DICE_SIZE)

enum enemy_type {
    E_BASIC,
    E_TOUGH,
    E_FAST,
    E_TRICKY,
    E_SPIRAL,
    E_SWARM,
    E_SHOOTER,
};

struct enemy_data {
    enemy_type enemyType;
    int minDifficulty;
    int difficultyCost;
};

class WaveController : public df::Object {

private:
    bool disabled; // set to true to shut down wave controller updates

    int waveNumber;
    int difficulty;
    std::vector<struct enemy_data> enemyOptions;

    bool waveComplete;   // whether the current wave is complete
    int waveBeginWait;   // the delay before the next wave spawns

    int enemySpawnCount; // the number of enemies spawned so far this wave
    int enemyKillCount;  // the number of enemies killed so far this wave
    int enemySpawnWait;  // the delay before the next enemy spawns
    std::vector<enemy_type> enemySpawnList; // the list of enemies to spawn
    
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
    WaveController();
    ~WaveController();

    // Handle game events
    int eventHandler(const df::Event* p_e); // OVERRIDE

    // Get the current wave number
    int getWave();
};
