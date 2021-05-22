#include <homestead/menu.h>
#include <homestead/homestead.h>
#include <mICE/mIce.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int map_offset_x = 1;
int map_offset_y = TOP_HUD_SIZE;

int cursor_x = 0;
int cursor_y = 0;

extern void playGame(Village* village);
extern void build(Village* village, BuildingType type);

void quit() {
	closeScreen();
	exit(0);
}

void newGame() {
	playGame(NULL);
}

void loadGame() {
	Village* village = newVillage();
	loadVillage(village);
	playGame(village);
}

void manual() {
	printTitle();
	clearColor();

	FILE* file = fopen(MANUAL_FILE, "r");
	if (!file) {
		mainMenu();
		return;
	}

	char buf[255];
	int y = 15;
	while (fgets(buf, 255, file)) {
		printsfat((SCREEN_WIDTH - strlen(buf)) / 2 + 1, y, "%s", buf);
		y++;
	}

	fclose(file);

	getKey();
}

void printTitle() {
	setCursor(0);
	clearColor();
	clearScreen();

	int title_offset = (SCREEN_WIDTH - 55) / 2;
	int title_height = 6;

	drawLineVertical(0, 0, SCREEN_HEIGHT, wall_v);
	drawLineVertical(SCREEN_WIDTH - 1, 0, SCREEN_HEIGHT, wall_v);

	drawLineHorizontal(0, 1, SCREEN_WIDTH - 2, wall_h);
	drawLineHorizontal(title_height + 2, 1, SCREEN_WIDTH - 2, wall_h);
	drawLineHorizontal(SCREEN_HEIGHT - 1, 1, SCREEN_WIDTH - 2, wall_h);

	printcat(0, 0, wall_se);
	printcat(SCREEN_WIDTH - 1, 0, wall_sw);
	printcat(0, title_height + 2, wall_nes);
	printcat(SCREEN_WIDTH - 1, title_height + 2, wall_nsw);
	printcat(0, SCREEN_HEIGHT - 1, wall_ne);
	printcat(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, wall_nw);

	printsat(title_offset, 1, L"  _    _                           _                 _ ");
	printsat(title_offset, 2, L" | |  | |                         | |               | |");
	printsat(title_offset, 3, L" | |__| | ___  _ __ ___   ___  ___| |_ ___  __ _  __| |");
	printsat(title_offset, 4, L" |  __  |/ _ \\| '_ ` _ \\ / _ \\/ __| __/ _ \\/ _` |/ _` |");
	printsat(title_offset, 5, L" | |  | | (_) | | | | | |  __/\\__ \\ ||  __/ (_| | (_| |");
	printsat(title_offset, 6, L" |_|  |_|\\___/|_| |_| |_|\\___||___/\\__\\___|\\__,_|\\__,_|");

	printsat(1, SCREEN_HEIGHT - 2, L"Mitchell Garrett");
	printsfat(SCREEN_WIDTH - 5, SCREEN_HEIGHT - 2, "v%d.%d", HOMESTEAD_VERSION_MAJOR, HOMESTEAD_VERSION_MINOR);
}

void mainMenu() {
	int menu_width = 10;
	int menu_y = SCREEN_HEIGHT / 2;
	int menu_offset = (SCREEN_WIDTH - menu_width) / 2;

	char* selections[] = { L"New Game ", L"Load Game", L"  Manual  ", L"   Quit   " };
	int num_selections = 4;
	int selection = 0;
	int key = 0;
	while (key != 'q') {
		printTitle();

		int menu_outline_min_x = menu_offset - menu_width - 1;
		int menu_outline_max_x = menu_offset + menu_width * 2;
		int menu_outline_min_y = menu_y - 2;
		int menu_outline_max_y = menu_y + num_selections * 2;

		drawLineVertical(menu_outline_min_x, menu_outline_min_y, menu_outline_max_y, twall_v);
		drawLineVertical(menu_outline_max_x, menu_y - 2, menu_outline_max_y, twall_v);

		drawLineHorizontal(menu_outline_min_y, menu_outline_min_x, menu_outline_max_x, twall_h);
		drawLineHorizontal(menu_outline_max_y, menu_outline_min_x, menu_outline_max_x, twall_h);

		printcat(menu_outline_min_x, menu_outline_min_y, twall_se);
		printcat(menu_outline_max_x, menu_outline_min_y, twall_sw);
		printcat(menu_outline_min_x, menu_outline_max_y, twall_ne);
		printcat(menu_outline_max_x, menu_outline_max_y, twall_nw);

		for (int i = 0; i < num_selections; ++i) {
			if (selection == i) {
				setColor(BLACK, WHITE);
			} else {
				clearColor();
			}
			printsat(menu_offset, i * 2 + menu_y, selections[i]);
		}

		key = tolower(getKey());
		switch (key) {
		case 'w':
			selection--;
			if (selection < 0) selection = 0;
			break;

		case 's':
			selection++;
			if (selection >= num_selections) selection = num_selections - 1;
			break;

		case 10:
			switch (selection) {
			case 0: newGame(); break;
			case 1: loadGame(); break;
			case 2: manual(); break;
			case 3: return;
			}
			break;
		}
	}
}

