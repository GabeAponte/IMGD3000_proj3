#pragma once
#include <string>
#include "Vector.h"
#include "Color.h"

namespace df {

	class Frame {

	private:
		int m_width; // Width of frame
		int m_height; // Height of frame
		std::string m_frame_str; // All frame characters stored as string

	public:
		// Create empty frame
		Frame();

		// Create frame of indicated width and height with string
		Frame(int new_width, int new_height, std::string frame_str);

		// Set/Get width of frame
		void setWidth(int new_width);
		int getWidth() const;

		// Set/Get height of frame
		void setHeight(int new_height);
		int getHeight() const;

		// Set/Get frame characters (stored as string) 
		void setString(std::string new_frame_str);
		std::string getString() const;

		// Draw self, centered at position (x, y) with color
		// Return 0 if ok, else −1
		// Note: top−left coordinate is (0, 0)
		int draw(Vector position, Color color, char transparent=0) const;
	};
}