// Joseph Henry Stadolnik IV
// jhstadolnik@wpi.edu

// An object used to test audio

#pragma once
#include "Sound.h"
#include "Music.h"
#include "Object.h"

namespace df {

	class TestAudio : public Object {

	private:
		Sound* m_p_sound1;
		Sound* m_p_sound2;
		Music* m_p_music;

	public:
		TestAudio();
		~TestAudio();

		int eventHandler(const Event* p_e);	// OVERRIDE
		int draw();							// OVERRIDE
	};
}