#include "tilemap.h"
#include "../../engine/logger/logger.h"
#include "utils.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

#define INITIAL_LAYER_CAPACITY 420

TileMap *create_tilemap(int height, int width, int layers) {
  TileMap *map = malloc(sizeof(TileMap));
  map->height = height;
  map->width = width;
  map->layer_count = layers;
  map->prop_count = 0;
  map->props_layer = malloc(height * width * sizeof(PropTile));
  map->render_layers = malloc(layers * sizeof(RenderLayer));

  for (int i = 0; i < layers; i++) {
    init_render_layer(&map->render_layers[i], INITIAL_LAYER_CAPACITY);
  }

  return map;
}

void init_render_layer(RenderLayer *render_layer, int initial_capacity) {
  render_layer->tile_count = 0;
  render_layer->ent_count = 0;
  render_layer->tile_capacity = initial_capacity;
  render_layer->ent_capacity = initial_capacity;
  render_layer->tiles = malloc(initial_capacity * sizeof(RenderTile));
  render_layer->ents = malloc(initial_capacity * sizeof(Entity));
}

void add_render_tile(RenderLayer *layer, RenderTile tile) {
  if (layer->tile_count == layer->tile_capacity) {
    layer->tile_capacity *= 2;
    layer->tiles =
        realloc(layer->tiles, layer->tile_capacity * sizeof(RenderTile));
  }

  layer->tiles[layer->tile_count++] = tile;
}

void add_render_ent(RenderLayer *layer, Entity *ent) {
  GINFO("adding ent");
  if (layer->ent_count == layer->ent_capacity) {
    layer->ent_capacity *= 2;
    layer->ents = realloc(layer->ents, layer->ent_capacity * sizeof(Entity));
  }

  layer->ents[layer->ent_count++] = *ent;
  GINFO("Current count: %d", layer->ent_count);
}

void add_prop_tile(TileMap *map, PropTile props) {
  if (map->prop_count == map->height * map->width) {
    GERROR("Prop tiles full");
  }

  map->props_layer[map->prop_count++] = props;
}

void remove_tile(RenderLayer *layer, int x, int y) {
  GINFO("x, y: %d, %d", x, y);
  for (int i = 0; i < layer->tile_count; i++) {
    GINFO("tiles x, y, w, h: %d, %d, %d, %d", layer->tiles[i].dest.x,
          layer->tiles[i].dest.y, layer->tiles[i].dest.w,
          layer->tiles[i].dest.h);
    if ((x >= layer->tiles[i].dest.x) &&
        (x <= layer->tiles[i].dest.x + layer->tiles[i].dest.w) &&
        (y >= layer->tiles[i].dest.y) &&
        (y <= layer->tiles[i].dest.y + layer->tiles[i].dest.h)) {
      GINFO("tile to delete found at %d, %d", x, y);
    }
  }
}

void remove_ent(RenderLayer *layer, int x, int y) {
  for (int i = 0; i < layer->ent_count; i++) {
    if ((x >= layer->ents[i].pos.x) &&
        (x <= layer->ents[i].pos.x + layer->ents[i].pos.w) &&
        (y >= layer->ents[i].pos.y) &&
        (y <= layer->ents[i].pos.y + layer->ents[i].pos.h)) {
      free(&layer->ents[i]);
      layer->ent_count--;
    }
  }
}

void render_layer(RenderLayer *layer, SDL_Renderer *renderer,
                  enum Renderer render_idx, AssetMap *cache, ZoomState *z,
                  float delta_time) {
  if (!layer->tile_count)
    return;

  for (int i = 0; i < layer->tile_count; i++) {
    SDL_Texture *texture =
        get_asset(cache, layer->tiles[i].tilesheet, render_idx);
    int x, y;
    world_to_screen(z->offset_x, z->offset_y, z->scale, layer->tiles[i].dest.x,
                    layer->tiles[i].dest.y, &x, &y);

    SDL_Rect dest = {x, y, layer->tiles[i].dest.w * z->scale,
                     layer->tiles[i].dest.h * z->scale};

    SDL_RenderCopy(renderer, texture, &layer->tiles[i].src, &dest);
  }

  for (int i = 0; i < layer->ent_count; i++) {
    SDL_Texture *texture = get_asset(cache, layer->ents[i].src_img, render_idx);
    int x, y;

    world_to_screen(z->offset_x, z->offset_y, z->scale, layer->ents[i].pos.x,
                    layer->ents[i].pos.y, &x, &y);

    SDL_Rect dest = {x, y, layer->ents[i].pos.w * z->scale,
                     layer->ents[i].pos.h * z->scale};

    SDL_RenderCopy(renderer, texture, &layer->ents[i].src_cur_frame_rect,
                   &dest);
  }
}
