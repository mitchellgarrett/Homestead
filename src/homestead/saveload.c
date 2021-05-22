#include <homestead/saveload.h>
#include <homestead/homestead.h>
#include <stdio.h>
#include <stdlib.h>
#include <mICE/mICE.h>

int saveVillage(struct Village* village) {
	FILE* file = fopen(SAVE_FILE, "wb");
	if (!file) return 0;

	fwrite(village, sizeof(Village), 1, file);
	fwrite(village->calendar, sizeof(Calendar), 1, file);

	for (int i = 0; i < village->population; ++i) {
		fwrite(village->villagers[i], sizeof(Villager), 1, file);
	}

	for (int i = 0; i < village->numBuildings; ++i) {
		fwrite(village->buildings[i], sizeof(Building), 1, file);
	}

	fclose(file);
	return 1;
}

int loadVillage(struct Village* village) {
	FILE* file = fopen(SAVE_FILE, "rb");
	if (!file) return 0;

	fread(village, sizeof(Village), 1, file);

	village->calendar = (Calendar*)malloc(sizeof(Calendar));
	fread(village->calendar, sizeof(Calendar), 1, file);

	//village->map = newMap(MAP_WIDTH, MAP_HEIGHT);
	//fread(village->map, )

	village->villagers = (Villager**)malloc(village->maxPopulation * sizeof(Villager*));
	for (int i = 0; i < village->population; ++i) {
		village->villagers[i] = (Villager*)malloc(sizeof(Villager));
		fread(village->villagers[i], sizeof(Villager), 1, file);
		village->villagers[i]->village = village;
	}

	village->buildings = (Building**)malloc(village->maxBuildings * sizeof(Building*));
	for (int i = 0; i < village->numBuildings; ++i) {
		village->buildings[i] = (Building*)malloc(sizeof(Building));
		fread(village->buildings[i], sizeof(Building), 1, file);
		village->buildings[i]->village = village;
	}

	fclose(file);
	return 1;
}