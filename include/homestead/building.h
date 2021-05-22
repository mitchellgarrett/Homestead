#ifndef HOMESTEAD_BUILDING
#define HOMESTEAD_BUILDING

#define NUM_BUILDINGS 7
typedef enum BuildingType { House, Farm, Silo, Mine, LoggingCamp, Warehouse, FishingHut } BuildingType;

typedef struct Building {

	struct Village* village;
	BuildingType type;
	char* name;
	int x;
	int y;
	int width;
	int height;

	int workers;
	int maxWorkers;

	int woodCost;
	int stoneCost;

} Building;

struct Building building_prototypes[];

Building* newBuilding(BuildingType type);

#endif
