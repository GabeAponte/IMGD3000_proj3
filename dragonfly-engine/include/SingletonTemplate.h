// From Dragonfly book

#pragma once

class Singleton {
private:
	Singleton();							// No constructing
	Singleton(const Singleton&);			// No copying
	Singleton& operator=(const Singleton&);	// No assigning
public:
	static Singleton & getInstance();		// Return instance
};

// Return the sole instance of the class
Singleton& Singleton::getInstance() {
	// Note: a static variable persists after method ends
	static Singleton single;
	return single;
}
