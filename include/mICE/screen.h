#ifndef M_ICE_SCREEN
#define M_ICE_SCREEN

void initScreen();
void closeScreen();
void clearScreen();
void refreshScreen();

int screenWidth();
int screenHeight();
void setScreenSize(int width, int height);
void setScreenTitle(const char* s);

// 0 No cursor
// 1 Small cursor
// 2 Big cursor
void setCursor(int cursor);
void moveCursor(int x, int y);

int getKey();
int getcat(int x, int y);
void flashScreen();

void printc(unsigned long c);
void printcat(int x, int y, unsigned long c);

void prints(const unsigned long* s);
void printsat(int x, int y, const unsigned long* s);

void printsf(const char* fmt, ...);
void printsfat(int x, int y, const char* fmt, ...);

#endif
