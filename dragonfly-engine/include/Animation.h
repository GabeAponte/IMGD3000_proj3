#pragma once
#include <string>
#include "Sprite.h"
#include "Box.h"

namespace df {

	class Animation {

	private:
		Sprite* m_p_sprite;		// Sprite associated with Animation
		std::string m_name;		// Sprite name in ResourceManager
		int m_index;			// Current index frame for Sprite
		int m_slowdown_count;	// Slowdown counter

	public:
		// Animation constructor
		Animation();

		// Set new associated sprite and set sprite index to 0 (first frame)
		// Note, Sprite is managed by ResourceManager
		void setSprite(Sprite* p_new_sprite);

		// Return pointer to associated Sprite
		Sprite* getSprite() const;

		// Set/Get Sprite name (in ResourceManager)
		void setName(std::string new_name);
		std::string getName() const;
	
		// Set/Get index of current Sprite frame to be displayed
		void setIndex(int new_index);
		int getIndex() const;
		
		// Set/Get animation slowdown count (−1 means stop animation)
		void setSlowdownCount(int new_slowdown_count);
		int getSlowdownCount() const;
		
		// Returns the collision box for the sprite, automatically centered
		Box getBox();

		// Draw single frame centered at position (x, y)
		// Drawing accounts for slowdown, and advances Sprite frame
		// Return 0 if ok, else −1.
		int draw(Vector position);
	};
}