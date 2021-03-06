// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// WaveController.cpp
// Handles all logic for spawning enemies and advancing the wave
//

#include <iostream>
#include <Vector.h>
#include <WorldManager.h>
#include <DisplayManager.h>
#include "../header_files/EventPlayerDeath.h"
#include "../header_files/Enemy.h"
#include "../header_files/Ammo.h"
#include "../header_files/WaveController.h"

using namespace df;

WaveController::WaveController() {

	// Set type
	setType("WaveController");

	// Set to SPECTRAL
	setSolidness(SPECTRAL);

	// Set to draw above things
	setAltitude(MAX_ALTITUDE);

	// Initialize vars
	waveNumber = 0;
	difficulty = START_DIFFICULTY;

	// Set up enemy options
	// enemy_data is (enemy type, minimum difficulty, difficulty cost)
	enemyOptions.push_back(enemy_data{ E_BASIC, START_DIFFICULTY, 1 }); // basic enemy must require difficulty 0
	enemyOptions.push_back(enemy_data{ E_TOUGH, 10, 2 });
	enemyOptions.push_back(enemy_data{ E_FAST, 15, 2 });
	enemyOptions.push_back(enemy_data{ E_TRICKY, 20, 3 });
	enemyOptions.push_back(enemy_data{ E_SWARM, 30, 9 });
	enemyOptions.push_back(enemy_data{ E_SHOOTER, 40, 5 });

	// Set up ammo values
	ammoValue[W_LASER] =	8;
	ammoValue[W_SPREAD] =	10;
	ammoValue[W_BOMB] =		8;
	ammoValue[W_PLASMA] =	4;
	ammoValue[W_RAPID] =	15;

	// Set up ammo "neglect" counters
	ammoNeglect[W_LASER] =	0;
	ammoNeglect[W_SPREAD] = 0;
	ammoNeglect[W_BOMB] =	0;
	ammoNeglect[W_PLASMA] = 0;
	ammoNeglect[W_RAPID] =	0;

	// Initialize vars
	enemySpawnTotal = 0;
	enemySpawnCount = 0;
	enemyKillCount = 0;
	ammoSpawnCount = 0;
	waveComplete = true;
	waveBeginWait = WAVE_BEGIN_DELAY;
	disabled = false; // start enabled
	displayWaveEnd = false;
	displayWaveStart = false;
	messageCooldown = 45;
	setAltitude(4);

	// Center so UI elements won't go off screen
	setPosition(WM.getBoundary().getCorner() + Vector(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2));
}

WaveController::~WaveController()
{
	enemyOptions.clear();
	enemySpawnList.clear();
}

// Handle step event
void WaveController::step() 
{
	// Early exit if disabled
	if (disabled)
		return;

	// Detect if wave complete
	if (waveComplete) {
		waveBeginWait--;

		if (waveBeginWait <= 0) {

			// Begin next wave
			beginWave();
		}
	}

	// Otherwise, handle wave updates
	else {
		if (enemySpawnWait > 0) {
			enemySpawnWait--;
		}
		else {
			spawnEnemy();
		}
	}
}

// Handle enemy death event
void WaveController::enemyDead(const EventEnemyDeath* p_enemydeath_event)
{
	// Record enemy kill
	enemyKillCount++;

	// End wave if all enemies spawned and killed
	if (enemyKillCount >= enemySpawnCount && enemySpawnList.empty()) {
		waveComplete = true;
		waveBeginWait = WAVE_BEGIN_DELAY;
		
		// Toggle wave ended message
		displayWaveEnd = true;
	}

	// Spawn ammo refill at enemy location if player killed enemy
	// This happens either randomly or by force if the quota amount of ammo hasn't dropped
	bool did_player_kill = p_enemydeath_event->getDidPlayerKill();
	bool rng_ammo_spawn = (randomPercent() <= AMMO_SPAWN_CHANCE);
	bool forced_ammo_spawn = (ammoSpawnCount < ammoSpawnQuota) && (enemySpawnTotal - enemyKillCount < ammoSpawnQuota);
	if (did_player_kill && (rng_ammo_spawn || forced_ammo_spawn)) {
		spawnAmmo(p_enemydeath_event->getPosition());
	}
}

