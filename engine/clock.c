#include "clock.h"

void init_clock(GameClock *clock) {
  clock->current_time = SDL_GetPerformanceCounter();
  clock->last_time = clock->current_time;
  clock->delta_time = 0.0f;
}

void update_clock(GameClock *clock) {
  clock->last_time = clock->current_time;
  clock->current_time = SDL_GetPerformanceCounter();

  Uint64 frequency = SDL_GetPerformanceFrequency();
  clock->delta_time =
      (float)(clock->current_time - clock->last_time) / frequency;

  if (clock->delta_time > 0.05f) {
    clock->delta_time = 0.05f;
  }
}
