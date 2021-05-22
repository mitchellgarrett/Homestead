#ifndef HOMESTEAD_MENU
#define HOMESTEAD_MENU

int map_offset_x;
int map_offset_y;

int cursor_x;
int cursor_y;

void quit();
void newGame();
void loadGame();
void manual();
void mainMenu();
void printHUD(struct Village* village);
void clearMenu();
void buildingMenu(struct Village* village);
void villagerMenu(struct Village* village);
void printTitle();

#endif
