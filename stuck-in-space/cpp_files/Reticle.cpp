//
// Reticle.cpp
//

#include "DisplayManager.h"
#include "EventMouse.h"
#include "WorldManager.h"
#include "../header_files/Reticle.h"

using namespace df;

Reticle::Reticle() {
  setType("Reticle");
  setSolidness(df::SPECTRAL);
  setAltitude(MAX_ALTITUDE); // Make Reticle in the foreground.

  // Start reticle in center of window.
  df::Vector p(WM.getBoundary().getHorizontal()/2,
	       WM.getBoundary().getVertical()/2);
  setPosition(p);
}

// Handle event.
// Return 0 if ignored, else 1.
int Reticle::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::MSE_EVENT) {
    const df::EventMouse *p_mouse_event = dynamic_cast <const df::EventMouse *> (p_e);
    if (p_mouse_event->getMouseAction() == df::MOVED) {
      // Change location to new mouse position.
      setPosition(p_mouse_event->getMousePosition());
      return 1;
    }
  }

  // If get here, have ignored this event.
  return 0;
}

// Draw reticle on window.
int Reticle::draw() {
  DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);
  return 0;
}
