#pragma once
#include <math.h>
#include <stdlib.h>

extern double playerX;
extern double playerY;
extern int playerDirection;
extern int throwCooldown;
extern int gameState;
extern bool isTotemSolved;
extern int playerHealth;
extern int playerIFrames;
extern bool lightningCollected;

extern int imgPortal3FullMap;
extern int portal3EnemyImg;
extern int portal3Enemy2Img;
extern int portal3LightningImg; // Used for the spell pickup item
extern int blueFireballImg;   // Image for the blue fireball attack

const int PORTAL3_ROWS = 25;
const int PORTAL3_COLS = 25;
const int PORTAL3_TILE = 40;

int portal3Map[PORTAL3_ROWS][PORTAL3_COLS] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 0, 0, 0, 2, 2, 2, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 0, 0, 0, 2, 2, 2, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1 },
	{ 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

inline bool isPortal3Solid(double x, double y) {
	int col = (int)(x / PORTAL3_TILE);
	int row = PORTAL3_ROWS - 1 - (int)(y / PORTAL3_TILE);
	if (row < 0 || row >= PORTAL3_ROWS || col < 0 || col >= PORTAL3_COLS) return true;
	return (portal3Map[row][col] == 1 || portal3Map[row][col] == 2);
}

struct PortalEnemy {
	double x, y;
	double minX, maxX;
	double speed;
	int direction;
	bool alive;
};

struct PortalEnemy2 {
	double x, y;
	double minX, maxX;
	double speed;
	int direction;
	bool alive;
};

struct LightningSpell {
	double x, y;
	bool collected;
};

// BLUE FIREBALL STRUCTURE & POOL
struct BlueFireball {
	double x, y;
	double vx, vy;
	bool active;
};

const int MAX_BLUE_FIREBALLS = 3;
BlueFireball blueFireballs[MAX_BLUE_FIREBALLS];

PortalEnemy portalEnemies[2] = {
	{ (4.0 * 40.0) + 280.0, ((25 - 1 - 12) * 40.0) + 200.0, (4.0 * 40.0) + 280.0, (10.0 * 40.0) + 200.0, 1.0, 1, true },
	{ (4.0 * 40.0) + 280.0, ((25 - 1 - 13) * 40.0) + 160.0, (4.0 * 40.0) + 280.0, (10.0 * 40.0) + 160.0, 1.0, 1, true }
};

PortalEnemy2 portalEnemy2[2] = {
	{ 18.0 * 40.0, (25 - 1 - 15) * 40.0, 18.0 * 40.0, (18.0 * 40.0) + 70.0, 1.0, 1, true },
	{ 17.0 * 40.0, (25 - 1 - 13) * 40.0, 17.0 * 40.0, (17.0 * 40.0) + 70.0, 1.0, 1, true }
};

LightningSpell portalLightnings[1] = {
	{ 20.0 * 40.0, (25 - 1 - 18) * 40.0, false }
};

bool rightGateOpened = false;

// Helper to check if all enemies are defeated
inline bool areAllPortal3EnemiesDead() {
	for (int i = 0; i < 2; i++) {
		if (portalEnemies[i].alive) return false;
		if (portalEnemy2[i].alive) return false;
	}
	return true;
}

// Helper to check if player is near the top-right final boss portal (Columns 19-22, Rows 1-3)
inline bool isNearTopRightDoor(double x, double y) {
	return (x >= 19.0 * 40.0 && x <= 22.5 * 40.0 && y >= 19.0 * 40.0 && y <= 24.5 * 40.0);
}

inline void checkAndOpenRightGate() {
	if (rightGateOpened) return;

	if (areAllPortal3EnemiesDead()) {
		portal3Map[7][17] = 0;
		portal3Map[8][17] = 0;
		portal3Map[7][18] = 0;
		portal3Map[8][18] = 0;
		rightGateOpened = true;
	}
}

// THROW BLUE FIREBALL FUNCTION
inline void throwBlueFireball() {
	if (throwCooldown > 0) return;

	for (int i = 0; i < MAX_BLUE_FIREBALLS; i++) {
		if (!blueFireballs[i].active) {
			blueFireballs[i].active = true;
			blueFireballs[i].x = playerX + 20.0;
			blueFireballs[i].y = playerY + 20.0;

			double speed = 10.0;
			blueFireballs[i].vx = 0.0;
			blueFireballs[i].vy = 0.0;

			if (playerDirection == 3) blueFireballs[i].vy = speed;
			else if (playerDirection == 0) blueFireballs[i].vy = -speed;
			else if (playerDirection == 1) blueFireballs[i].vx = -speed;
			else if (playerDirection == 2) blueFireballs[i].vx = speed;

			throwCooldown = 20;
			break;
		}
	}
}

inline void updatePortal3Enemies() {
	if (throwCooldown > 0) throwCooldown--;

	// Update Blue Fireballs & Collisions with Enemies
	for (int i = 0; i < MAX_BLUE_FIREBALLS; i++) {
		if (blueFireballs[i].active) {
			blueFireballs[i].x += blueFireballs[i].vx;
			blueFireballs[i].y += blueFireballs[i].vy;

			// Screen boundary or map solidity check for projectiles
			if (blueFireballs[i].x < 0 || blueFireballs[i].x > PORTAL3_COLS * PORTAL3_TILE ||
				blueFireballs[i].y < 0 || blueFireballs[i].y > PORTAL3_ROWS * PORTAL3_TILE ||
				isPortal3Solid(blueFireballs[i].x, blueFireballs[i].y)) {
				blueFireballs[i].active = false;
			}

			// Check collision with PortalEnemy group 1
			for (int e = 0; e < 2; e++) {
				if (portalEnemies[e].alive) {
					double distX = blueFireballs[i].x - portalEnemies[e].x;
					double distY = blueFireballs[i].y - portalEnemies[e].y;
					if (sqrt(distX * distX + distY * distY) < 25.0) {
						portalEnemies[e].alive = false;
						blueFireballs[i].active = false;
					}
				}
			}

			// Check collision with PortalEnemy group 2
			for (int e = 0; e < 2; e++) {
				if (portalEnemy2[e].alive) {
					double distX = blueFireballs[i].x - portalEnemy2[e].x;
					double distY = blueFireballs[i].y - portalEnemy2[e].y;
					if (sqrt(distX * distX + distY * distY) < 25.0) {
						portalEnemy2[e].alive = false;
						blueFireballs[i].active = false;
					}
				}
			}
		}
	}

	for (int i = 0; i < 2; i++) {
		if (!portalEnemies[i].alive) continue;

		portalEnemies[i].x += portalEnemies[i].speed * portalEnemies[i].direction;

		if (portalEnemies[i].x >= portalEnemies[i].maxX) {
			portalEnemies[i].x = portalEnemies[i].maxX;
			portalEnemies[i].direction = -1;
		}
		else if (portalEnemies[i].x <= portalEnemies[i].minX) {
			portalEnemies[i].x = portalEnemies[i].minX;
			portalEnemies[i].direction = 1;
		}

		if (gameState == 7 && playerIFrames == 0) {
			double distX = playerX - portalEnemies[i].x;
			double distY = playerY - portalEnemies[i].y;
			double distance = sqrt(distX * distX + distY * distY);

			if (distance < 30.0) {
				playerHealth -= 2;
				if (playerHealth < 0) playerHealth = 0;
				playerIFrames = 60;
			}
		}
	}
	checkAndOpenRightGate();
}

inline void updatePortal3Enemy2() {
	for (int i = 0; i < 2; i++) {
		if (!portalEnemy2[i].alive) continue;

		portalEnemy2[i].x += portalEnemy2[i].speed * portalEnemy2[i].direction;

		if (portalEnemy2[i].x >= portalEnemy2[i].maxX) {
			portalEnemy2[i].x = portalEnemy2[i].maxX;
			portalEnemy2[i].direction = -1;
		}
		else if (portalEnemy2[i].x <= portalEnemy2[i].minX) {
			portalEnemy2[i].x = portalEnemy2[i].minX;
			portalEnemy2[i].direction = 1;
		}

		if (gameState == 7 && playerIFrames == 0) {
			double distX = playerX - portalEnemy2[i].x;
			double distY = playerY - portalEnemy2[i].y;
			double distance = sqrt(distX * distX + distY * distY);

			if (distance < 30.0) {
				playerHealth -= 2;
				if (playerHealth < 0) playerHealth = 0;
				playerIFrames = 60;
			}
		}
	}

	// Check player collection for lightning spells
	if (gameState == 7) {
		for (int i = 0; i < 1; i++) {
			if (!portalLightnings[i].collected) {
				double distX = playerX - portalLightnings[i].x;
				double distY = playerY - portalLightnings[i].y;
				double distance = sqrt(distX * distX + distY * distY);

				if (distance < 30.0) {
					portalLightnings[i].collected = true;
					lightningCollected = true;
				}
			}
		}
	}
}

inline void drawPortal3Map() {
	for (int row = 0; row < PORTAL3_ROWS; row++) {
		for (int col = 0; col < PORTAL3_COLS; col++) {
			int tileType = portal3Map[row][col];

			if (tileType == 2 && !isTotemSolved) {
				int x = col * PORTAL3_TILE;
				int y = (PORTAL3_ROWS - 1 - row) * PORTAL3_TILE;

				iSetColor(255, 215, 0);
				iFilledRectangle(x + 18, y + 60, 4, 12);
				iFilledCircle(x + 20, y + 55, 2.5);
			}
		}
	}

	iShowImage(0, 0, PORTAL3_COLS * PORTAL3_TILE, PORTAL3_ROWS * PORTAL3_TILE, imgPortal3FullMap);

	// Draw uncollected lightning spells
	for (int i = 0; i < 1; i++) {
		if (!portalLightnings[i].collected) {
			iShowImage(portalLightnings[i].x, portalLightnings[i].y, 30, 30, portal3LightningImg);
		}
	}

	// Draw active player blue fireballs with image
	for (int i = 0; i < MAX_BLUE_FIREBALLS; i++) {
		if (blueFireballs[i].active) {
			if (blueFireballImg != -1) {
				iShowImage((int)(blueFireballs[i].x - 15), (int)(blueFireballs[i].y - 15), 30, 30, blueFireballImg);
			}
			else {
				iSetColor(0, 150, 255); // Fallback color
				iFilledCircle(blueFireballs[i].x, blueFireballs[i].y, 6);
			}
		}
	}

	for (int i = 0; i < 2; i++) {
		if (portalEnemies[i].alive) {
			iShowImage(portalEnemies[i].x, portalEnemies[i].y, 35, 35, portal3EnemyImg);
		}
	}
	for (int i = 0; i < 2; i++) {
		if (portalEnemy2[i].alive) {
			iShowImage(portalEnemy2[i].x, portalEnemy2[i].y, 35, 35, portal3Enemy2Img);
		}
	}
}