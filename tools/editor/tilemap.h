#ifndef TILEMAP_H
#define TILEMAP_H

#include "../../engine/asset_manager.h"
#include "../../engine/entity.h"
#include "utils.h"

typedef struct {
  int layer;
  SDL_Rect src;
  SDL_Rect dest;
  char *tilesheet;
} RenderTile;

typedef struct {
  int tile_count;
  int tile_capacity;
  int ent_count;
  int ent_capacity;
  RenderTile *tiles;
  Entity *ents;
} RenderLayer;

typedef struct {
  SDL_Rect tile;
  int collidable;
} PropTile;

typedef struct {
  int width;
  int height;
  int layer_count;
  int prop_count;
  PropTile *props_layer;
  RenderLayer *render_layers;
} TileMap;

TileMap *create_tilemap(int height, int width, int layers);
void init_render_layer(RenderLayer *render_layer, int initial_capcity);
void add_render_tile(RenderLayer *layer, RenderTile tile);
void add_render_ent(RenderLayer *layer, Entity *ent);
void add_prop_tile(TileMap *map, PropTile props);
void remove_tile(RenderLayer *layer, int x, int y);
void remove_ent(RenderLayer *layer, int x, int y);
void update_ent(Entity *ent, float delta_time);
void render_layer(RenderLayer *layer, SDL_Renderer *renderer,
                  enum Renderer render_idx, AssetMap *cache, ZoomState *z,
                  float delta_time);
void free_tilemap(TileMap *map);

#endif
