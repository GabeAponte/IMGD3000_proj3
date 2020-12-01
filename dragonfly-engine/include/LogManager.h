// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

#pragma once
#include <stdarg.h>
#include "Utility.h"
#include "Manager.h"

namespace df {

	// Two-letter access macro
	#define LM LogManager::getInstance()

	class LogManager: public Manager {
	
	private:
		LogManager();								// No constructing
		LogManager(const LogManager&);				// No copying
		LogManager& operator=(const LogManager&);	// No assigning

		// Private implementation of writeLog used to support multiple constructors
		int writeLogInternal(int level, const char* text, va_list args) const;

		const char* LOGFILE_NAME = "dragonfly.log";	// Filename for the log file
		FILE *log_file;					// Pointer to the log file
		bool do_flush = false;			// Whether to flush log immediately to disk
		bool log_time_string = true;	// Whether to display the timestamp of log messages
		bool log_step_count = true;		// Whether to display the engine step count of log messages
		int log_level = 2;				// The level of log verbosity

	public:
		~LogManager();

		// Return singleton instance
		static LogManager& getInstance();
		
		int startUp();		// OVERRIDE
		void shutDown();	// OVERRIDE

		// Enable or disable logging with timestamps
		void setLogTime(bool enabled=true);

		// Enable or disable logging with step count
		void setLogStepCount(bool enabled=true);

		// Enable or disable flushing
		void setFlush(bool enabled=true);

		// Changes the debug log level
		// 0 is lowest (minimal logs)
		// 1 is warnings
		// 2 is engine function calls
		// 3 is update loop timing
		void setLogLevel(int level=0);

		// Writes a message to the log. Accepts a variable number of arguments
		// Optionally starts with debug level (minimum level to display message at)
		// Return the number of bites written, -1 if error
		int writeLog(const char* text, ...) const;
		int writeLog(int level, const char* text, ...) const;
	};
}