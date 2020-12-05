// Gabriel Aponte
// gaaponte@wpi.edu

//
// ScreenShaker.h
// Invisible object that will shake the screen
//

#pragma once
#include "Object.h"

// Shorthand to access the ScreenShaker singleton implementation
#define SCREENSHAKER ScreenShaker::getInstance()

class ScreenShaker : public df::Object
{
public:
	// Gets the single instance of this class
	static ScreenShaker& getInstance();

private:
	ScreenShaker();                         // Private since a singleton.
	ScreenShaker(ScreenShaker const&);      // Don't allow copy.
	void operator=(ScreenShaker const&);    // Don't allow assignment.
};

