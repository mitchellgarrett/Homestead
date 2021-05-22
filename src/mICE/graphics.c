#include <mICE/graphics.h>
#include <mICE/screen.h>
#include <stdlib.h>

#ifdef _WIN32
#define PDC_WIDE
#include <pdcurses/curses.h>
#else
// Use ncurses
#endif

// Bresenham's line drawing algorithm
void drawLine(int xi, int yi, int xf, int yf, unsigned long c) {
	int dx = abs(xf - xi);
	int sx = xi < xf ? 1 : -1;

	int dy = -abs(yf - yi);
	int sy = yi < yf ? 1 : -1;

	int e = dx + dy;
	int e2;
	int x = xi;
	int y = yi;
	while (1) {
		printcat(x, y, c);
		if (x == xf && y == yf) break;
		e2 = 2 * e;
		if (e2 >= dy) {
			e += dy;
			x += sx;
		}
		if (e2 <= dx) {
			e += dx;
			y += sy;
		}
	}
}

void drawLineHorizontal(int y, int xi, int xf, unsigned long c) {
	int x = xi;
	int dx = xi < xf ? 1 : -1;
	xf += dx;
	while (x != xf) {
		printcat(x, y, c);
		x += dx;
	}
}

void drawLineVertical(int x, int yi, int yf, unsigned long c) {
	int y = yi;
	int dy = yi < yf ? 1 : -1;
	yf += dy;
	while (y != yf) {
		printcat(x, y, c);
		y += dy;
	}
}

void fillBackground(unsigned long c) {
	/*if (c <= 255) {
		bkgd(c);
	} else {
		bkgrnd(c);
	}*/
	drawBoxFill(0, 0, screenWidth(), screenHeight(), c);
}

void drawBox(int x, int y, int width, int height, unsigned long c) {
	int xf = x + width - 1;
	int yf = y + height - 1;
	drawLineHorizontal(y, x, xf, c);
	drawLineHorizontal(yf, x, xf, c);
	drawLineVertical(x, y, yf, c);
	drawLineVertical(xf, y, yf, c);
}

void drawBoxFill(int x, int y, int width, int height, unsigned long c) {
	/*unsigned long* line = (unsigned long*)malloc(width * sizeof(unsigned long));
	memset(line, c, width);

	int yf = y + height;
	for (; y < yf; ++y) {
		printsat(x, y, line);
	}
	free(line);*/
	int xi = x;
	int xf = x + width;
	int yf = y + height;
	for (; y < yf; ++y) {
		for (x = xi; x < xf; ++x) {
			printcat(x, y, c);
		}
	}
}

void drawBoxFillBorder(int x, int y, int width, int height, unsigned long border, unsigned long fill) {
	drawBox(x, y, width, height, border);
	drawBoxFill(x + 1, y + 1, width - 2, height - 2, fill);
}

// TODO
void drawCircle(int x, int y, int r, unsigned long c) {
	int cx = 0;
	int cy = r;
	int d = 3 - 2 * r;

	printcat(x + cx, y + cy, c);
	printcat(x - cx, y + cy, c);
	printcat(x + cx, y - cy, c);
	printcat(x - cx, y - cy, c);
	printcat(x + cy, y + cx, c);
	printcat(x - cy, y + cx, c);
	printcat(x + cy, y - cx, c);
	printcat(x - cy, y - cx, c);

	while (y >= x) {
		x++;
		if (d > 0) {
			y--;
			d = d + 4 * (x - y) + 10;
		} else {
			d = d + 4 * x + 6;
		}

		printcat(x + cx, y + cy, c);
		printcat(x - cx, y + cy, c);
		printcat(x + cx, y - cy, c);
		printcat(x - cx, y - cy, c);
		printcat(x + cy, y + cx, c);
		printcat(x - cy, y + cx, c);
		printcat(x + cy, y - cx, c);
		printcat(x - cy, y - cx, c);
	}

}

// TODO
void drawCircleFill(int x, int y, int r, unsigned long c) {

}

void drawCircleFillBorder(int x, int y, int r, unsigned long border, unsigned long fill) {
	drawCircle(x, y, r, border);
	drawCircleFill(x, y, r - 1, fill);
}