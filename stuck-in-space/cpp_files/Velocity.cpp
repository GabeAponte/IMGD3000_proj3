// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// Velocity.cpp
// Conversion utility methods between real velocity (based on pixels)
// and Dragonfly velocity (based on characters)
//

#include <iostream>

#include <DisplayManager.h>
#include "../header_files/Velocity.h"

using namespace df;

// Calculate the scale factor based on the screen width and height
// Multiply a Dragonfly y velocity by this to get a uniform screen velocity
// (ex. a dragonfly velocity of (1,0) will appear the same speed as one of (0,scaleFactor) )
float scaleFactor()
{
	float x_scale = DM.getHorizontalPixels() / DM.getHorizontal();
	float y_scale = DM.getVerticalPixels() / DM.getVertical();
	return x_scale / y_scale;
}


// Convert a vector from Dragonfly velocity to real velocity
df::Vector convertToReal(df::Vector dragonfly_velocity)
{
	Vector real_velocity = dragonfly_velocity;
	real_velocity.setY(dragonfly_velocity.getY() * scaleFactor());
	return real_velocity;
}


// Convert a vector from real velocity to dragonfly velocity
df::Vector convertToDragonfly(df::Vector real_velocity)
{
	Vector dragonfly_velocity = real_velocity;
	dragonfly_velocity.setY(real_velocity.getY() / scaleFactor());
	return dragonfly_velocity;
}