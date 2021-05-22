#include <homestead/renderer.h>
#include <homestead/homestead.h>
#include <mICE/screen.h>
#include <mICE/color.h>

void drawMap(Map* map) {
	setColor(WHITE, GREEN);
	drawBoxFill(1, TOP_HUD_SIZE, MAP_WIDTH, MAP_HEIGHT, ' ');

	for (int y = 0; y < map->height; ++y) {
		for (int x = 0; x < map->width; ++x) {
			Tile tile = map->tiles[y][x];
			switch (tile) {

			case Tile_Water:
				setColor(CYAN, BLUE);
				printcat(1 + x, TOP_HUD_SIZE + y, water1);
				break;

			case Tile_Tree:
				drawTree(1 + x, TOP_HUD_SIZE + y);
				break;

			case Tile_Stone:
				useColorPair(65);
				printcat(1 + x, TOP_HUD_SIZE + y, human);
				break;
			}
		}
	}
}

void drawTree(int x, int y) {
	setColor(MAGENTA, GREEN);
	printcat(x, y, human);
	setColor(RED, GREEN);
	printcat(x, y - 1, triangle_n);
}

void drawSilo(int x, int y) {
	setColor(WHITE, MAGENTA);

	printsfat(x + 0, y + 0, "%c%c", angle_r, angle_l);
	//printsfat(x + 0, y + 1, "%c  %c", angle_r, angle_l);

	printcat(x + 0, y + 1, wall_v);
	printcat(x + 1, y + 1, wall_v);

	printcat(x + 0, y + 2, wall_v);
	printcat(x + 1, y + 2, wall_v);

	printcat(x + 0, y + 3, wall_ne);
	printcat(x + 1, y + 3, wall_nw);
}

void drawFarm(int x, int y) {
	setColor(MAGENTA, GREEN);
	drawLineVertical(x, y, y + 4, wall_v);
	drawLineVertical(x + 4, y, y + 4, wall_v);
	drawLineHorizontal(y, x, x + 4, wall_h);
	drawLineHorizontal(y + 4, x, x + 4, wall_h);

	printcat(x + 0, y + 0, wall_se);
	printcat(x + 4, y + 0, wall_sw);
	printcat(x + 0, y + 4, wall_ne);
	printcat(x + 4, y + 4, wall_nw);

	setColor(WHITE, YELLOW);
	drawBoxFill(x + 1, y + 1, 3, 3, ' ');
}

void drawHouse(int x, int y) {
	setColor(WHITE, MAGENTA);
	printsfat(x + 1, y + 0, "%c%c", angle_r, angle_l);
	printsfat(x + 0, y + 1, "%c  %c", angle_r, angle_l);
	printcat(x + 0, y + 2, wall_ne);
	printcat(x + 1, y + 2, wall_h);
	printcat(x + 2, y + 2, wall_h);
	printcat(x + 3, y + 2, wall_nw);
}

void drawBuilding(Building* building) {
	int x = 1 + building->x;
	int y = TOP_HUD_SIZE + building->y;
	switch (building->type) {
	case Farm: drawFarm(x, y); break;
	case Silo: drawSilo(x, y); break;
	default: drawHouse(x, y); break;
	}
}

void drawVillage(Village* village) {
	for (int i = 0; i < village->numBuildings; ++i) {
		drawBuilding(village->buildings[i]);
	}
}