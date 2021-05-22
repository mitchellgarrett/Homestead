#ifndef HOMESTEAD_SAVE_LOAD
#define HOMESTEAD_SAVE_LOAD

#define SAVE_FILE "data/save.dat"
#define MANUAL_FILE "data/manual.txt"

int saveVillage(struct Village* village);
int loadVillage(struct Village* village);

#endif
