#pragma once
#include <string>
#include "Event.h"
#include "Vector.h"
#include "Box.h"
#include "Animation.h"

namespace df {

	enum Solidness {
		HARD,		// Object causes collisions and impedes
		SOFT,		// Object causes collisions, but doesn’t impede
		TANGIBLE,	// Object recieves collisions, but doesn't detect its own
		SPECTRAL,	// Object doesn’t cause collisions
	};

	class Object {

	private:
		int m_id;				// Unique game engine defined identifier
		std::string m_type;		// Game programmer defined type
		Vector m_position;		// Position in game world
		Vector m_direction = Vector(0,0); // Direction of movement
		float m_speed = 0;		// Magnitude of movement
		int m_altitude = 0;		// Elevation for drawing
		Solidness m_solidness = HARD; // Solidness of the object
		bool m_always_collide = false; // Whether the object is set to always check for collisions
		Box m_box; // Box for sprite boundary & collisions
		Animation m_animation;	// Animation linked to this object

	public:
		// Construct object
		// Set default parameters and add to world (WorldManager)
		Object();

		// Destroy object
		// Remove object from the game world (WorldManager)
		virtual ~Object();

		// PROPERTIES

		// Set/get object ID
		void setId(int new_id);
		int getId() const;

		// Set/get object type identifier
		void setType(std::string new_type);
		std::string getType() const;

		// Set/get object solidness, with checks for consistency
		// Return 0 if ok, else −1
		int setSolidness(Solidness new_solid);
		Solidness getSolidness() const;
		// True if HARD, SOFT, or TANGIBLE, otherwise false
		bool isSolid() const;
		// True only if HARD or SOFT
		bool detectsCollisions() const;

		// Set/get whether object always checks for collisions
		// Return 0 if ok, else −1
		int setAlwaysCollide(bool always_collide);
		bool getAlwaysCollide() const;

		// LOCATION AND PHYSICS

		// Set/get object position
		void setPosition(Vector new_pos);
		Vector getPosition() const;

		// Set/get object direction
		void setDirection(Vector new_dir);
		Vector getDirection() const;

		// Set/get object speed
		void setSpeed(float new_speed);
		float getSpeed() const;

		// Set/get object veocity
		void setVelocity(Vector new_vel);
		Vector getVelocity() const;

		// Set/get object elevation
		int setAltitude(int new_alt);
		int getAltitude() const;

		// Predict Object position based on speed and direction
		// Return predicted position
		Vector predictPosition();

		// Set/Get Object's bounding box
		void setBox(Box new_box);
		Box getBox() const;


		// EVENTS

		// Handle event (default is to ignore everything)
		// Return 0 if ignored, else 1 if handled
		virtual int eventHandler(const Event* p_e);
		
		// DRAWING AND ANIMATION

		// Set Sprite for this Object to animate
		// Return 0 if ok, else −1.
		int setSprite(std::string sprite_label);
		
		// Set Animation for this Object to new one
		// Set bounding box to size of associated Sprite
		void setAnimation(Animation new_animation);
		
		// Get Animation for this Object
		Animation getAnimation() const;

		// Toggle whether the Object animates
		void setAnimationState(bool enabled);

		// Set the animation frame index used by the Object
		void setAnimationIndex(int new_index);

		// Draw the object
		virtual int draw();
	};
}