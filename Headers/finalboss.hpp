#ifndef FINAL_HPP
#define FINAL_HPP

#include <math.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

#define PI 3.14159265358979323846

extern double playerX;
extern double playerY;
extern int playerDirection; 
extern int throwCooldown;

struct LightningBall {
	double x, y;
	double vx, vy;
	bool active;
};

const int MAX_LIGHTNING_BALLS = 3;
LightningBall lightningBalls[MAX_LIGHTNING_BALLS];

extern int bgArenaImg;
extern int bossImg;
extern int bossGreenSpellImg;
extern int portal3LightningImg;
extern int trappedFairyImg;

// BOSS STATE


double bossX = 500.0;
double bossY = 700.0;
double bossHealth = 100.0;
double maxBossHealth = 100.0;
bool bossActive = true;
int bossAttackTimer = 0;

// Boss(Green Spell)
struct BossProjectile {
	double x, y;
	double vx, vy;
	bool active;
};
const int MAX_BOSS_PROJECTILES = 5;
BossProjectile bossProjectiles[MAX_BOSS_PROJECTILES];



// BOSS & ARENA 


inline void drawBoss()
{
	if (!bossActive) return;

	if (bossImg != -1) {
		iShowImage((int)(bossX - 45), (int)(bossY - 60), 90, 120, bossImg);
	}
	else {
		iSetColor(40, 30, 30);
		iFilledRectangle(bossX - 30, bossY - 45, 60, 90);
		iSetColor(255, 100, 0);
		iFilledCircle(bossX, bossY + 30, 15);
		iSetColor(255, 200, 0);
		iFilledCircle(bossX - 5, bossY + 32, 3);
		iFilledCircle(bossX + 5, bossY + 32, 3);
	}

	// Boss Health Bar UI 
	iSetColor(50, 50, 50);
	iFilledRectangle(350, 920, 300, 20);
	iSetColor(255, 50, 0);
	double healthWidth = (double)bossHealth / maxBossHealth * 300.0;
	if (healthWidth < 0) healthWidth = 0;
	iFilledRectangle(350, 920, healthWidth, 20);
	iSetColor(255, 255, 255);
	iRectangle(350, 920, 300, 20);
}

inline void drawMysticGroveArena() {
	if (bgArenaImg != -1) {
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bgArenaImg);
	}
	else {
		iSetColor(20, 50, 30);
		iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	//Trapped Fairy Tree
	if (trappedFairyImg != -1) {
		
		iShowImage(720, 660, 70, 110, trappedFairyImg);
	}
}



// LIGHTNING BALL (PLAYER ATTACK)


inline void throwLightningBall() {
	if (throwCooldown > 0) return;

	for (int i = 0; i < MAX_LIGHTNING_BALLS; i++) {
		if (!lightningBalls[i].active) {
			lightningBalls[i].active = true;
			lightningBalls[i].x = playerX + 20.0;
			lightningBalls[i].y = playerY + 20.0;

			double speed = 10.0;
			lightningBalls[i].vx = 0.0;
			lightningBalls[i].vy = 0.0;

			if (playerDirection == 3) lightningBalls[i].vy = speed;       
			else if (playerDirection == 0) lightningBalls[i].vy = -speed; 
			else if (playerDirection == 1) lightningBalls[i].vx = -speed; 
			else if (playerDirection == 2) lightningBalls[i].vx = speed;   

			throwCooldown = 20; 
			break;
		}
	}
}


// BATTLE MECHANISM & BOSS AI 


