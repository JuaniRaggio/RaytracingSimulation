#include <iostream>
#include <SDL2/SDL.h>
#include "include/formats.hpp"
#include "include/raytracing_simulation.hpp"
#include "include/error_management.hpp"

static void show_simulation_updates(Raytracing raytracing, SDL_Surface * surface);

int main(void) {
  std::cout << "Hello ray!\n";
  CHECKERROR(SDL_Init(SDL_INIT_VIDEO) != SUCCESS, SDL_GetError());
  SDL_Window * window = SDL_CreateWindow("Interactive raytracing",
                   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                   0, 0, /* Window height and width are irrelevant since we are using fullscreen  */
                   SDL_WINDOW_FULLSCREEN_DESKTOP);
  CHECKERROR(window == NULL, SDL_GetError());
  SDL_GetWindowSize(window, &windows_width, &windows_height);

  SDL_Surface * window_surface = SDL_GetWindowSurface(window);
  CHECKERROR(window_surface == NULL, SDL_GetError());

  Raytracing raytracing = Raytracing();
  // raytracing.start_simulation();
  // Makes no sense to do this method because when to finish the simulation should be decided by the front aka this file
  SDL_Event current_event;
  while (raytracing.get_status() != END_SIMULATION) {
    while (SDL_PollEvent(&current_event)) {
      raytracing.manage_event(current_event);
    }
    show_simulation_updates(raytracing, window_surface);
    SDL_UpdateWindowSurface(window);
  }

  SDL_DestroyWindowSurface(window);
  SDL_DestroyWindow(window);
  SDL_Quit();
  std::cout << "Bye ray!\n";
  return 0;
}

static void show_simulation_updates(Raytracing raytracing, SDL_Surface * surface) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      // Show each cell. Probably multiple states are going to be settled
    }
  }
  return;
}
