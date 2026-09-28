#pragma once
#include <math.h> 
#ifndef PORTAL1_SPAWN_X
#define PORTAL1_SPAWN_X 500.0
#define PORTAL1_SPAWN_Y 100.0
#endif

extern double playerX;
extern double playerY;
extern int gameState;
extern int slimeImg;
extern int slimeBulletImg;
extern int imgPortal1Map;
extern int bookImg;



const int PORTAL_ROWS = 25;
const int PORTAL_COLS = 25;
const int PORTAL_TILE = 40;

// 0 = Walkable Grass, 1 = Border Trees / Stone Pillars, 2 = Bushes, 3 = Spell Book
int portalMap[PORTAL_ROWS][PORTAL_COLS] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // Row 0 (Y: 960-1000)
	{ 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 }, // Row 1 (Y: 920-960)
	{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 }, // Row 2 (Y: 880-920, Lowered Book)
	{ 1, 1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 1, 1, 1 }, // Row 3 (Y: 840-880, Top 1st Slime Lane)
	{ 1, 1, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 1, 1, 1 }, // Row 4 (Y: 800-840, 3 Top Bushes 2x2)
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 }, // Row 5 (Y: 760-800)
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1 }, // Row 6 (Y: 720-760, Clear lane from Left Trees to Pillar)
	{ 1, 1, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1, 0, 0, 0, 1, 1, 1 }, // Row 7 (Y: 680-720, Top half of the 2 Bushes + Pillar)
	{ 1, 1, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1, 0, 0, 0, 1, 1, 1 }, // Row 8 (Y: 640-680, Bottom half of the 2 Bushes + Pillar)
	{ 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 }, // Row 9 (Y: 600-640, Mid Slime Lane)
	{ 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1 }, // Row 10 (Y: 560-600, Left Pillar + Right Bush)
	{ 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1 }, // Row 11 (Y: 520-560, Bottom 2nd Slime Lane)
	{ 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 }, // Row 12 (Y: 480-520, Center Bush 3x2)
	{ 1, 1, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 1, 1, 1 }, // Row 13 (Y: 440-480, Lower-Mid Bushes 2x2)
	{ 1, 1, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 1, 1, 1 }, // Row 14 (Y: 400-440, Bottom 1st Slime Lane)
	{ 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 }, // Row 15 (Y: 360-400, Bottom Pillars Top)
	{ 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 }, // Row 16 (Y: 320-360, Bottom-Center Bush)
	{ 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 }, // Row 17 (Y: 280-320, Bottom-Center Bush)
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1 }, // Row 18 (Y: 240-280, Bottom-Right Pillar Top)
	{ 1, 1, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1 }, // Row 19 (Y: 200-240, Bottom-Left Bush)
	{ 1, 1, 1, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 2, 2, 1, 1 }, // Row 20 (Y: 160-200, Bottom Bushes + Pillar)
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1 }, // Row 21 (Y: 120-160)
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 }, // Row 22 (Y: 80-120, Player Spawn Area)
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // Row 23 (Y: 40-80)
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }  // Row 24 (Y: 0-40)
};

bool spellCollected = false;
int speedBoostTimer = 0;
double defaultPlayerSpeed = 4.0;
double currentPlayerSpeed = 4.0;

void updatePortalSpell() {
	if (gameState != 5 || spellCollected) return;

	double bookX = 468.0;
	double bookY = 865.0;
	double bookSize = 65.0;

	// Player Collision Check
	if ((playerX + 12.0 > bookX) &&
		(playerX - 12.0 < bookX + bookSize) &&
		(playerY + 50.0 > bookY) &&
		(playerY < bookY + bookSize)) {

		portalMap[2][12] = 0;
		spellCollected = true;
	}
}

inline bool isPortalSolid(double x, double y) {
	int col = (int)(x / PORTAL_TILE);
	int row = PORTAL_ROWS - 1 - (int)(y / PORTAL_TILE);

	if (row < 0 || row >= PORTAL_ROWS || col < 0 || col >= PORTAL_COLS) return true;

	int tile = portalMap[row][col];
	return (tile == 1 || tile == 2);
}

const int NUM_SLIMES = 5;

struct Slime {
	double x, y;
	double speed;
	int direction;
	double bulletX, bulletY;
	int bulletActive;
	int active;
};

Slime slimes[NUM_SLIMES];

