// Gabriel Aponte
// gaaponte@wpi.edu

//
// Handles playing the game music
//

#include "..\header_files\MusicPlayer.h"

using namespace df;

MusicPlayer::MusicPlayer() {

	// Set the game music
	p_music = RM.getMusic("game-music");

	// Initialize vars
	isPlaying = false;
	isPaused = false;
	isStopped = false;
}

// Get the singleton implementation of this class
MusicPlayer& MusicPlayer::getInstance()
{
	static MusicPlayer player;
	return player;
}

// Play the game music
void MusicPlayer::playMusic()
{
	// Only play if it isn't already playing
	if (!isPlaying) {
		p_music->play();

		// Change toggle values
		isPlaying = true;
		isPaused = false;
		isStopped = false;
	}
}

// Pause the game music
void MusicPlayer::pauseMusic()
{
	// Only pause if it is playing
	if (!isPaused && !isStopped && isPlaying) {
		p_music->pause();

		isPlaying = false;
		isPaused = true;
		isStopped = false;
	}
}

// Stop the game music
void MusicPlayer::stopMusic()
{
	// Only stop if it is playing
	if (!isStopped && !isPaused && isPlaying) {
		p_music->stop();

		isPlaying = false;
		isPaused = false;
		isStopped = true;
	}
}
