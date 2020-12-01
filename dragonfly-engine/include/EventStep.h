#pragma once
#include "Event.h"

namespace df {

    const std::string STEP_EVENT = "df::step";

    class EventStep : public Event {
    
    private:
        int m_step_count; // Iteration number of game loop

    public:
        // Default constructor
        EventStep();
        ~EventStep();
        
        // Constructor with initial step count
        EventStep(int init_step_count);
        
        // Set/get step count
        void setStepCount(int new_step_count);
        int getStepCount() const;
    };
}