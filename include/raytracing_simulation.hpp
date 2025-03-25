#pragma once

#include <SDL2/SDL.h>
#include "formats.hpp"

// This file has the functions and methods in charge of administrating the tecnical side of the simulation

typedef enum {END_SIMULATION = 0, RUNNING_SIMULATION} simulation_status;

class Raytracing {
  private:
    simulation_status current_status {END_SIMULATION};
  public:
    Raytracing();
    const simulation_status& get_status(void) const;
    // This method will restart the simulation if it is used while the simulation is running
    void start_simulation(void);
    void manage_event(SDL_Event event);
};
