//
// Star.h
//

#pragma once

#include "Object.h"

class Star : public df::Object {

private:
	void out();

public:
	Star();
	int eventHandler(const df::Event* p_e);
};
