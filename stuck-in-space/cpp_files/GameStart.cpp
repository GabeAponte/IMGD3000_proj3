//
// GameStart.cpp
//

// Engine includes.
#include "Color.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "../header_files/GameStart.h"
#include "../header_files/Hero.h"
#include "Music.h"
#include "../header_files/Points.h"
#include "../header_files/Enemy.h"
#include "..\header_files\Leaderboard.h"

using namespace df;

GameStart::GameStart() {

  WM.deleteObjectsOfType("Saucer");

  setType("GameStart");

  // Link to "message" sprite.
  setSprite("gamestart");

  // Put in center of screen.
  setLocation(df::CENTER_CENTER);
  
  // Play start music.
  p_music = RM.getMusic("start music");
  playMusic();

  
}

// Play start music.
void GameStart::playMusic() {
  p_music->play();
}

// Handle event.
// Return 0 if ignored, else 1.
int GameStart::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::KEYBOARD_EVENT) {
    df::EventKeyboard *p_keyboard_event = (df::EventKeyboard *) p_e;
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
    switch (p_keyboard_event->getKey()) {
    case df::Keyboard::P: 			// play
      start();
      break;
    case df::Keyboard::Q:			// quit
      GM.setGameOver();
      break;
    case df::Keyboard::L:			// see leaderboards
        new Leaderboard();
        //df::WM.removeObject(this);
        df::WM.markForDelete(this);
        break;
    default:
      break;
    }
    return 1;
  }

  // If get here, have ignored this event.
  return 0;
}

void GameStart::start() {

  // Create hero.
  new Hero;

  // Spawn some saucers to shoot.
  for (int i = 0; i < 20; i++) {
      df::Vector temp_pos;

      // Get world boundaries.
      int world_horiz = (int)WM.getBoundary().getHorizontal();
      int world_vert = (int)WM.getBoundary().getVertical();

      // x is off right side of window.
      temp_pos.setX((float)(world_horiz + rand() % world_horiz + 3));

      // y is in vertical range.
      temp_pos.setY(rand() % (world_vert - 4) + 4.0f);

      // If collision, move right slightly until empty space.
      df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
      while (!collision_list.isEmpty()) {
          temp_pos.setX(temp_pos.getX() + 1);
          collision_list = WM.getCollisions(this, temp_pos);
      }
      new Enemy(temp_pos);
  }
   

  // Setup heads-up display.
  new Points;		                     // Points display.

  df::ViewObject* p_fuel = new df::ViewObject; // Shield display
  p_fuel->setLocation(df::TOP_LEFT);
  p_fuel->setViewString("Shield Integrity %");
  p_fuel->setValue(100);
  p_fuel->setColor(df::YELLOW);

  // Pause start music.
  p_music->pause();

  // When game starts, destroy this object.
  WM.markForDelete(this);
}
// Override default draw so as not to display "value".
int GameStart::draw() {
  df::Object::draw();
  return 0;
}
