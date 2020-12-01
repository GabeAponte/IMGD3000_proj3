//
// Points.cpp
//

// Engine includes
#include "DisplayManager.h"
#include "Event.h"
#include "EventStep.h"
#include "LogManager.h"

// Game includes.
#include "../header_files/Points.h"

Points::Points() {
  setLocation(df::TOP_RIGHT);
  setViewString(POINTS_STRING);
  setColor(df::YELLOW);
}

// Handle event.
// Return 0 if ignored, else 1.
int Points::eventHandler(const df::Event *p_e) {

  // Parent handles event if score update.
  if (df::ViewObject::eventHandler(p_e)) {
    return 1;
  }

  // If get here, have ignored this event.
  return 0;
}
