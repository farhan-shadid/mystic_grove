#pragma once
#include <math.h>
#include <stdlib.h>

extern double playerX;
extern double playerY;
extern int gameState;
extern bool isTotemSolved;

const int PORTAL3_ROWS = 25;
const int PORTAL3_COLS = 25;
const int PORTAL3_TILE = 40;

// 0 = Grass Path
// 1 = Scattered Forest Tree 
// 2 = Rock Totem NPC 
int portal3Map[PORTAL3_ROWS][PORTAL3_COLS] = {
	{ 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0 },
	{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
	{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0 },
	{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0 },
	{ 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
	{ 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
	{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1 },
	{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0 },
	{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
	{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
	{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
	{ 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0 }
};

inline bool isPortal3Solid(double x, double y) {
	int col = (int)(x / PORTAL3_TILE);
	int row = PORTAL3_ROWS - 1 - (int)(y / PORTAL3_TILE);

	if (row < 0 || row >= PORTAL3_ROWS || col < 0 || col >= PORTAL3_COLS) return true;

	return (portal3Map[row][col] == 1 || portal3Map[row][col] == 2);
}

void drawPortal3Map() {
	for (int row = 0; row < PORTAL3_ROWS; row++) {
		for (int col = 0; col < PORTAL3_COLS; col++) {
			int x = col * PORTAL3_TILE;
			int y = (PORTAL3_ROWS - 1 - row) * PORTAL3_TILE;

			if ((row + col) % 2 == 0) iSetColor(34, 139, 34);
			else iSetColor(50, 205, 50);
			iFilledRectangle(x, y, PORTAL3_TILE, PORTAL3_TILE);

			int tileType = portal3Map[row][col];

			if (tileType == 1) {
				iSetColor(139, 69, 19);
				iFilledRectangle(x + 15, y, 10, 20);
				iSetColor(0, 100, 0);
				iFilledCircle(x + 20, y + 25, 16);
				iSetColor(34, 139, 34);
				iFilledCircle(x + 20, y + 30, 10);
			}
			else if (tileType == 2) {
				//Totem
				iSetColor(120, 120, 125);
				iFilledRectangle(x + 4, y + 4, 32, 40);
				iSetColor(100, 100, 105);
				iFilledCircle(x + 20, y + 44, 16);

				// The Face
				iSetColor(30, 30, 30);
				iFilledCircle(x + 13, y + 32, 3);
				iFilledCircle(x + 27, y + 32, 3);
				iFilledRectangle(x + 15, y + 18, 10, 4);

				// Quest marker
				if (!isTotemSolved) {
					
					iSetColor(255, 215, 0);
					iFilledRectangle(x + 18, y + 60, 4, 12);
					iFilledCircle(x + 20, y + 55, 2.5);
				}
			}
		}
	}
}

