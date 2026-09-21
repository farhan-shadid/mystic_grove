#pragma once
#include <math.h> 
#include <stdlib.h>

extern double playerX;
extern double playerY;
extern int gameState;

const int PORTAL2_ROWS = 25;
const int PORTAL2_COLS = 25;
const int PORTAL2_TILE = 40;

// 0 = Path, 1 = Metallic Block, 2 = Cloud Barrier, 3 = Crystal Goal
int portal2Map[PORTAL2_ROWS][PORTAL2_COLS] = {
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 1, 1, 0, 0, 2, 2, 0, 0, 1, 0, 0, 0, 1, 0, 0, 2, 2, 0, 0, 1, 1, 0, 2 },
	{ 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 0, 2 },
	{ 2, 0, 0, 0, 0, 2, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 0, 0, 0, 0, 2 },
	{ 2, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 2, 0, 2, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2 },
	{ 2, 0, 0, 0, 1, 1, 0, 0, 2, 0, 0, 1, 0, 1, 0, 0, 2, 0, 0, 1, 1, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 1, 0, 0, 0, 2, 2, 0, 0, 1, 0, 0, 0, 1, 0, 0, 2, 2, 0, 0, 0, 1, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 2 },
	{ 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2 },
	{ 2, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2 },
	{ 2, 0, 2, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 2, 0, 2 },
	{ 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }
};

inline bool isPortal2Solid(double x, double y) {
	int col = (int)(x / PORTAL2_TILE);
	int row = PORTAL2_ROWS - 1 - (int)(y / PORTAL2_TILE);

	if (row < 0 || row >= PORTAL2_ROWS || col < 0 || col >= PORTAL2_COLS) return true;

	int tile = portal2Map[row][col];
	return (tile == 1 || tile == 2);
}


const int NUM_PORTAL2_DRONES = 8;

struct Portal2Drone {
	double x, y;
	double speed;
	int direction;
	double minX, maxX;
	double bulletX, bulletY;
	double bulletVx, bulletVy;
	int bulletActive;
};

Portal2Drone portal2Drones[NUM_PORTAL2_DRONES];

void initPortal2Drones() {
	
	portal2Drones[0] = { 120.0, (double)((PORTAL2_ROWS - 1 - 1) * PORTAL2_TILE), 2.0, 1, 40.0, 400.0, 0.0, 0.0, 0.0, 0.0, 0 };
	portal2Drones[1] = { 520.0, (double)((PORTAL2_ROWS - 1 - 5) * PORTAL2_TILE), 2.5, -1, 400.0, 720.0, 0.0, 0.0, 0.0, 0.0, 0 };
	portal2Drones[2] = { 320.0, (double)((PORTAL2_ROWS - 1 - 8) * PORTAL2_TILE), 1.8, 1, 200.0, 560.0, 0.0, 0.0, 0.0, 0.0, 0 };
	portal2Drones[3] = { 600.0, (double)((PORTAL2_ROWS - 1 - 11) * PORTAL2_TILE), 2.2, -1, 480.0, 840.0, 0.0, 0.0, 0.0, 0.0, 0 };
	portal2Drones[4] = { 160.0, (double)((PORTAL2_ROWS - 1 - 13) * PORTAL2_TILE), 2.0, 1, 80.0, 440.0, 0.0, 0.0, 0.0, 0.0, 0 };
	portal2Drones[5] = { 400.0, (double)((PORTAL2_ROWS - 1 - 16) * PORTAL2_TILE), 2.4, -1, 280.0, 680.0, 0.0, 0.0, 0.0, 0.0, 0 };
	portal2Drones[6] = { 240.0, (double)((PORTAL2_ROWS - 1 - 19) * PORTAL2_TILE), 1.9, 1, 120.0, 480.0, 0.0, 0.0, 0.0, 0.0, 0 };
	portal2Drones[7] = { 580.0, (double)((PORTAL2_ROWS - 1 - 22) * PORTAL2_TILE), 2.1, -1, 360.0, 800.0, 0.0, 0.0, 0.0, 0.0, 0 };
}

void shootPortal2DroneBullets() {
	for (int i = 0; i < NUM_PORTAL2_DRONES; i++) {
		if (portal2Drones[i].bulletActive == 0) {
			portal2Drones[i].bulletActive = 1;
			portal2Drones[i].bulletX = portal2Drones[i].x + (PORTAL2_TILE / 2) - 4;
			portal2Drones[i].bulletY = portal2Drones[i].y + (PORTAL2_TILE / 2) - 4;

			int dirChoice = rand() % 4;
			double projSpeed = 4.5;

			if (dirChoice == 0)      { portal2Drones[i].bulletVx = 0.0;        portal2Drones[i].bulletVy = -projSpeed; }
			else if (dirChoice == 1) { portal2Drones[i].bulletVx = 0.0;        portal2Drones[i].bulletVy = projSpeed; }
			else if (dirChoice == 2) { portal2Drones[i].bulletVx = -projSpeed; portal2Drones[i].bulletVy = 0.0; }
			else                     { portal2Drones[i].bulletVx = projSpeed;  portal2Drones[i].bulletVy = 0.0; }
		}
	}
}

