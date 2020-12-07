// Gabriel Aponte
// gaaponte@wpi.edu

//
// Handles playing the game music
//

#pragma once

#include <ResourceManager.h>

// Shorthand to access the MusicPlayer singleton implementation
#define MUSICPLAYER MusicPlayer::getInstance()

class MusicPlayer {

public:

	// Gets the single instance of this class
	static MusicPlayer& getInstance();

	// Plays the game music
	void playMusic();

	// Pauses the game music
	void pauseMusic();

	// Stops the game music
	void stopMusic();

private:

	MusicPlayer();                          // Private since a singleton.
	MusicPlayer(MusicPlayer const&);		// Don't allow copy.
	void operator=(MusicPlayer const&);     // Don't allow assignment.

	// The game music
	df::Music* p_music;

	// Toggles for playing, pausing and stopping the game music
	bool isPlaying;
	bool isPaused;
	bool isStopped;
};

