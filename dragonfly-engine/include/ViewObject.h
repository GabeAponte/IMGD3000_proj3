#pragma once
#include <string>
#include "Object.h"
#include "Event.h"

namespace df {

	// General location of ViewObject on screen
	enum ViewObjectLocation {
		UNDEFINED = -1,
		TOP_LEFT,
		TOP_CENTER,
		TOP_RIGHT,
		CENTER_LEFT,
		CENTER_CENTER,
		CENTER_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_CENTER,
		BOTTOM_RIGHT,
	};

	class ViewObject : public Object {

	private:
		std::string view_string;	// Label for value (e.g., "Points")
		int m_value;				// Value displayed (e.g., points)
		bool m_draw_value;			// True if should draw value
		bool m_border;				// True if border around display
		Color m_color;				// Color for text (and border)
		ViewObjectLocation m_location; // Location of ViewObject

	public:
		// Construct ViewObject
		// Object settings: SPECTRAL, max alt
		// ViewObject defaults: border, top center, default color, draw value
		ViewObject();

		// Draw view string and value
		virtual int draw();

		// Handle ‘view’ event if tag matches view string (others ignored)
		// Return 0 if ignored, else 1 if handled
		virtual int eventHandler(const Event* p_e);

		// Set/Get general location of ViewObject on screen
		void setLocation(ViewObjectLocation new_location);
		ViewObjectLocation getLocation() const;

		// Set/Get view value
		void setValue(int new_value);
		int getValue() const;

		// Set/Get view border (true = display border)
		void setBorder(bool new_border);
		bool getBorder() const;

		// Set/Get view color
		void setColor(Color new_color);
		Color getColor() const;
		
		// Set/Get view display string
		void setViewString(std::string new_view_string);
		std::string getViewString() const;
		
		// Set/Get whether to draw value with display string
		void setDrawValue(bool new_draw_value = true);
		bool getDrawValue() const;
	};
}