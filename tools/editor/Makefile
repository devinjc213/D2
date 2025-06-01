CC = gcc
CFLAGS = -g -Wall -Wextra -std=c11 -D_DEFAULT_SOURCE
LDFLAGS = -lSDL2 -lSDL2_image -lm

TARGET = dozy_tiler 
SRCS = main.c editor.c input.c tilemap.c utils.c ../../engine/logger/logger.c ../../engine/asset_manager.c ../../engine/entity.c ../../engine/clock.c
ASSETS_DIR = ./bin/assets/Rogue/Rogue\ Adventure\ World\ 3.0.0/Tilesets\ \(32x32\)/
BIN_DIR = bin

$(TARGET): $(SRCS) copy_assets
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRCS) -o $(BIN_DIR)/$(TARGET) $(LDFLAGS)

copy_assets:
	@mkdir -p $(BIN_DIR)/assets/tilesets
	@cp -R $(ASSETS_DIR)/* $(BIN_DIR)/assets/tilesets

clean:
	rm -f $(BIN_DIR)/$(TARGET)
