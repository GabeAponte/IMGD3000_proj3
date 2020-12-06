// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

//
// Velocity.h
// Conversion utility methods between real velocity (based on pixels)
// and Dragonfly velocity (based on characters)
//

#pragma once

#include <Vector.h>

#define PI 3.14159

// Calculate the scale factor based on the screen width and height
float scaleFactor();

// Convert a vector from Dragonfly velocity to real velocity
df::Vector convertToReal(df::Vector dragonfly_velocity);

// Convert a vector from real velocity to dragonfly velocity
df::Vector convertToDragonfly(df::Vector real_velocity);

// Produces a vector in the indicated direction with the indicated magnitude
// Y-component is automatically adjusted to accommodate the screen distortion
df::Vector makeRealVector(df::Vector direction, float magnitude);

// Rotates a vector counterclockwise by the indicated amount in degrees
df::Vector rotateVector(df::Vector base_vector, float degrees);