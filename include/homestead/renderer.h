#ifndef HOMESTEAD_RENDERER
#define HOMESTEAD_RENDERER

void drawMap(struct Map* map);
void drawTree(int x, int y);
void drawSilo(int x, int y);
void drawFarm(int x, int y);
void drawHouse(int x, int y);
void drawBuilding(struct Building* building);
void drawVillage(struct Village* village);

#endif
