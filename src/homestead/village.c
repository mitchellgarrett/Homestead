#include <homestead/village.h>
#include <homestead/villager.h>
#include <homestead/building.h>
#include <homestead/map.h>
#include <homestead/homestead.h>
#include <stdlib.h>
#include <string.h>
#include <mICE/screen.h>

Village* newVillage() {
	Village* village = (Village*)malloc(sizeof(Village));
	
	memset(village, 0, sizeof(Village));

	village->gold = 100;
	village->food = 10;
	village->maxFood = 10;
	village->population = 5;
	village->maxPopulation = 5;
	village->maxBuildings = 25;
	village->wood = 15;
	village->maxWood = 15;
	village->stone = 15;
	village->maxStone = 15;

	village->villagers = (Villager**)malloc(village->maxPopulation * sizeof(Villager*));
	village->buildings = (Building**)malloc(village->maxBuildings * sizeof(Building*));

	village->numBuildings = 1;
	village->buildings[0] = newBuilding(House);
	village->buildings[0]->x = MAP_WIDTH / 2;
	village->buildings[0]->y = MAP_HEIGHT / 2;

	for (int i = 0; i < village->population; ++i) {
		village->villagers[i] = newVillager();
		village->villagers[i]->village = village;
		village->villagers[i]->age = ADULT_AGE;
	}
	village->adults = village->population;
	village->workers[Unemployed] = village->adults;

	return village;
}

void villageUpdate(Village* village) {
	village->food += -village->population + 3 * village->workers[Farmer] + 6 * village->workers[Fisherman];
	if (village->food > village->maxFood) {
		village->food = village->maxFood;
	}

	village->wood += village->workers[Logger];
	if (village->wood > village->maxWood) village->wood = village->maxWood;

	village->stone += village->workers[Miner];
	if (village->stone > village->maxStone) village->stone = village->maxStone;

	if (village->food < 0) {
		removeVillager(village);
		village->food = 0;
	} else if (village->population < village->maxPopulation && village->food >= village->population * 3) {
		Villager* v = newVillager();
		v->village = village;
		village->villagers[village->population++] = v;
		village->children++;
	}

	for (int i = 0; i < village->population; ++i) {
		Villager* v = village->villagers[i];
		v->age++;
		if (v->age == ADULT_AGE) {
			village->children--;
			village->adults++;
			village->workers[Unemployed]++;
		}
	}

	saveVillage(village);
}

void placeBuilding(Village* village, enum BuildingType type, int x, int y) {
	if (village->numBuildings >= village->maxBuildings) {
		setMaxBuildings(village, village->maxBuildings + 25);
	}

	Building* building = newBuilding(type);
	building->village = village;
	building->x = x;
	building->y = y;

	village->buildings[village->numBuildings++] = building;

	for (int dx = x; dx < building->width; ++dx) {
		for (int dy = y; dy < building->height; ++dy) {
			village->map->tiles[dy][dx] = Tile_Building;
		}
	}

	switch (building->type) {

	case House:
		setMaxVillagers(village, village->maxPopulation + building->maxWorkers);
		break;

	case Silo:
		village->maxFood += building->maxWorkers;
		break;

	case Warehouse:
		village->maxWood += building->maxWorkers;
		village->maxStone += building->maxWorkers;
		break;

	case Farm:
		village->maxWorkers[Farmer] += building->maxWorkers;
		break;

	case FishingHut:
		village->maxWorkers[Fisherman] += building->maxWorkers;
		break;

	case LoggingCamp:
		village->maxWorkers[Logger] += building->maxWorkers;
		break;

	case Mine:
		village->maxWorkers[Miner] += building->maxWorkers;
		break;
	}
}

void setMaxVillagers(Village* village, int max) {
	Villager** villagers = (Villager**)malloc(max * sizeof(Villager*));

	for (int i = 0; i < village->population; ++i) {
		villagers[i] = village->villagers[i];
	}
	free(village->villagers);
	village->maxPopulation = max;
	village->villagers = villagers;
}

void setMaxBuildings(Village* village, int max) {
	Building** buildings = (Building**)malloc(max * sizeof(Building*));

	for (int i = 0; i < village->numBuildings; ++i) {
		buildings[i] = village->buildings[i];
	}
	free(village->buildings);
	village->maxBuildings = max;
	village->buildings = buildings;
}

void removeVillager(Village* village) {
	if (village->population <= 0) return;
	village->population--;
	Villager* v = village->villagers[village->population];

	if (v->age >= ADULT_AGE) {
		village->adults--;
	} else {
		village->children--;
	}

	village->workers[v->job]--;
	village->villagers[village->population] = NULL;
}

void addJob(Village* village, enum Job job) {
	for (int i = 0; i < village->population; ++i) {
		if (village->villagers[i]->job == Unemployed) {
			village->villagers[i]->job = job;
			return;
		}
	}
}