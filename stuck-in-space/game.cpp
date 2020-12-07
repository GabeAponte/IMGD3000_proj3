// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// Gabriel Aponte
// gaaponte@wpi.edu

//
// game.cpp
//

#include "GameManager.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "ResourceManager.h"
#include "header_files/GameStart.h"
#include "header_files/Star.h"
#include "header_files/ScoresIOStreamer.h"
#include <WorldManager.h>
#include "header_files/ScreenShaker.h"

// Function prototypes.
void loadResources(void);
void populateWorld(void);

using namespace df;

int main(int argc, char* argv[]) {

	// Set window dimensions and title BEFORE STARTUP
	DM.setWindowTitle("STUCK IN SPACE");
	DM.setHorizontal(120);
	DM.setVertical(36);
	DM.setHorizontalPixels(1024);
	DM.setVerticalPixels(768);
	
	// Start up game manager.
	if (GM.startUp()) {
		LM.writeLog("Error starting game manager!");
		GM.shutDown();
		return 0;
	}

	// Set boundary and view for screen shake functionality
	WM.setBoundary(Box(Vector(-2, -2), 124, 40));
	WM.setView(Box(Vector(0, 0), 120, 36));
	WM.setViewFollowing(new ScreenShaker());

	// Set flush of logfile during development (when done, make false).
	LM.setFlush(true);

	// Load game resources.
	loadResources();

	// Populate game world with some objects.
	populateWorld();

	// Run game (this blocks until game loop is over).
	GM.run();

	// Shut everything down.
	GM.shutDown();
}

// Load resources (sprites, sound effects, music).
void loadResources(void) {

	// Log level for what statements to print
	LM.setLogLevel(3);

	// Load sprites
	RM.loadSprite("../sprites/spr_player.txt", "player");
	RM.loadSprite("../sprites/spr_player_hit.txt", "player-hit");
	RM.loadSprite("../sprites/spr_player_no_shield.txt", "player-no-shield");
	RM.loadSprite("../sprites/spr_ammo.txt", "ammo");
	RM.loadSprite("../sprites/spr_star0.txt", "star0");
	RM.loadSprite("../sprites/spr_star1.txt", "star1");
	RM.loadSprite("../sprites/spr_star2.txt", "star2");
	RM.loadSprite("../sprites/spr_w_bullet.txt", "w_bullet");
	RM.loadSprite("../sprites/spr_w_bomb.txt", "w_bomb");
	RM.loadSprite("../sprites/spr_w_spread.txt", "w_spread");
	RM.loadSprite("../sprites/spr_w_plasma.txt", "w_plasma");
	RM.loadSprite("../sprites/spr_w_rapid.txt", "w_rapid");
	RM.loadSprite("../sprites/spr_enemy_basic.txt", "basic-enemy");
	RM.loadSprite("../sprites/spr_enemy_fast.txt", "fast-enemy");
	RM.loadSprite("../sprites/spr_enemy_swarm.txt", "swarm-enemy");
	RM.loadSprite("../sprites/spr_enemy_tough.txt", "tough-enemy");
	RM.loadSprite("../sprites/spr_enemy_tough_hit.txt", "tough-enemy-hit");
	RM.loadSprite("../sprites/spr_enemy_tricky.txt", "tricky-enemy");
	RM.loadSprite("../sprites/spr_enemy_shooter.txt", "shooter-enemy");
	RM.loadSprite("../sprites/spr_enemy_spiral.txt", "spiral-enemy");
	RM.loadSprite("../sprites/spr_enemybullet.txt", "enemy-bullet");
	RM.loadSprite("../sprites/spr_explosion.txt", "explosion");
	RM.loadSprite("../sprites/spr_bombexplosion.txt", "bomb-explosion");
	RM.loadSprite("../sprites/spr_gamestart.txt", "gamestart");
	RM.loadSprite("../sprites/spr_gameover.txt", "gameover");

	// Load sounds
	RM.loadSound("../sounds/fire.wav", "fire");
	RM.loadSound("../sounds/explode.wav", "explode");
	RM.loadSound("../sounds/nuke.wav", "nuke");
	RM.loadSound("../sounds/game-over.wav", "game over");
	RM.loadSound("../sounds/laser.wav", "laser");
	RM.loadSound("../sounds/spread.wav", "spread");
	RM.loadSound("../sounds/missile.wav", "missile");
	RM.loadSound("../sounds/plasma.wav", "plasma");
	RM.loadSound("../sounds/bomb.wav", "bomb");
	RM.loadSound("../sounds/bomb-explosion.wav", "bomb-explosion");
	RM.loadSound("../sounds/shield-overload.wav", "shield-overload");
	RM.loadSound("../sounds/shield-hit.wav", "shield-hit");
	RM.loadSound("../sounds/ammo-pickup.wav", "ammo-pickup");

	// Load music
	RM.loadMusic("../sounds/start-music.wav", "start music");
}

// Populate world with some objects.
void populateWorld(void) {

	// Spawn some Stars.
	for (int i = 0; i < 32; i++)
		new Star;

	// Create GameStart object.
	new GameStart();
}
