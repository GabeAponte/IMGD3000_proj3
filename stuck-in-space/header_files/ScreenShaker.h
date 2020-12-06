// Gabriel Aponte
// gaaponte@wpi.edu

//
// ScreenShaker.h
// Invisible object that will shake the screen
//

#pragma once
#include "Object.h"

class ScreenShaker : public df::Object
{
public:
	ScreenShaker();

private:
	int shakeIndex;
	bool canShake;
	int eventHandler(const df::Event* p_e);
};

