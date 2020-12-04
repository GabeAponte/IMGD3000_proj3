// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// WaveController.cpp
// Handles all logic for spawning enemies and advancing the wave
//

#include <iostream>

#include <Vector.h>
#include <EventView.h>
#include <WorldManager.h>
#include "../header_files/EventEnemyDeath.h"
#include "../header_files/EventPlayerDeath.h"
#include "../header_files/Enemy.h"
#include "../header_files/Ammo.h"
#include "../header_files/WaveController.h"

using namespace df;

WaveController::WaveController()
{
	setType("WaveController");
	setSolidness(SPECTRAL);

	waveNumber = 0;
	difficulty = START_DIFFICULTY;

	// Set up enemy options
	// enemy_data is (enemy type, minimum difficulty, difficulty cost)
	enemyOptions.push_back(enemy_data{ E_BASIC, START_DIFFICULTY, 1 }); // basic enemy must require difficulty 0
	enemyOptions.push_back(enemy_data{ E_TOUGH, 0, 1 });
	enemyOptions.push_back(enemy_data{ E_FAST, 0, 1 });
	enemyOptions.push_back(enemy_data{ E_TRICKY, 0, 1 });
	enemyOptions.push_back(enemy_data{ E_SPIRAL, 0, 1 });
	enemyOptions.push_back(enemy_data{ E_SWARM, 100, 1 });
	enemyOptions.push_back(enemy_data{ E_SHOOTER, 0, 1 });

	enemySpawnCount = 0;
	enemyKillCount = 0;
	waveComplete = true;
	waveBeginWait = WAVE_BEGIN_DELAY;

	disabled = false; // start enabled
}


// Handle step event
void WaveController::step() {
	// Early exit if disabled
	if (disabled)
		return;

	// Detect if wave complete
	if (waveComplete)
	{
		waveBeginWait--;
		if (waveBeginWait <= 0)
		{
			// Begin next wave
			beginWave();
		}
	}
	// Otherwise, handle wave updates
	else
	{
		if (enemySpawnWait > 0)
		{
			enemySpawnWait--;
			if (enemySpawnWait <= 0)
			{
				// Spawn an enemy
				spawnEnemy();
			}
		}
	}
}


WaveController::~WaveController()
{
	enemyOptions.clear();
	enemySpawnList.clear();
}


// Handle enemy death event
void WaveController::enemyDead(const EventEnemyDeath* p_enemydeath_event)
{
	// Record enemy kill
	enemyKillCount++;
	
	// End wave if all enemies spawned and killed
	if (enemyKillCount >= enemySpawnCount && enemySpawnList.empty())
	{
		waveComplete = true;
		waveBeginWait = WAVE_BEGIN_DELAY;
		// TODO: Popup wave clear notification
	}

	// Spawn ammo refill at enemy location
	// TODO: maybe more likely if low on ammo
	if (randomPercent() >= AMMO_SPAWN_CHANCE)
	{
		spawnAmmo(p_enemydeath_event->getPosition());
	}
}


// Generate a new wave
void WaveController::beginWave()
{
	// Reset counts
	enemySpawnCount = 0;
	enemyKillCount = 0;
	enemySpawnList.clear();

	// Advance wave
	waveNumber++;
	std::cout << "STARTING WAVE " << waveNumber << "\n";
	EventView ev("WAVE", waveNumber, false);
	WM.onEvent(&ev);
	waveComplete = false;

	// Advance difficulty
	difficulty += DIFFICULTY_INCREASE;

	// Generate wave contents based on difficulty budget
	int difficulty_cost = 0;
	while (difficulty_cost < difficulty)
	{
		for (std::vector<enemy_data>::reverse_iterator it = enemyOptions.rbegin(); it != enemyOptions.rend(); it++)
		{
			// Ensure that enemy can be spawned
			// (is available at current difficulty and is within budget)
			if (it->minDifficulty <= difficulty && it->difficultyCost <= difficulty-difficulty_cost)
			{
				// Chance to spawn selected enemy. Otherwise, if no options found: default to basic enemy
				if (rand() % 2 == 1 || it == enemyOptions.rend() - 1)
				{
					// Queue enemy for spawning, and add cost to accumulated difficulty cost
					enemySpawnList.push_back(it->enemyType);
					difficulty_cost += it->difficultyCost;
					std::cout << "~ Queuing enemy of type " << (int) it->enemyType << " (Cost: " << difficulty_cost << "/" << difficulty << ")\n";
					if (difficulty_cost >= difficulty)
					{
						break;
					}
				}
			}
		}
	}

	// Start spawn timer
	enemySpawnWait = ENEMY_SPAWN_DELAY;
}


