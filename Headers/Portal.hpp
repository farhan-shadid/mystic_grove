#pragma once
#include <math.h> 


extern double playerX;
extern double playerY;
extern int gameState;
extern int slimeImg;
extern int slimeBulletImg;
extern int stoneImg;
extern int bookImg;



const int PORTAL_ROWS = 25;
const int PORTAL_COLS = 25;
const int PORTAL_TILE = 40;

//  0 = Path, 1 = Stone, 2 = Bush, 3 = Spell Book
int portalMap[PORTAL_ROWS][PORTAL_COLS] = {
	{ 0, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 2 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 0 }
};

bool spellCollected = false;
int speedBoostTimer = 0;          
double defaultPlayerSpeed = 4.0;  
double currentPlayerSpeed = 4.0;  

void updatePortalSpell() { 
	
	if (gameState != 5) return;

	
	if (spellCollected) return;


	int bookRow = 1;
	int bookCol = 12;
	double bookX = bookCol * PORTAL_TILE;
	double bookY = (PORTAL_ROWS - 1 - bookRow) * PORTAL_TILE;

	// Player Collision Check

	if ((playerX + 12.0 > bookX) &&
		(playerX - 12.0 < bookX + PORTAL_TILE) &&
		(playerY + 50.0 > bookY) &&
		(playerY < bookY + PORTAL_TILE)) {

		portalMap[bookRow][bookCol] = 0;

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
	slimes[0] = { 120.0, (double)((PORTAL_ROWS - 1 - 2) * PORTAL_TILE), 2.0, 1, 0.0, 0.0, 0, 1 };
	slimes[1] = { 520.0, (double)((PORTAL_ROWS - 1 - 7) * PORTAL_TILE), 3.0, -1, 0.0, 0.0, 0, 1 };
	slimes[2] = { 320.0, (double)((PORTAL_ROWS - 1 - 14) * PORTAL_TILE), 1.5, 1, 0.0, 0.0, 0, 1 };
	slimes[3] = { 280.0, (double)((PORTAL_ROWS - 1 - 17) * PORTAL_TILE), 2.5, 1, 0.0, 0.0, 0, 1 };
	slimes[4] = { 640.0, (double)((PORTAL_ROWS - 1 - 5) * PORTAL_TILE), 2.0, -1, 0.0, 0.0, 0, 1 };
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

		if (isPortalSolid(nextX, slimes[i].y + 20) || isPortalSolid(nextX + 30, slimes[i].y + 20)) {
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

//		COLLISIONS

		if (gameState == 5) {
			// 3. Player x Slime 
			if (playerIFrames == 0) {
				if ((playerX - 12.0 < slimes[i].x + 60.0) &&
					(playerX + 12.0 > slimes[i].x) &&
					(playerY < slimes[i].y + 60.0) &&
					(playerY + 50.0 > slimes[i].y)) {

					playerHealth -= 1;
					playerIFrames = 60;
					if (playerHealth <= 0) {
						gameState = 0;
						playerHealth = maxHealth;
					}
					playerX = 500.0;
					playerY = 60.0;
				}
			}

			// 4. Player x Bullet
			if (slimes[i].bulletActive == 1 && playerIFrames == 0) {
				if ((playerX - 12.0 < slimes[i].bulletX + 24.0) &&
					(playerX + 12.0 > slimes[i].bulletX) &&
					(playerY < slimes[i].bulletY + 24.0) &&
					(playerY + 50.0 > slimes[i].bulletY)) {

					playerHealth -= 1;
					playerIFrames = 60;
					if (playerHealth <= 0) {
						gameState = 0;
						playerHealth = maxHealth;
					}
					playerX = 500.0;
					playerY = 60.0;
					slimes[i].bulletActive = 0;
				}
			}
		}
	}
}

void drawPortalSlimes() {
	for (int i = 0; i < NUM_SLIMES; i++) {
		if (slimes[i].active == 1) {

			
			if (slimes[i].bulletActive == 1) {
				if (slimeBulletImg != -1) {
					iShowImage(slimes[i].bulletX, slimes[i].bulletY, 24, 24, slimeBulletImg);
				}
			}

			
			if (slimeImg != -1) {
				iShowImage(slimes[i].x - 10.0, slimes[i].y - 10.0, 60, 60, slimeImg);
			}
		}
	}
}

void drawPortal1Map() {
	for (int row = 0; row < PORTAL_ROWS; row++) {
		for (int col = 0; col < PORTAL_COLS; col++) {
			int x = col * PORTAL_TILE;
			int y = (PORTAL_ROWS - 1 - row) * PORTAL_TILE;

			if ((row + col) % 2 == 0) iSetColor(35, 90, 35);
			else iSetColor(45, 110, 45);

			iFilledRectangle(x, y, PORTAL_TILE, PORTAL_TILE);

			int tileType = portalMap[row][col];

			if (tileType == 1) {
				if (stoneImg != -1) {
					
					iShowImage(x, y - 8.0, PORTAL_TILE, PORTAL_TILE, stoneImg);
				}
				else {
					iSetColor(105, 105, 105);
					iFilledRectangle(x, y, PORTAL_TILE, PORTAL_TILE);
				}
			}
			else if (tileType == 2) {
				
				iSetColor(25, 65, 25); 
				iFilledRectangle(x, y, PORTAL_TILE, 12);

				
				iSetColor(35, 110, 35);				
				iFilledEllipse(x + 20, y + 16, 16, 14);				
				iFilledEllipse(x + 10, y + 12, 10, 10);				
				iFilledEllipse(x + 30, y + 12, 10, 10);

				
				iSetColor(50, 140, 50);
				iFilledEllipse(x + 20, y + 18, 10, 8);
				iFilledEllipse(x + 10, y + 14, 6, 6);
				iFilledEllipse(x + 30, y + 14, 6, 6);

				
				iSetColor(15, 40, 15);
				iLine(x, y, x + PORTAL_TILE, y);
			}
			else if (tileType == 3) {			
				if (bookImg != -1) {
					iShowImage(x, y, PORTAL_TILE, PORTAL_TILE, bookImg);
				}
			}
		}
	}
	drawPortalSlimes();
}