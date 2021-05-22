#include <mICE/mICE.h>
#include <homestead/homestead.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

Map* generateMap() {
	Map* map = newMap(MAP_WIDTH, MAP_HEIGHT);

	for (int y = 0; y < MAP_HEIGHT; ++y) {
		for (int x = 2; x < 8; ++x) {
			map->tiles[y][x] = Tile_Water;
		}
	}

	// Trees
	int num = 50;
	for (int i = 0; i < num; ++i) {
		int x = randInt(MAP_WIDTH / 2, MAP_WIDTH);
		int y = randInt(1, MAP_HEIGHT / 2);
		map->tiles[y][x] = Tile_Tree;
	}

	// Stones
	for (int i = 0; i < num; ++i) {
		int x = randInt(MAP_WIDTH / 2, MAP_WIDTH);
		int y = randInt(MAP_HEIGHT / 2, MAP_HEIGHT);
		map->tiles[y][x] = Tile_Stone;
	}

	return map;
}

void build(Village* village, BuildingType type) {
	Building prototype = building_prototypes[type];
	if (village->wood < prototype.woodCost || village->stone < prototype.stoneCost) return;

	village->wood -= prototype.woodCost;
	village->stone -= prototype.stoneCost;

	for (int y = 0; y < prototype.height; ++y) {
		for (int x = 0; x < prototype.width; ++x) {
			if (cursor_x + x >= MAP_WIDTH || cursor_y + y >= MAP_HEIGHT || village->map->tiles[cursor_y + y][cursor_x + x] != Tile_Empty) return;
		}
	}

	placeBuilding(village, type, cursor_x, cursor_y);
	drawMap(village->map);
	drawVillage(village);
	printHUD(village, village->calendar);
}

void nextTurn(Village* village) {
	nextDay(village->calendar);
	villageUpdate(village);
}

void playGame(Village* village) {
	setSeed(0);
	setCursor(2);

	cursor_x = MAP_WIDTH / 2;
	cursor_y = MAP_HEIGHT / 2;

	if (!village) {
		village = newVillage();
		//village->map = generateMap();
		village->calendar = newCalendar();
	}
	village->map = generateMap();
	drawMap(village->map);

	int key = 0;
	while (key != 'q') {
		printHUD(village, village->calendar);
		drawVillage(village);

		moveCursor(map_offset_x + cursor_x, map_offset_y + cursor_y);

		key = tolower(getKey());
		switch (key) {

		// Movement
		case 'w':
			cursor_y--;
			if (cursor_y < 0) cursor_y = 0;
			break;

		case 's':
			cursor_y++;
			if (cursor_y >= MAP_HEIGHT) cursor_y = MAP_HEIGHT - 1;
			break;

		case 'a':
			cursor_x--;
			if (cursor_x < 0) cursor_x = 0;
			break;

		case 'd':
			cursor_x++;
			if (cursor_x >= MAP_WIDTH) cursor_x = MAP_WIDTH - 1;
			break;

		// Menu
		case 'b':
			buildingMenu(village);
			break;

		case 'v':
			villagerMenu(village);
			break;

		case 'e':
			nextTurn(village);
			break;
		}
		saveVillage(village);
		clearMenu();
	}
}

int main(int argc, char* argv[]) {

	if (!initScreenColor()) {
		printf("Could not initialize screen with color.\n");
		return -1;
	}

	setScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	setScreenTitle(SCREEN_TITLE);

	defineColor(MAGENTA, 600, 300, 0);
	defineColor(RED, 0, 400, 0);
	defineColor(9, 250, 250, 250);
	defineColorPair(65, 9, GREEN);

	//playGame();
	mainMenu();
	quit();

	return 0;
}