// Spawn an enemy of the designated type
void WaveController::spawnEnemy()
{
	// Reset spawn timer
	enemySpawnWait = rand() % MAX_ENEMY_SPAWN_DELAY;

	// Early exit if nothing to spawn
	if (enemySpawnList.empty())
		return;

	// Select and remove random enemy from spawn list
	std::vector<enemy_type>::iterator e_it = enemySpawnList.begin() + (rand() % enemySpawnList.size());
	enemy_type e_type = *e_it;
	enemySpawnList.erase(e_it);

	// Calculate spawn position
	Vector spawn_pos = Vector();
	if (randomPercent() <= SIDE_SPAWN_CHANCE)
	{
		// Spawn to the side of the map
		if (rand() % 2 == 0)
		{
			spawn_pos.setX(-SPAWN_X_OFFSET);
		}
		else
		{
			spawn_pos.setX(WM.getBoundary().getHorizontal() + SPAWN_X_OFFSET);
		}
		spawn_pos.setY((float) (rand() % (int)WM.getBoundary().getVertical()));
	}
	else
	{
		// Spawn above or below the map
		if (rand() % 2 == 0)
		{
			spawn_pos.setY(-SPAWN_Y_OFFSET);
		}
		else
		{
			spawn_pos.setY(WM.getBoundary().getVertical() + SPAWN_Y_OFFSET);
		}
		spawn_pos.setX((float) (rand() % (int)WM.getBoundary().getHorizontal()));
	}

	// Spawn the selected enemy
	switch (e_type)
	{
	case E_BASIC:
	{
		// TODO spawn enemy here
		enemySpawnCount++;
		break;
	}
	case E_TOUGH:
	{
		// TODO spawn enemy here
		enemySpawnCount++;
		break;
	}
	case E_FAST:
	{
		// TODO spawn enemy here
		enemySpawnCount++;
		break;
	}
	case E_TRICKY:
	{
		// TODO spawn enemy here
		enemySpawnCount++;
		break;
	}
	case E_SPIRAL:
	{
		// TODO spawn enem here
		enemySpawnCount++;
		break;
	}
	case E_SWARM:
	{
		for (int i = 0; i < 4; i++)
		{
			// TODO spawn enemy here, passing in i as radial offset
			enemySpawnCount++;
		}
		break;
	}
	default:
		// If you got here something went bad. Don't proceed.
		return;
	}

	// TODO - REMOVE THIS AFTER IMPLEMENTING PROPER SPAWNING ABOVE
	new Enemy(spawn_pos);
}


// Spawn an ammo drop at the location
void WaveController::spawnAmmo(df::Vector position)
{
	player_weapon ammo_type = W_MISSILE;
	int ammo_value = 0;
	
	// randomly choose ammo type
	switch (rand() % 5)
	{
	// No case for W_MISSILE
	case 0: 
		ammo_type = W_LASER;
		ammo_value = 10;
		break;
	case 1:
		ammo_type = W_SPREAD;
		ammo_value = 15;
		break;
	case 2:
		ammo_type = W_BOMB;
		ammo_value = 10;
		break;
	case 3:
		ammo_type = W_PLASMA;
		ammo_value = 5;
		break;
	case 4:
		ammo_type = W_RAPID;
		ammo_value = 25;
		break;
	}
	
	new Ammo(position, ammo_type, ammo_value);
}


// Generate a random float from 0 to 1
float WaveController::randomPercent()
{
	return (float) (rand() % RAND_DICE_SIZE) / RAND_DICE_SIZE;
}


// Handle events
int WaveController::eventHandler(const Event* p_e) {

	// Step event handler
	if (p_e->getType() == STEP_EVENT) {
		step();
		return 1;
	}
	// Enemy Death event handler
	if (p_e->getType() == ENEMY_DEATH_EVENT) {
		const EventEnemyDeath* p_enemydeath_event = dynamic_cast <const EventEnemyDeath*> (p_e);
		enemyDead(p_enemydeath_event);
		return 1;
	}
	// Player Death event handler
	// Stop spawning waves if disabled
	if (p_e->getType() == PLAYER_DEATH_EVENT) {
		disabled = true;
		return 1;
	}

	return 0;
}


// Get the current wave number
int WaveController::getWave()
{
	return waveNumber;
}