void updatePortal2Drones() {
	for (int i = 0; i < NUM_PORTAL2_DRONES; i++) {

		double nextX = portal2Drones[i].x + (portal2Drones[i].speed * portal2Drones[i].direction);

		if (nextX <= portal2Drones[i].minX || nextX >= portal2Drones[i].maxX ||
			isPortal2Solid(nextX, portal2Drones[i].y + 20) || isPortal2Solid(nextX + 30, portal2Drones[i].y + 20)) {
			portal2Drones[i].direction *= -1;
		}
		else {
			portal2Drones[i].x = nextX;
		}

		if (portal2Drones[i].bulletActive == 1) {
			portal2Drones[i].bulletX += portal2Drones[i].bulletVx;
			portal2Drones[i].bulletY += portal2Drones[i].bulletVy;

			if (portal2Drones[i].bulletX < 0 || portal2Drones[i].bulletX > 1000 ||
				portal2Drones[i].bulletY < 0 || portal2Drones[i].bulletY > 1000 ||
				isPortal2Solid(portal2Drones[i].bulletX, portal2Drones[i].bulletY)) {
				portal2Drones[i].bulletActive = 0;
			}
		}

		if (gameState == 6) {
			// Player vs Drone Body Collision
			if ((playerX - 12.0 < portal2Drones[i].x + 36.0) &&
				(playerX + 12.0 > portal2Drones[i].x + 4.0) &&
				(playerY < portal2Drones[i].y + 32.0) &&
				(playerY + 50.0 > portal2Drones[i].y + 8.0)) {

				// THE GATEKEEPER
				if (playerIFrames == 0) {
					playerHealth -= 1;
					playerIFrames = 60; // Grant immunity 

					if (playerHealth <= 0) {
						gameState = 0;
						playerHealth = maxHealth; 
					}

					
					playerX = 500.0;
					playerY = 60.0;
				}
			}

			// Player vs Drone Bullet 
			if (portal2Drones[i].bulletActive == 1) {
				if ((playerX - 12.0 < portal2Drones[i].bulletX + 8.0) &&
					(playerX + 12.0 > portal2Drones[i].bulletX) &&
					(playerY < portal2Drones[i].bulletY + 8.0) &&
					(playerY + 50.0 > portal2Drones[i].bulletY)) {

					// THE GATEKEEPER
					if (playerIFrames == 0) {
						playerHealth -= 1;
						playerIFrames = 60; // Grant spawn immunity 

						if (playerHealth <= 0) {
							gameState = 0;
							playerHealth = maxHealth; 
						}

						playerX = 500.0;
						playerY = 60.0;
						portal2Drones[i].bulletActive = 0;
					}
				}
			}
		}
	}
}

void drawPortal2Drones() {
	for (int i = 0; i < NUM_PORTAL2_DRONES; i++) {
		double dx = portal2Drones[i].x;
		double dy = portal2Drones[i].y;

		iSetColor(50, 55, 65);
		iFilledRectangle(dx + 6, dy + 12, 28, 18);
		iSetColor(20, 20, 20);
		iRectangle(dx + 6, dy + 12, 28, 18);

		iSetColor(255, 69, 0);
		iFilledRectangle(dx + 14, dy + 18, 12, 6);

		iSetColor(100, 100, 100);
		iFilledRectangle(dx + 10, dy + 6, 6, 6);
		iFilledRectangle(dx + 24, dy + 6, 6, 6);

		if (portal2Drones[i].bulletActive == 1) {
			iSetColor(255, 120, 0);
			iFilledRectangle(portal2Drones[i].bulletX, portal2Drones[i].bulletY, 8, 8);
		}
	}
}

void drawPortal2Map() {
	for (int row = 0; row < PORTAL2_ROWS; row++) {
		for (int col = 0; col < PORTAL2_COLS; col++) {
			int x = col * PORTAL2_TILE;
			int y = (PORTAL2_ROWS - 1 - row) * PORTAL2_TILE;

			if ((row + col) % 2 == 0) iSetColor(70, 130, 180);
			else iSetColor(100, 149, 237);

			iFilledRectangle(x, y, PORTAL2_TILE, PORTAL2_TILE);

			int tileType = portal2Map[row][col];

			if (tileType == 1) { // Metallic Block
				iSetColor(105, 105, 105);
				iFilledRectangle(x + 2, y + 2, 36, 36);
				iSetColor(169, 169, 169);
				iFilledRectangle(x + 6, y + 6, 28, 28);
			}
			else if (tileType == 2) { // Cloud Barrier
				iSetColor(220, 230, 242);
				iFilledEllipse(x + 20, y + 20, 18, 14);
				iSetColor(255, 255, 255);
				iFilledEllipse(x + 20, y + 22, 14, 10);
			}
			else if (tileType == 3) { // Basic Crystal Goal
				double dx = (double)x;
				double dy = (double)y;

				iSetColor(139, 0, 0);
				double outerX[] = { dx + 20.0, dx + 32.0, dx + 20.0, dx + 8.0 };
				double outerY[] = { dy + 35.0, dy + 20.0, dy + 5.0, dy + 20.0 };
				iFilledPolygon(outerX, outerY, 4);

				iSetColor(255, 50, 50);
				double innerX[] = { dx + 20.0, dx + 26.0, dx + 20.0, dx + 14.0 };
				double innerY[] = { dy + 29.0, dy + 20.0, dy + 11.0, dy + 20.0 };
				iFilledPolygon(innerX, innerY, 4);
			}
		}
	}
	drawPortal2Drones();
}