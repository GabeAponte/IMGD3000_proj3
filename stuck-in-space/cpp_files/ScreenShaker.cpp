// Gabriel Aponte
// gaaponte@wpi.edu

//
// ScreenShaker.cpp
// Invisible object that will shake the screen
//

#include <WorldManager.h>
#include <EventStep.h>
#include "../header_files/EventShake.h"
#include "../header_files/ScreenShaker.h"

using namespace df;

ScreenShaker::ScreenShaker()
{
	// Invisible and set at center of screen
	setSolidness(SPECTRAL);
	setPosition(Vector(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2));
}

// Handles events
int ScreenShaker::eventHandler(const df::Event* p_e)
{
	// Step event handler to shake the screen
	if (p_e->getType() == STEP_EVENT) {
		if (canShake) {
			if (shakeIndex == 0) {
				setVelocity(Vector(1, 0));
				shakeIndex++;
			}
			else if (shakeIndex == 1) {
				setVelocity(Vector(-1, -1));
				shakeIndex++;
			}
			else if (shakeIndex == 2) {
				setVelocity(Vector(-1, 0));
				shakeIndex++;
			}
			else if (shakeIndex == 3) {
				setVelocity(Vector(1, 1));
				shakeIndex++;
			}
			else if (shakeIndex == 4) {
				setVelocity(Vector());
				setPosition(Vector(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2));
				WM.setViewFollowing(this);
				shakeIndex = 0;
				canShake = false;
			}
		}
		return 1;
	}

	// Shake event handler to toggle shake
	if (p_e->getType() == SHAKE_EVENT) {
		canShake = true;
		shakeIndex = 0;
		return 1;
	}

	return 0;
}
