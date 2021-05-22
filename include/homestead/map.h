#ifndef HOMESTEAD_MAP
#define HOMESTEAD_MAP

typedef enum Tile { Tile_Empty, Tile_Water, Tile_Tree, Tile_Stone, Tile_Building } Tile;

typedef struct Map {

	int width;
	int height;

	Tile** tiles;

} Map;

Map* newMap(int width, int height);

#endif
