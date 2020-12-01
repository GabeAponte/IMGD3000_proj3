#pragma once
#include "Vector.h"

namespace df {

	class Box {

	private:
		Vector m_corner;	// Upper left corner of box
		float m_horizontal; // Horizontal dimension
		float m_vertical;	// Vertical dimension

	public:
		// Create box with (0, 0) for the corner, and 0 for horizontal and vertical
		Box();
		
		// Create box with an upper−left corner, horizontal and vertical sizes
		Box(Vector init_corner, float init_horizontal, float init_vertical);
		
		// Create a box for a 1-character object
		static Box charBox();

		// Set/Get upper left corner of box
		void setCorner(Vector new_corner);
		Vector getCorner() const;
		
		// Set/Get horizontal size of box
		void setHorizontal(float new_horizontal);
		float getHorizontal() const;
		
		// Set/Get vertical size of box
		void setVertical(float new_vertical);
		float getVertical() const;
	};
}