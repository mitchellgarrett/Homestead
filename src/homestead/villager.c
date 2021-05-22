#include <homestead/villager.h>

char* job_names[] = { "Unemployed", "Farmers", "Loggers", "Miners", "Fishermen" };

Villager* newVillager() {
	Villager* villager = (Villager*)malloc(sizeof(Villager));
	villager->age = 0;
	villager->job = Unemployed;
	return villager;
}