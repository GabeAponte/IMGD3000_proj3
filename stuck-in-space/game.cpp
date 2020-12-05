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

// Function prototypes.
void loadResources(void);
void populateWorld(void);

using namespace df;
 
int main(int argc, char *argv[]) {
    // Set window dimensions and title BEFORE STARTUP
    DM.setWindowTitle("STUCK IN SPACE");
    DM.setHorizontal(120);
    DM.setVertical(36);
    DM.setHorizontalPixels(1024);
    DM.setVerticalPixels(768);

    // Start up game manager.
    if (GM.startUp())  {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 0;
    }

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
  RM.loadSprite("../sprites/saucer-spr.txt", "saucer");
  RM.loadSprite("../sprites/bullet-spr.txt", "bullet");
  RM.loadSprite("../sprites/explosion-spr.txt", "explosion");
  RM.loadSprite("../sprites/gamestart-spr.txt", "gamestart");
  RM.loadSprite("../sprites/gameover-spr.txt", "gameover");
  RM.loadSprite("../sprites/player-spr.txt", "player");
  RM.loadSprite("../sprites/ammo-spr.txt", "ammo");
  RM.loadSound("../sounds/fire.wav", "fire");
  RM.loadSound("../sounds/explode.wav", "explode");
  RM.loadSound("../sounds/nuke.wav", "nuke");
  RM.loadSound("../sounds/game-over.wav", "game over");
  RM.loadMusic("../sounds/start-music.wav", "start music");
}
 
// Populate world with some objects.
void populateWorld(void) {

  // Spawn some Stars.
  for (int i=0; i<16; i++) 
    new Star;
 
  // Create GameStart object.
  new GameStart();
}