inline void updateBattleMechanics(int &playerHealthRef, int &playerIFramesRef) {
	if (throwCooldown > 0) throwCooldown--;
	if (playerIFramesRef > 0) playerIFramesRef--;

	for (int i = 0; i < MAX_LIGHTNING_BALLS; i++) {
		if (lightningBalls[i].active) {
			lightningBalls[i].x += lightningBalls[i].vx;
			lightningBalls[i].y += lightningBalls[i].vy;

			if (lightningBalls[i].x < 0 || lightningBalls[i].x > SCREEN_WIDTH ||
				lightningBalls[i].y < 0 || lightningBalls[i].y > SCREEN_HEIGHT) {
				lightningBalls[i].active = false;
			}

			// Boss Collision Check
			if (bossActive) {
				double distX = lightningBalls[i].x - bossX;
				double distY = lightningBalls[i].y - bossY;
				if (sqrt(distX * distX + distY * distY) < 35.0) {
					bossHealth -= 5.0;
					lightningBalls[i].active = false;
					if (bossHealth <= 0) {
						bossHealth = 0;
						bossActive = false;
					}
				}
			}
		}
	}

	// Boss AI & Movement 
	if (bossActive) {
		bossAttackTimer++;

		if (bossX < playerX) bossX += 0.2;
		if (bossX > playerX) bossX -= 0.2;
		if (bossY < playerY) bossY += 0.2;
		if (bossY > playerY) bossY -= 0.2;

		if (bossAttackTimer >= 90) {
			bossAttackTimer = 0;
			for (int j = 0; j < MAX_BOSS_PROJECTILES; j++) {
				if (!bossProjectiles[j].active) {
					bossProjectiles[j].active = true;
					bossProjectiles[j].x = bossX;
					bossProjectiles[j].y = bossY;

					double angle = atan2(playerY - bossY, playerX - bossX) + ((rand() % 40 - 20) * 0.01);
					bossProjectiles[j].vx = cos(angle) * 5.5;
					bossProjectiles[j].vy = sin(angle) * 5.5;
					break;
				}
			}
		}
	}

	// Update Boss Green Spell Projectiles & Check Collision with Player
	for (int j = 0; j < MAX_BOSS_PROJECTILES; j++) {
		if (bossProjectiles[j].active) {
			bossProjectiles[j].x += bossProjectiles[j].vx;
			bossProjectiles[j].y += bossProjectiles[j].vy;

			if (bossProjectiles[j].x < 0 || bossProjectiles[j].x > SCREEN_WIDTH ||
				bossProjectiles[j].y < 0 || bossProjectiles[j].y > SCREEN_HEIGHT) {
				bossProjectiles[j].active = false;
			}

			// Player hit collision check 
			if (playerIFramesRef == 0) {
				double pdx = bossProjectiles[j].x - playerX;
				double pdy = bossProjectiles[j].y - (playerY + 20);
				if (sqrt(pdx * pdx + pdy * pdy) < 22.0) {
					playerHealthRef -= 2;
					if (playerHealthRef < 0) playerHealthRef = 0;
					playerIFramesRef = 60;
					bossProjectiles[j].active = false;
				}
			}
		}
	}
}

inline void renderProjectiles() {
	for (int i = 0; i < MAX_LIGHTNING_BALLS; i++) {
		if (lightningBalls[i].active) {
			if (portal3LightningImg != -1) {
				
				iShowImage((int)(lightningBalls[i].x - 15), (int)(lightningBalls[i].y - 15), 30, 30, portal3LightningImg);
			}
			else {
			
				iSetColor(0, 255, 255);
				iFilledCircle(lightningBalls[i].x, lightningBalls[i].y, 6);
			}
		}
	}
	// Render Boss Green Spell Projectiles
	for (int j = 0; j < MAX_BOSS_PROJECTILES; j++) {
		if (bossProjectiles[j].active) {
			if (bossGreenSpellImg != -1) {
				iShowImage((int)(bossProjectiles[j].x - 15), (int)(bossProjectiles[j].y - 15), 30, 30, bossGreenSpellImg);
			}
			else {
				// Fallback vector green spell graphic
				iSetColor(50, 255, 50);
				iFilledCircle(bossProjectiles[j].x, bossProjectiles[j].y, 9);
			}
		}
	}
}

#endif 