void initPortalSlimes() {
	// 1. Top 1st Slime, patrols between Top-Left & Top-Mid Bush
	slimes[0] = { 240.0, (double)((PORTAL_ROWS - 1 - 3) * PORTAL_TILE), 2.0, 1, 0.0, 0.0, 0, 1 };

	// 2. Middle Slime, Bounces between Mid-Left Pillar (Col 4) and Right Trees (Col 22)
	slimes[1] = { 560.0, (double)((PORTAL_ROWS - 1 - 9) * PORTAL_TILE), 3.0, -1, 0.0, 0.0, 0, 1 };

	// 3. Bottom 2nd Slime, Initialized on the RIGHT (700.0); bounces off Center Bush (Col 12)
	slimes[2] = { 700.0, (double)((PORTAL_ROWS - 1 - 11) * PORTAL_TILE), 1.8, -1, 0.0, 0.0, 0, 1 };

	// 4. Bottom 1st Slime (Lowest), bounces between Lower-Left & Lower-Right bushes
	slimes[3] = { 380.0, (double)((PORTAL_ROWS - 1 - 14) * PORTAL_TILE), 2.5, 1, 0.0, 0.0, 0, 1 };

	// 5. Top 2nd Slime (Row 6, Y = 720): Initialized from the LEFT (120.0)
	slimes[4] = { 120.0, (double)((PORTAL_ROWS - 1 - 6) * PORTAL_TILE), 2.0, 1, 0.0, 0.0, 0, 1 };
}
void shootSlimeBullets() {
	for (int i = 0; i < NUM_SLIMES; i++) {
		if (slimes[i].active == 1 && slimes[i].bulletActive == 0) {
			slimes[i].bulletActive = 1;

			slimes[i].bulletX = slimes[i].x + 8.0;

			slimes[i].bulletY = slimes[i].y - 20.0;
		}
	}
}

void updatePortalSlimes() {
	for (int i = 0; i < NUM_SLIMES; i++) {
		if (slimes[i].active == 0) {
			slimes[i].bulletActive = 0;
			continue;
		}

		double nextX = slimes[i].x + (slimes[i].speed * slimes[i].direction);

		// Check the true outer edges (-15 left, +55 right) of the 85x85 slime sprite
		if (isPortalSolid(nextX - 15.0, slimes[i].y + 20.0) || isPortalSolid(nextX + 55.0, slimes[i].y + 20.0)) {
			slimes[i].direction *= -1;
		}
		else {
			slimes[i].x = nextX;
		}

		if (slimes[i].bulletActive == 1) {
			slimes[i].bulletY -= 5.0;

			if (slimes[i].bulletY < 0 || isPortalSolid(slimes[i].bulletX, slimes[i].bulletY)) {
				slimes[i].bulletActive = 0;
			}
		}

		// COLLISIONS
		if (gameState == 5) {
			// Player x Slime 
			if (playerIFrames == 0) {
				if ((playerX - 12.0 < slimes[i].x + 55.0) &&
					(playerX + 12.0 > slimes[i].x - 15.0) &&
					(playerY < slimes[i].y + 55.0) &&
					(playerY + 50.0 > slimes[i].y - 15.0)) {

					playerHealth -= 1;
					playerIFrames = 60;
					playerX = PORTAL1_SPAWN_X;
					playerY = PORTAL1_SPAWN_Y;
				}
			}

			// Player x Bullet
			if (slimes[i].bulletActive == 1 && playerIFrames == 0) {
				if ((playerX - 12.0 < slimes[i].bulletX + 24.0) &&
					(playerX + 12.0 > slimes[i].bulletX) &&
					(playerY < slimes[i].bulletY + 24.0) &&
					(playerY + 50.0 > slimes[i].bulletY)) {

					playerHealth -= 1;
					playerIFrames = 60;
					playerX = PORTAL1_SPAWN_X;
					playerY = PORTAL1_SPAWN_Y;
					slimes[i].bulletActive = 0;
				}
			}
		}
	}
}

void drawPortalSlimes() {
	for (int i = 0; i < NUM_SLIMES; i++) {
		if (slimes[i].active == 1) {
			if (slimes[i].bulletActive == 1 && slimeBulletImg != -1) {
				iShowImage(slimes[i].bulletX, slimes[i].bulletY, 24, 24, slimeBulletImg);
			}

			if (slimeImg != -1) {
				iShowImage(slimes[i].x - 22.5, slimes[i].y - 22.5, 85, 85, slimeImg);
			}
		}
	}
}
void drawPortal1Map() {
	if (imgPortal1Map != -1) {
		iShowImage(0, 0, PORTAL_COLS * PORTAL_TILE, PORTAL_ROWS * PORTAL_TILE, imgPortal1Map);
	}

	if (!spellCollected && bookImg != -1) {
		iShowImage(468, 865, 65, 65, bookImg);
	}

	drawPortalSlimes();
}

