#include <homestead/map.h>
#include <stdlib.h>

Map* newMap(int width, int height) {
	Map* map = (Map*)malloc(sizeof(Map));
	map->width = width;
	map->height = height;

	map->tiles = (Tile**)malloc(height * sizeof(Tile*));
	for (int y = 0; y < height; ++y) {
		map->tiles[y] = (Tile*)malloc(width * sizeof(Tile));
		for (int x = 0; x < width; ++x) {
			map->tiles[y][x] = Tile_Empty;
		}
	}

	return map;
}