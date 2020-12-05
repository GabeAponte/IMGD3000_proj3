// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// Velocity.cpp
// Conversion utility methods between real velocity (based on pixels)
// and Dragonfly velocity (based on characters)
//

#include <iostream>

#include <LogManager.h>
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


// Produces a vector in the indicated direction with the indicated magnitude
// Y-component is automatically adjusted to accommodate the screen distortion
df::Vector makeRealVector(df::Vector direction, float magnitude)
{
	df::Vector v = convertToDragonfly(direction); // adjust direction for screen coordinates
	v.normalize();				// convert to direction unit vector
	v.scale(magnitude);			// set magnitude
	v = convertToReal(v);	// adjust velocity for screen coordinates
	return v;
}


// Rotates a vector counterclockwise by the indicated amount in degrees
df::Vector rotateVector(df::Vector base_vector, float degrees)
{
	// screen for 0 vector
	if (base_vector.getX() == 0 && base_vector.getY() == 0)
	{
		LM.writeLog(1, "ERROR: Tried to get direction of 0-vector!");
		return base_vector;
	}
	//double direction = atan2(base_vector.getY(), base_vector.getX()) + degrees*PI/180;
	//float magnitude = base_vector.getMagnitude();
	//df::Vector rv = Vector(magnitude * cos(direction), magnitude * sin(direction));
	//std::cout << "Dir: " << direction << "\n";
	return base_vector;
	//return rv;
}