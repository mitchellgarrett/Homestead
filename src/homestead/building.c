#include <homestead/building.h>
#include <stdlib.h>

// House, Farm, FishingHut, Mine, LoggingCamp, Silo, Warehouse
Building building_prototypes[] = { 
	{ NULL, House, "House", 0, 0, 4, 3, 0, 5, 5, 0 },
	{ NULL, Farm, "Farm", 0, 0, 5, 5, 0, 5, 5, 5 },
	{ NULL, Silo, "Silo", 0, 0, 2, 4, 0, 15, 10, 10 },
	{ NULL, Mine, "Mine", 0, 0, 4, 3, 0, 1, 10, 0 },
	{ NULL, LoggingCamp, "Logging Camp", 0, 0, 4, 3, 0, 2, 0, 10 },
	{ NULL, Warehouse, "Warehouse", 0, 0, 4, 3, 0, 25, 10, 10 },
	{ NULL, FishingHut, "Fishing Hut", 0, 0, 4, 3, 0, 2, 15, 5 }
};

Building* newBuilding(BuildingType type) {
	Building* building = (Building*)malloc(sizeof(Building));
	memcpy(building, &building_prototypes[type], sizeof(Building));
	return building;
}