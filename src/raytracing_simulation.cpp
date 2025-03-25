#include "../include/raytracing_simulation.hpp"


void Raytracing::start_simulation(void) {
  current_status = RUNNING_SIMULATION;
}

const simulation_status& Raytracing::get_status(void) const {
  return current_status;
}

void Raytracing::manage_event(SDL_Event event) {
  switch (event.type) {
    case SDL_MOUSEBUTTONDOWN:
    break;
    case SDL_QUIT:
      current_status = END_SIMULATION;
    break;
  }
}
