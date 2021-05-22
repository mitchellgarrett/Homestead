#ifndef HOMESTEAD_VILLAGER
#define HOMESTEAD_VILLAGER

#define ADULT_AGE 60
#define NUM_JOBS 5

typedef enum Job { Unemployed, Farmer, Logger, Miner, Fisherman } Job;
char* job_names[];

typedef struct Villager {
	struct Village* village;
	int age;
	Job job;
} Villager;

Villager* newVillager();

#endif
