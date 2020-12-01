#pragma once

#include <string>

// Represents a game event

namespace df {

	const std::string UNDEFINED_EVENT = "df::undefined";

	class Event {

	private:
		std::string m_event_type;

	public:
		// Create base event
		Event();

		// Destructor
		virtual ~Event();

		// Set/get event type
		void setType(std::string new_type);
		std::string getType() const;
	};
}
