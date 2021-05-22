#ifndef HOMESTEAD_VILLAGE
#define HOMESTEAD_VILLAGE
#include <homestead/villager.h>

typedef struct Village {

	struct Map* map;
	struct Calendar* calendar;

	int gold;

	int food;
	int maxFood;

	int population;
	int maxPopulation;
	struct Villager** villagers;

	int numBuildings;
	int maxBuildings;
	struct Building** buildings;

	int wood;
	int maxWood;

	int stone;
	int maxStone;

	int children;
	int adults;
	int workers[NUM_JOBS];
	int maxWorkers[NUM_JOBS];

} Village;

Village* newVillage();
void villageUpdate(Village* village);
void placeBuilding(Village* village, enum BuildingType type, int x, int y);
void setMaxVillagers(Village* village, int max);
void setMaxBuildings(Village* village, int max);
void removeVillager(Village* village);
void addJob(Village* village, enum Job job);

#endif