// Generate a new wave
void WaveController::beginWave()
{
	// Reset counts
	enemySpawnTotal = 0;
	enemySpawnCount = 0;
	enemyKillCount = 0;
	enemySpawnList.clear();
	ammoSpawnCount = 0;

	// Advance wave
	waveNumber++;

	// Toggle wave started message
	displayWaveStart = true;

	//std::cout << "STARTING WAVE " << waveNumber << "\n";
	waveComplete = false;

	// Advance difficulty
	difficulty += DIFFICULTY_INCREASE;

	// Calculate ammo spawn quota
	// At least one, increasing as difficulty rises
	ammoSpawnQuota = std::max(1,(int) sqrt(difficulty*AMMO_QUOTA_FACTOR));

	// Generate wave contents based on difficulty budget
	int difficulty_cost = 0;
	while (difficulty_cost < difficulty) {

		for (std::vector<enemy_data>::reverse_iterator it = enemyOptions.rbegin(); it != enemyOptions.rend(); it++) {

			// Ensure that enemy can be spawned
			// (is available at current difficulty and is within budget)
			if (it->minDifficulty <= difficulty && it->difficultyCost <= difficulty - difficulty_cost) {

				// Chance to spawn selected enemy. Otherwise, if no options found: default to basic enemy
				if (randomPercent() < 0.5 || it == enemyOptions.rend() - 1) {

					// Queue enemy for spawning, and add cost to accumulated difficulty cost
					enemySpawnList.push_back(it->enemyType);
					difficulty_cost += it->difficultyCost;
					if (it->enemyType == E_SWARM)
					{
						enemySpawnTotal += 5;
					}
					else
					{
						enemySpawnTotal++;
					}
					//std::cout << "~ Queuing enemy of type " << (int)it->enemyType << " (Cost: " << difficulty_cost << "/" << difficulty << ")\n";
					break;
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
	if (randomPercent() <= SIDE_SPAWN_CHANCE) {

		// Spawn to the side of the map
		if (rand() % 2 == 0) {
			spawn_pos.setX(-SPAWN_X_OFFSET);
		}
		else {
			spawn_pos.setX(WM.getBoundary().getHorizontal() + SPAWN_X_OFFSET);
		}
		spawn_pos.setY((float)(rand() % (int)WM.getBoundary().getVertical()));
	}
	else {

		// Spawn above or below the map
		if (rand() % 2 == 0) {
			spawn_pos.setY(-SPAWN_Y_OFFSET);
		}
		else {
			spawn_pos.setY(WM.getBoundary().getVertical() + SPAWN_Y_OFFSET);
		}

		spawn_pos.setX((float)(rand() % (int)WM.getBoundary().getHorizontal()));
	}
	spawn_pos = spawn_pos + WM.getBoundary().getCorner();

	// Spawn the selected enemy
	switch (e_type) {

	case E_BASIC:
	{
		new Enemy(spawn_pos, E_BASIC);
		enemySpawnCount++;
		break;
	}
	case E_TOUGH:
	{
		new Enemy(spawn_pos, E_TOUGH);
		enemySpawnCount++;
		break;
	}
	case E_FAST:
	{
		new Enemy(spawn_pos, E_FAST);
		enemySpawnCount++;
		break;
	}
	case E_TRICKY:
	{
		new Enemy(spawn_pos, E_TRICKY);
		enemySpawnCount++;
		break;
	}
	case E_SWARM:
	{
		new Enemy(spawn_pos, E_SWARM);
		new Enemy(spawn_pos + Vector(0, +4), E_SWARM);
		new Enemy(spawn_pos + Vector(0, -4), E_SWARM);
		new Enemy(spawn_pos + Vector(+9, 0), E_SWARM);
		new Enemy(spawn_pos + Vector(-9, 0), E_SWARM);
		enemySpawnCount += 5;
		break;
	}

	case E_SHOOTER:
	{
		new Enemy(spawn_pos, E_SHOOTER);
		enemySpawnCount++;
		break;
	}
	default:
		// If you got here something went bad. Don't proceed.
		return;
	}
}

// Spawn an ammo drop at the location
void WaveController::spawnAmmo(df::Vector position)
{
	// Default to random weapon type
	player_weapon ammo_type = ammo_type = (player_weapon)(1 + rand() % 5);

	// Override with a "neglected" ammo type if any present
	for (std::map<player_weapon, int>::iterator it = ammoNeglect.begin(); it != ammoNeglect.end(); it++)
	{
		if (it->second >= AMMO_NEGLECT_LIMIT)
		{
			ammo_type = it->first;
		}
	}

	// Update "neglect" counters
	for (std::map<player_weapon, int>::iterator it = ammoNeglect.begin(); it != ammoNeglect.end(); it++)
	{
		if (it->first == ammo_type)
		{
			// reset "neglect" counter if ammo chosen
			it->second = 0;
		}
		else
		{
			// increment "neglect" counter if ammo not dropped
			it->second++;
		}
	}
	
	// Spawn ammo
	new Ammo(position, ammo_type, ammoValue[ammo_type]);
	ammoSpawnCount++;
}

// Generate a random float from 0 to 1
float WaveController::randomPercent()
{
	return (float)(rand() % RAND_DICE_SIZE) / RAND_DICE_SIZE;
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
		const EventEnemyDeath* p_enemydeath_event = dynamic_cast<const EventEnemyDeath*> (p_e);
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
int WaveController::getWaveNumber()
{
	return waveNumber;
}

// Draws messages when waves start and end
int WaveController::draw() 
{
	float mid_x = WM.getView().getCorner().getX() + WM.getView().getHorizontal() / 2;
	float top_y = WM.getView().getCorner().getY();
	float mid_y = top_y + WM.getView().getVertical() / 2;

	// Display wave count over player HUD
	DM.drawString(Vector(mid_x, top_y+2), "WAVE " + std::to_string(std::max(1,waveNumber)), CENTER_JUSTIFIED, Color::GREEN);

	// Display wave start message if it is toggled
	if (displayWaveStart) {
		if (messageCooldown > 0) {
			DM.drawString(Vector(mid_x, mid_y - 10), "Wave " + std::to_string(waveNumber) + " starting...", CENTER_JUSTIFIED, Color::GREEN);
			messageCooldown--;
		}

		// Reset wave start display
		else {
			displayWaveStart = false;
			messageCooldown = 45;
		}

		return 1;
	}

	// Display wave end message if it is toggled
	if (displayWaveEnd) {
		if (messageCooldown > 0) {
			DM.drawString(Vector(mid_x, mid_y - 10), "Wave " + std::to_string(waveNumber) + " cleared.", CENTER_JUSTIFIED, Color::GREEN);
			messageCooldown--;
		}

		// Reset wave end display
		else {
			displayWaveEnd = false;
			messageCooldown = 45;
		}

		return 1;
	}

	return 0;
}