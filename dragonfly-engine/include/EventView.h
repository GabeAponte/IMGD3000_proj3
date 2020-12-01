#pragma once
#include "Event.h"

namespace df {

	const std::string VIEW_EVENT = "df::view";

	class EventView : public Event {
	
	private:
		std::string m_tag; // Tag to associate
		int m_value; // Value for view
		bool m_delta; // True if change in  alue, else replace value
		
	public:
		// Create view event with tag VIEW EVENT, value 0 and delta false
		EventView();
		
		// Create view event with tag, value and delta as indicated
		EventView(std::string new_tag, int new_value, bool new_delta);
		
		// Set/Get tag to new tag
		void setTag(std::string new_tag);
		std::string getTag() const;
		
		// Set/Get value
		void setValue(int new_value);
		int getValue() const;
		
		// Set/Get delta
		void setDelta(bool new_delta);
		bool getDelta() const;
	};
}