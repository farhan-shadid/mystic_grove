#pragma once
#include <math.h> 
#include <stdlib.h>
#ifndef PORTAL2_SPAWN_X
#define PORTAL2_SPAWN_X 500.0
#define PORTAL2_SPAWN_Y 100.0
#endif
extern double playerX;
extern double playerY;
extern int gameState;
extern int playerIFrames;
extern int playerHealth;
extern int maxHealth;
// External image handles for the 5 drone variations (to be loaded in main.cpp)
extern int imgPortal2Drones[5];

// External image handle for the full map background (to be loaded in main.cpp)
extern int imgPortal2Map;

const int PORTAL2_ROWS = 25;
const int PORTAL2_COLS = 25;
const int PORTAL2_TILE = 40;

// ================= SPEED BOOSTER =================

// ================= SPEED BOOSTERS =================

const int NUM_SPEED_BOOSTERS = 3;

double normalMoveSpeed = 1.2;
double moveSpeed = 1.2;

const double BOOSTED_SPEED = 2.4;

const int SPEED_BOOST_DURATION = 5000;

double boosterX[NUM_SPEED_BOOSTERS] = {
	220.0,  // Booster 1
	500.0,  // Booster 2
	880.0   // Booster 3
};

double boosterY[NUM_SPEED_BOOSTERS] = {
	700.0,
	500.0,
	280.0
};

bool speedBoosterActive[NUM_SPEED_BOOSTERS] = {
	true, true, true
};

bool speedBoosted = false;

int speedBoostTime = 0;


// 0 = Path, 1 = Metallic Block, 2 = Cloud Barrier, 3 = Crystal Goal
int portal2Map[PORTAL2_ROWS][PORTAL2_COLS] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1 },
	{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
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
	int droneImageIndex; // Stores which of the 5 images this drone uses
};

Portal2Drone portal2Drones[NUM_PORTAL2_DRONES];

bool waterBallActive[NUM_PORTAL2_DRONES] = { false };
double waterBallX[NUM_PORTAL2_DRONES] = { 0 };
double waterBallY[NUM_PORTAL2_DRONES] = { 0 };


void initPortal2Drones() {
	int droneImages[NUM_PORTAL2_DRONES] =
	{ 0, 1, 2, 0, 2, 4, 1, 2 };

	// Drone 0 - Row 7, continuous 0 area
	portal2Drones[0] =
	{ 200.0, (double)((PORTAL2_ROWS - 1 - 7) * PORTAL2_TILE),
	2.0, 1, 100.0, 760.0,
	0.0, 0.0, 0.0, 0.0, 0, droneImages[0] };

	// Drone 1 - ENEMY 2
	// Row 10, right-side continuous 0 area
	portal2Drones[1] =
	{ 700.0, (double)((PORTAL2_ROWS - 1 - 10) * PORTAL2_TILE),
	2.5, -1, 600.0, 800.0,
	0.0, 0.0, 0.0, 0.0, 0, droneImages[1] };

	// Drone 2 - ENEMY 3
	// Row 13, large continuous 0 area
	portal2Drones[2] =
	{ 500.0, (double)((PORTAL2_ROWS - 1 - 13) * PORTAL2_TILE),
	1.8, 1, 220.0, 800.0,
	0.0, 0.0, 0.0, 0.0, 0, droneImages[2] };

	// Drone 3 - Row 14
	portal2Drones[3] =
	{ 500.0, (double)((PORTAL2_ROWS - 1 - 14) * PORTAL2_TILE),
	2.2, -1, 220.0, 800.0,
	0.0, 0.0, 0.0, 0.0, 0, droneImages[3] };

	// Drone 4 - Row 18
	// Only the middle continuous 0 area
	portal2Drones[4] =
	{ 560.0, (double)((PORTAL2_ROWS - 1 - 18) * PORTAL2_TILE),
	2.0, 1, 440.0, 720.0,
	0.0, 0.0, 0.0, 0.0, 0, droneImages[4] };

	// Drone 5 - Row 19
	portal2Drones[5] =
	{ 600.0, (double)((PORTAL2_ROWS - 1 - 19) * PORTAL2_TILE),
	2.4, -1, 480.0, 840.0,
	0.0, 0.0, 0.0, 0.0, 0, droneImages[5] };

	// Drone 6 - Row 20
	portal2Drones[6] =
	{ 600.0, (double)((PORTAL2_ROWS - 1 - 20) * PORTAL2_TILE),
	1.9, 1, 480.0, 760.0,
	0.0, 0.0, 0.0, 0.0, 0, droneImages[6] };

	// Drone 7 - Row 6
	portal2Drones[7] =
	{ 400.0, (double)((PORTAL2_ROWS - 1 - 6) * PORTAL2_TILE),
	2.1, -1, 100.0, 760.0,
	0.0, 0.0, 0.0, 0.0, 0, droneImages[7] };
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


					playerX = PORTAL2_SPAWN_X;
					playerY = PORTAL2_SPAWN_Y;
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



						playerX = PORTAL2_SPAWN_X;
						playerY = PORTAL2_SPAWN_Y;
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
		int imgIndex = portal2Drones[i].droneImageIndex;

		// Draw the randomly assigned drone image
		iShowImage((int)dx, (int)dy, PORTAL2_TILE, PORTAL2_TILE, imgPortal2Drones[imgIndex]);

		// Keep bullet rendering untouched
		if (portal2Drones[i].bulletActive == 1) {
			iSetColor(255, 120, 0);
			iFilledRectangle(portal2Drones[i].bulletX, portal2Drones[i].bulletY, 8, 8);
		}
	}
}