void printHUD(Village* village) {
	clearColor();
	//setColor(WHITE, YELLOW); // Decide what colors to use for HUD

	// Draw outline
	drawLineVertical(0, 0, SCREEN_HEIGHT, wall_v);
	drawLineVertical(SCREEN_WIDTH - 1, 0, SCREEN_HEIGHT, wall_v);

	drawLineHorizontal(0, 1, SCREEN_WIDTH - 2, wall_h);
	drawLineHorizontal(TOP_HUD_SIZE - 1, 1, SCREEN_WIDTH - 2, wall_h);

	drawLineHorizontal(SCREEN_HEIGHT - 1, 1, SCREEN_WIDTH - 2, wall_h);
	drawLineHorizontal(SCREEN_HEIGHT - BOTTOM_HUD_SIZE, 1, SCREEN_WIDTH - 2, wall_h);

	printcat(0, 0, wall_se);
	printcat(SCREEN_WIDTH - 1, 0, wall_sw);
	printcat(0, TOP_HUD_SIZE - 1, wall_nes);
	printcat(SCREEN_WIDTH - 1, TOP_HUD_SIZE - 1, wall_nsw);

	int top = SCREEN_HEIGHT - BOTTOM_HUD_SIZE;
	printcat(0, top, wall_nes);
	printcat(SCREEN_WIDTH - 1, top, wall_nsw);
	printcat(0, SCREEN_HEIGHT - 1, wall_ne);
	printcat(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, wall_nw);

	drawBoxFill(1, 1, SCREEN_WIDTH - 2, TOP_HUD_SIZE - 2, ' ');
	drawBoxFill(1, top + 1, SCREEN_WIDTH - 2, BOTTOM_HUD_SIZE - 2, ' ');

	// Print controls
	printsat(1, top + 1, L"[B]uildings");
	printsat(1, top + 2, L"[V]illagers");
	printsat(1, top + 3, L"[E]nd day");

	// Print village variables
	printsfat(1, 1, "Gold: %d, Food %d/%d, Pop: %d/%d, Wood: %d/%d, Stone: %d/%d", village->gold, village->food, village->maxFood, village->population, village->maxPopulation, village->wood, village->maxWood, village->stone, village->maxStone);

	// Print date
	Calendar* calendar = village->calendar;
	char buf[255];
	sprintf_s(buf, 255, "Day: %d, Season: %s, Year: %d", calendar->day, getSeasonName(calendar->season), calendar->year);
	printsfat(SCREEN_WIDTH - strlen(buf) - 1, 1, "Day: %d, Season: %s, Year: %d", calendar->day, getSeasonName(calendar->season), calendar->year);
}

void clearMenu() {
	clearColor();
	int offset_x = 12;
	drawBoxFill(offset_x, SCREEN_HEIGHT - BOTTOM_HUD_SIZE + 1, SCREEN_WIDTH - offset_x, BOTTOM_HUD_SIZE - 2, ' ');
}

void buildingMenu(Village* village) {
	clearColor();
	int offset_x = 15;
	int offset_y = SCREEN_HEIGHT - BOTTOM_HUD_SIZE + 1;

	int selection = 0;
	int key = 0;
	while (key != 'q' && key != 'b') {

		for (int i = 0; i < NUM_BUILDINGS; ++i) {
			if (building_prototypes[i].woodCost < 0) continue;
			if (i == selection) setColor(BLACK, WHITE);
			else clearColor();
			printsfat(offset_x + (i / 3) * 20, offset_y + i % 3, "%s (%dw, %ds)", building_prototypes[i].name, building_prototypes[i].woodCost, building_prototypes[i].stoneCost);
		}

		moveCursor(map_offset_x + cursor_x, map_offset_y + cursor_y);
		key = tolower(getKey());
		switch (key) {
		case 'w':
			selection--;
			if (selection < 0) selection = 0;
			break;

		case 's':
			selection++;
			if (selection >= NUM_BUILDINGS) selection = NUM_BUILDINGS - 1;
			break;

		case 10:
			build(village, selection);
			return;
		}
	}
}

void villagerMenu(Village* village) {
	clearColor();
	int offset_x = 15;
	int offset_y = SCREEN_HEIGHT - BOTTOM_HUD_SIZE + 1;

	int key = 0;
	int selection = 1;
	while (key != 'q' && key != 'v') {
		clearMenu();

		printsfat(offset_x, offset_y + 0, "Population: %d/%d", village->population, village->maxPopulation);
		printsfat(offset_x, offset_y + 1, "Children/Adults: %d/%d", village->children, village->adults);
		printsfat(offset_x, offset_y + 2, "Unemployed: %d", village->workers[Unemployed]);

		for (int i = 1; i < NUM_JOBS; ++i) {
			if (i == selection) setColor(BLACK, WHITE);
			else clearColor();
			printsfat(offset_x + 22 + ((i - 1) / 3) * 20, offset_y + (i - 1) % 3, "%s: %d/%d (+/-)", job_names[i], village->workers[i], village->maxWorkers[i]);
		}

		moveCursor(map_offset_x + cursor_x, map_offset_y + cursor_y);
		key = tolower(getKey());
		switch (key) {
		case 'w':
			selection--;
			if (selection < 1) selection = 1;
			break;

		case 's':
			selection++;
			if (selection >= NUM_JOBS) selection = NUM_JOBS - 1;
			break;

		case '=':
			if (village->workers[Unemployed] > 0 && village->workers[selection] < village->maxWorkers[selection]) {
				village->workers[Unemployed]--;
				village->workers[selection]++;
			}
			break;;

		case '-':
			if (village->workers[selection] > 0) {
				village->workers[Unemployed]++;
				village->workers[selection]--;
			}
			break;;
		}
	}
}