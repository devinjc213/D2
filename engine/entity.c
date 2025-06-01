#include "entity.h"

Entity *create_entity(char *src_img, SDL_Rect src_pos, int frame_rows,
                      int frame_columns, float frame_duration, SDL_Rect pos) {
  Entity *ent = malloc(sizeof(Entity));
  ent->src_img = src_img;
  ent->pos = pos;
  ent->src_full_rect = src_pos;
  ent->frame_rows = frame_rows;
  ent->frame_columns = frame_columns;
  ent->frame_duration = frame_duration;
  ent->frame_count = frame_columns * frame_rows;
  ent->frame_time_elapsed = 0;
  ent->cur_frame = 0;
  ent->frame_w = src_pos.w / frame_columns;
  ent->frame_h = src_pos.h / frame_rows;

  SDL_Rect cur_frame = {.x = src_pos.x,
                        .y = src_pos.y,
                        .w = ent->frame_w,
                        .h = ent->frame_h};

  ent->src_cur_frame_rect = cur_frame;

  return ent;
}

void update_entity(Entity *ent, float delta_time) {
  if ((ent->frame_time_elapsed += delta_time) > ent->frame_duration) {
    ent->cur_frame = (ent->cur_frame + 1) % ent->frame_count;
    
    // Calculate row and column from current frame
    int row = ent->cur_frame / ent->frame_columns;
    int col = ent->cur_frame % ent->frame_columns;
    
    // Update source rectangle
    ent->src_cur_frame_rect.x = ent->src_full_rect.x + (col * ent->frame_w);
    ent->src_cur_frame_rect.y = ent->src_full_rect.y + (row * ent->frame_h);
    ent->src_cur_frame_rect.w = ent->frame_w;
    ent->src_cur_frame_rect.h = ent->frame_h;
    
    // Reset timer
    ent->frame_time_elapsed -= ent->frame_duration;
  }
}

void free_entity(Entity *ent) { free(ent); }