void drawPortal2Map() {
	// Draw the full background image covering the entire map area (e.g., 1000x1000 pixels)


	for (int row = 0; row < PORTAL2_ROWS; row++) {
		for (int col = 0; col < PORTAL2_COLS; col++) {
			int x = col * PORTAL2_TILE;
			int y = (PORTAL2_ROWS - 1 - row) * PORTAL2_TILE;

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
	iShowImage(0, 0, PORTAL2_COLS * PORTAL2_TILE, PORTAL2_ROWS * PORTAL2_TILE, imgPortal2Map);
	drawPortal2Drones();
}
// ================= DRAW SPEED BOOSTER =================
// ================= DRAW SPEED BOOSTER =================

// ================= DRAW SPEED BOOSTERS =================

void drawSpeedBoosters()
{
	for (int i = 0; i < NUM_SPEED_BOOSTERS; i++)
	{
		if (!speedBoosterActive[i])
			continue;

		iSetColor(0, 255, 255);
		iFilledCircle(boosterX[i], boosterY[i], 15);

		iSetColor(255, 255, 255);
		iCircle(boosterX[i], boosterY[i], 20);

		iSetColor(255, 255, 0);

		if (i == 0)
			iText(boosterX[i] - 35, boosterY[i] + 25, "SPEED 1");
		else if (i == 1)
			iText(boosterX[i] - 35, boosterY[i] + 25, "SPEED 2");
		else
			iText(boosterX[i] - 35, boosterY[i] + 25, "SPEED 3");
	}
}


// ================= CHECK SPEED BOOSTERS =================

void checkSpeedBooster()
{
	for (int i = 0; i < NUM_SPEED_BOOSTERS; i++)
	{
		if (!speedBoosterActive[i])
			continue;

		double playerCenterX = playerX;
		double playerCenterY = playerY + 25.0;

		double dx = playerCenterX - boosterX[i];
		double dy = playerCenterY - boosterY[i];

		if (dx * dx + dy * dy < 35.0 * 35.0)
		{
			speedBoosterActive[i] = false;

			speedBoosted = true;
			moveSpeed = BOOSTED_SPEED;

			speedBoostTime = SPEED_BOOST_DURATION;
		}
	}
}


// ================= UPDATE SPEED BOOSTER =================

void updateSpeedBooster()
{
	if (!speedBoosted)
		return;

	speedBoostTime -= 16;

	if (speedBoostTime <= 0)
	{
		speedBoosted = false;
		speedBoostTime = 0;

		moveSpeed = normalMoveSpeed;
	}
}