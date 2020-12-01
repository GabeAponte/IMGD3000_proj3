#pragma once

// include platform-specific libraries
#if defined(_WIN64) || defined(_WIN32)
	#include <windows.h>
	#include <profileapi.h>
	#define PLATFORM_WINDOWS
#elif
	#include <time.h>
#endif

// The clock, for timing (such as in the game loop)

namespace df {

	class Clock {

	private:
		// Returns the present system time in milliseconds
		long unsigned int getSystemTime() const;

		// The internal function combining split() and delta()
		long int splitInternal(bool reset);

		#ifdef PLATFORM_WINDOWS
		LARGE_INTEGER m_frequency = { 0 };
		#endif
		long unsigned int m_previous_time = 0; // Previous time delta() was called (in milliseconds)

	public:
		// Sets m_previous_time to current time .
		Clock();

		// Return time elapsed since delta() was last called , −1 if error
		// Resets previous time .
		// Units are microseconds
		long int delta();

		// Return time elapsed since delta() was last called, −1 if error
		// Does not reset previous time
		// Units are microseconds
		long int split();
	};

}