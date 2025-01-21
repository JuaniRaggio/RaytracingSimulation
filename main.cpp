#include <iostream>
#include <SDL2/SDL.h>
#include "include/formats.hpp"

int windows_width;
int windows_height;

int main(void) {
  std::cout << "Hello ray!\n";
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window * window = SDL_CreateWindow("Interactive raytracing",
                   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                   0, 0, /* Window height and width are irrelevant since we are using fullscreen  */
                   SDL_WINDOW_FULLSCREEN_DESKTOP);
  SDL_GetWindowSize(window, &windows_width, &windows_height);
  SDL_Surface * window_surface = SDL_GetWindowSurface(window);
  SDL_Quit();
  return 0;
}
