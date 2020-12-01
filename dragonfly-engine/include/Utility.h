// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

#pragma once
#include <time.h>
#include "Vector.h"
#include "Box.h"
#include "Object.h"

namespace df {
		
	// Returns a pointer to a struct of the current time
	struct tm* getLocalTime();

	// Returns the current time as a string
	char* getTimeString();

	// Return true if two positions intersect, otherwise false
	bool positionsIntersect(Vector p1, Vector p2);

	// Returns the boolean as a string
	// NOTE: can only be used once per function call
	char* boolToString(bool value);

	// Convert int to a string, returning string
	std::string toString(int i);

	// Convert relative bounding Box for Object to absolute world Box
	Box getWorldBox(const Object* p_o);
	Box getWorldBox(const Object* p_o, Vector where);

	// Convert world position to view position
	Vector worldToView(Vector world_pos);

	// Convert view position to world position
	Vector viewToWorld(Vector world_pos);

	// Returns whether or not two boxes interect
	bool boxIntersectsBox(Box A, Box B);

	// Return true if Box contains Position
	bool boxContainsPosition(Box b, Vector p);
		
	// Return true if Box 1 completely contains Box 2
	bool boxContainsBox(Box b1, Box b2);

	// Return distance between any two positions
	float distance(Vector p1, Vector p2);
}