//
// Reticle.h
//

#pragma once

#include "Object.h"

#define RETICLE_CHAR '+'

class Reticle : public df::Object {

public:
	Reticle();
	int draw(void);
	int eventHandler(const df::Event* p_e);
};
