//
// GameOver.cpp
//

// Engine includes.
#include "EventStep.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "../header_files/GameOver.h"
#include "../header_files/GameStart.h"
#include "../header_files/WaveController.h"
#include "../header_files/InputPlayerName.h"

using namespace df;

GameOver::GameOver() {

  setType("GameOver");

  // Link to "message" sprite.
  if (setSprite("gameover") == 0)
    time_to_live = getAnimation().getSprite()->getFrameCount() * 15;
  else
    time_to_live = 0;

  // Put in center of window.
  setLocation(df::CENTER_CENTER);
  
  // Play "game over" sound.
  df::Sound *p_sound = RM.getSound("game over");
  p_sound->play();
}

// When done, game over so shut down.
GameOver::~GameOver() {
    // Clear view objects
    WM.deleteObjectsOfType("ViewObject");
    
    // Get the wave controller
    ObjectList ol = WM.objectsOfType("WaveController");
    ObjectListIterator oli(&ol);
    WaveController* p_wc = dynamic_cast <WaveController*> (oli.currentObject());
    
    // Display results and let player input highscores
    new InputPlayerName(p_wc->getWave()-1);
    
    // Delete wave controller
    WM.markForDelete(p_wc);
}

// Handle event.
// Return 0 if ignored, else 1.
int GameOver::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::STEP_EVENT) {
    step();
    return 1;
  }

  // If get here, have ignored this event.
  return 0;
}

// Count down to end of message.
void GameOver::step() {
  time_to_live--;
  if (time_to_live <= 0) { 
    WM.markForDelete(this);
  }
}

// Override default draw so as not to display "value".
int GameOver::draw() {
  df::Object::draw();
  return 0;
}
