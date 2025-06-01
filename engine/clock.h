#ifndef CLOCK_H
#define CLOCK_H
#include <SDL2/SDL.h>
#include <stdio.h>

typedef struct {
  Uint64 current_time;
  Uint64 last_time;
  float delta_time;
} GameClock;

void init_clock(GameClock *clock);
void update_clock(GameClock *clock);

#endif
