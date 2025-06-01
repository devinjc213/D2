#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL.h>

typedef struct {
  SDL_Rect pos;
  SDL_Rect src_full_rect;
  SDL_Rect src_cur_frame_rect;

  char *src_img;

  float speed;

  int cur_frame;
  int frame_count;

  int frame_w;
  int frame_h;

  // for animations in spreadsheets that wrap
  int frame_rows;
  int frame_columns;

  float frame_duration;
  float frame_time_elapsed;
} Entity;

Entity *create_entity(char *src_img, SDL_Rect src_pos, int frame_rows,
                      int frame_columns, float frame_duration, SDL_Rect pos);
void update_entity(Entity *ent, float delta_time);
void free_entity(Entity *ent);

#endif
