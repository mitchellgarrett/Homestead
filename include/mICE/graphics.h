#ifndef M_ICE_GRAPHCS
#define M_ICE_GRAPHICS

void drawLine(int xi, int yi, int xf, int yf, unsigned long c);
void drawLineHorizontal(int y, int xi, int xf, unsigned long c);
void drawLineVertical(int x, int yi, int yf, unsigned long c);

void fillBackground(unsigned long c);
void drawBox(int x, int y, int width, int height, unsigned long c);
void drawBoxFill(int x, int y, int width, int height, unsigned long c);
void drawBoxFillBorder(int x, int y, int width, int height, unsigned long border, unsigned long fill);

void drawCircle(int x, int y, int r, unsigned long c);
void drawCircleFill(int x, int y, int r, unsigned long c);
void drawCircleFillBorder(int x, int y, int r, unsigned long border, unsigned long fill);

#endif
