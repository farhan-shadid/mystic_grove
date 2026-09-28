#include "iGraphics.h"

int gameState = 0;
int menuBgImage;
int mainmap;
int imgPortal3FullMap;
int portal3EnemyImg;
int portal3Enemy2Img;
int portal3LightningImg;
int blueFireballImg;
int bgArenaImg;
int bossImg;
int bossGreenSpellImg;
int trappedFairyImg;
int playerHealth = 6;
int maxHealth = 6;
int victoryTextTimer = 0;
int playerIFrames = 0;
int levelClearTimer = 0;
int imgWeaponFront;
int imgWeaponLeft;
int imgWeaponRight;
int imgWeaponBack;
int imgPortal2Map;
int imgPortal2Drones[5];
int slimeImg = -1;
int slimeBulletImg = -1;
int imgPortal1Map = -1;
int bookImg = -1;
int heartFullImg = -1;
int heartHalfImg = -1;
int portal3TextImg = -1;
int manualImg = -1;
int inspectImg = -1;
int hintImg = -1;
int mapHintTimer = 0;
int lockedImg = -1;
int solvedImg = -1;
int imgFireball;
int imgWaterball;
int storyImg = -1;
int creditImg = -1;
int imgFairyHelp = -1;
int imgVillainIntro1 = -1;
int imgVillainIntro2 = -1;
int imgVillainDefeat = -1;
int imgFairyHelped = -1;
int imgGameCleared = -1;
int imgGameOver = -1;
int imgLevelCleared = -1;
int imgPuzzleSolved = -1;

int bossIntroTimer = 0; 
int bossOutroTimer = 0; 

bool portal1Cleared = false;
bool portal2Cleared = false;
bool portal2Unlocked = false; 
bool portal3Unlocked = false; 
extern bool spellCollected;
extern bool isTotemSolved;

const double MAIN_SPAWN_X = 460.0;
const double MAIN_SPAWN_Y = 100.0;

const double PORTAL1_SPAWN_X = 500.0;
const double PORTAL1_SPAWN_Y = 100.0;

const double PORTAL2_SPAWN_X = 500.0;
const double PORTAL2_SPAWN_Y = 100.0;


#include "Menu.hpp"
#include "Mainmap.hpp"
#include "Character.hpp"
#include "Portal.hpp"
#include "portal2.hpp"
#include "portal3.hpp"
#include "RunePuzzle.hpp"
#include "finalboss.hpp"
#include "SaveSystem.hpp"

inline void drawPlayerStones() {
	for (int i = 0; i < MAX_STONES; i++) {
		if (playerStones[i].active) {
			if (playerStones[i].isLightning) {
			
				iShowImage(playerStones[i].x, playerStones[i].y, 30, 30, portal3LightningImg);
			}
			else {
			
				iSetColor(120, 120, 120);
				iFilledCircle(playerStones[i].x, playerStones[i].y, 5);
			}
		}
	}
}
void drawLevelClearedOverlay() {
	if (levelClearTimer > 0) {
		if (imgLevelCleared != -1) {
			
			iShowImage(150, 380, 700, 240, imgLevelCleared);
		}
	}
}

void iDraw() {
	iClear();

	if (gameState == 0) {
		drawMenuScreen();
	}
	else if (gameState == 2) {
		if (appState == APP_MAP) {
			currentLevel.draw();
			drawPlayer();

			
			if (mapHintTimer > 0) {
				if (hintImg != -1) {
					
					iShowImage(200, 750, 600, 200, hintImg);
				}
			}

		}
		else if (appState == APP_PUZZLE) {
			drawPuzzleMinigame();
		}


		// PORTAL 1 
		if (playerX < 200 && playerY > 700) {
			if (portal1Cleared) {
				if (solvedImg != -1) iShowImage(70, 840, 180, 120, solvedImg);
			}
			else if (!isPortalOpen) { 
				if (lockedImg != -1) iShowImage(70, 840, 180, 120, lockedImg);
			}
		}

		// PORTAL 2 
		if (playerX > 740 && playerY > 700) {
			if (portal2Cleared) {
				if (solvedImg != -1) iShowImage(760, 840, 180, 120, solvedImg);
			}
			else if (!portal2Unlocked) { 
				if (lockedImg != -1) iShowImage(760, 840, 180, 120, lockedImg);
			}
		}

		// PORTAL 3 
		if (isNearBigTree(playerX, playerY)) {
			if (isTotemSolved) {
				if (solvedImg != -1) iShowImage(410, 820, 180, 120, solvedImg);
			}
			else if (!portal3Unlocked) { 
				if (lockedImg != -1) iShowImage(410, 820, 180, 120, lockedImg);
			}
		}
	}
	else if (gameState == 3) {
		drawStoryPopup();
	}
	else if (gameState == 4) {
		drawCreditsPopup();
	}
	else if (gameState == 5) {
		drawPortal1Map();
		drawPlayer();
	}

	else if (gameState == 6) {
		drawPortal2Map();
		drawSpeedBoosters();
		drawPlayer();

	
		for (int i = 0; i < NUM_PORTAL2_DRONES; i++)
		{
			if (waterBallActive[i])
			{
				iShowImage(
					(int)waterBallX[i] - 15,
					(int)waterBallY[i] - 15,
					30,
					30,
					imgWaterball
					);
			}
		}
	}
	if (gameState == 6)
	{
		for (int i = 0; i < MAX_STONES; i++)
		{
			if (playerStones[i].active)
			{
				iShowImage(
					(int)playerStones[i].x - 12,
					(int)playerStones[i].y - 12,
					24,
					24,
					imgFireball
					);
			}
		}
	}

	if (gameState == 5) {
		for (int i = 0; i < MAX_STONES; i++) {
			if (playerStones[i].active) {
				if (spellCollected) {
					
					if (imgFireball != -1) {
						
						iShowImage(playerStones[i].x - 12, playerStones[i].y - 12, 24, 24, imgFireball);
					}
				}
				else {
					
					iSetColor(169, 169, 169);
					iFilledCircle(playerStones[i].x, playerStones[i].y, 6);

					iSetColor(211, 211, 211);
					iFilledCircle(playerStones[i].x - 2, playerStones[i].y + 2, 2);
				}
			}
		}
	}


	if (gameState == 5) {
		for (int i = 0; i < MAX_STONES; i++) {
			if (playerStones[i].active) {
				for (int j = 0; j < NUM_SLIMES; j++) {
					if (slimes[j].active == 1) {

						double slimeCenterX = slimes[j].x + 20.0;
						double slimeCenterY = slimes[j].y + 20.0;

						double dx = playerStones[i].x - slimeCenterX;
						double dy = playerStones[i].y - slimeCenterY;

						if (dx * dx + dy * dy <= 22.0 * 22.0) {
							slimes[j].active = 0; 
							playerStones[i].active = false; 
							break;
						}
					}
				}
			}
		}
	}

	//  WIN CONDITION: PORTAL 1  
	if (gameState == 5) {
		bool slimesRemaining = false;
		for (int i = 0; i < NUM_SLIMES; i++) {
			if (slimes[i].active == 1) {
				slimesRemaining = true;
				break;
			}
		}

	
		if (!slimesRemaining && spellCollected) {
			if (levelClearTimer == 0) {
				levelClearTimer = 120;
			}
		}
	}
	
	if (gameState == 6) {
		for (int i = 0; i < MAX_STONES; i++) {
			if (playerStones[i].active) {
				for (int j = 0; j < NUM_PORTAL2_DRONES; j++) {

					double droneCenterX = portal2Drones[j].x + 20.0;
					double droneCenterY = portal2Drones[j].y + 21.0;

					double dx = playerStones[i].x - droneCenterX;
					double dy = playerStones[i].y - droneCenterY;

					if (dx * dx + dy * dy <= 22.0 * 22.0) {

						
						waterBallActive[j] = true;
						waterBallX[j] = portal2Drones[j].x + 20.0;
						waterBallY[j] = portal2Drones[j].y + 21.0;

				
						portal2Drones[j].bulletActive = 0;
						portal2Drones[j].x = -9999.0;

					
						playerStones[i].active = false;

						break;
					}
				}
			}
		}
	}

	// WIN CONDITION: PORTAL 2  
	if (gameState == 6) {
		bool dronesRemaining = false;
		for (int i = 0; i < NUM_PORTAL2_DRONES; i++) {
			if (portal2Drones[i].x > -1000.0) {
				dronesRemaining = true;
				break;
			}
		}

		if (!dronesRemaining) {
			if (levelClearTimer == 0) {
				levelClearTimer = 120; 
			}
		}
	}

	if (levelClearTimer > 0) {
		drawLevelClearedOverlay();
	}

	if (gameState == 6) {
		drawHealthUI();
	}

	else if (gameState == 7) {
		
		drawPortal3Map();
		drawPlayer();

		if (appState == APP_MAP) {
			
			if (playerX >= 200.0 && playerX <= 400.0 && playerY >= 560.0 && playerY <= 880.0 && !isTotemSolved) {
				iSetColor(255, 255, 255);
				iText(playerX - 70, playerY + 60, (char*)"Press [F] to inspect Totem", GLUT_BITMAP_HELVETICA_18);
			}

		
			if (victoryTextTimer > 0 && imgPuzzleSolved != -1) {
				iShowImage(150, 280, 700, 440, imgPuzzleSolved);
			}
		}
		else if (appState == APP_INFO) {
	
			if (portal3TextImg != -1) {
				iShowImage(150, 280, 700, 440, portal3TextImg);
			}
		}
		else if (appState == APP_RUNE_MANUAL) {

			if (manualImg != -1) {
				iShowImage(150, 280, 700, 440, manualImg);
			}
		}
		else if (appState == APP_RUNE) {
			drawRunePuzzle();
		}
	}

	else if (gameState == 9) {
		drawMysticGroveArena(); 
		drawBoss();            
		renderProjectiles();    
		drawPlayer();           

	
		if (bossIntroTimer > 360) {
			if (imgFairyHelp != -1) iShowImage(100, 350, 800, 320, imgFairyHelp); // Fairy trapped
		}
		else if (bossIntroTimer > 180) {
			if (imgVillainIntro1 != -1) iShowImage(100, 350, 800, 320, imgVillainIntro1); // "So you've arrived..."
		}
		else if (bossIntroTimer > 0) {
			if (imgVillainIntro2 != -1) iShowImage(100, 350, 800, 320, imgVillainIntro2); // "I shall see to it..."
		}

	
		if (bossOutroTimer > 180) {
			if (imgVillainDefeat != -1) iShowImage(100, 350, 800, 320, imgVillainDefeat); // "This can't be happening!"
		}
		else if (bossOutroTimer > 0 && bossOutroTimer <= 180) {
			if (imgFairyHelped != -1) iShowImage(100, 350, 800, 320, imgFairyHelped); // Fairy freed
		}
	}

	
	if (gameState == 2 || gameState == 7) {
		drawPlayerStones();
	}


	if (gameState == 2 || gameState == 5 || gameState == 6 || gameState == 7 || gameState == 9) {
		drawHealthUI();
	}
	else if (gameState == 10) {
	
		iSetColor(15, 0, 0);
		iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		if (imgGameOver != -1) {
			iShowImage(50, 300, 900, 400, imgGameOver);
		}
	}
	else if (gameState == 11) {
		
		iSetColor(5, 20, 10);
		iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		if (imgGameCleared != -1) {
			iShowImage(50, 300, 900, 400, imgGameCleared);
		}
	}
}

void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		// 1. MAIN MENU BUTTONS
		if (gameState == 0) {
			for (int i = 0; i < 4; i++) {
				if (mx >= menuBtns[i].x && mx <= (menuBtns[i].x + menuBtns[i].width) &&
					my >= menuBtns[i].y && my <= (menuBtns[i].y + menuBtns[i].height)) {

					if (i == 0) {
						if (saveExists) {
							loadGame();
							playerX = MAIN_SPAWN_X;
							playerY = MAIN_SPAWN_Y;
						}
						else {
							resetAllGameData();
						}
						gameState = 2;
						mapHintTimer = 180;
					}
					else if (i == 1) gameState = 3;
					else if (i == 2) gameState = 4;
					else if (i == 3) {
						resetAllGameData(); // CLEAR DATA button
					}
					break;
				}
			}
		}

		// 2. PUZZLE MINIGAME BOXES
		else if (gameState == 2 && appState == APP_PUZZLE) {
			for (int i = 0; i < NUM_BOXES; i++) {
				bool insideX = (mx >= boxes[i].x && mx <= (boxes[i].x + BOX_SIZE));
				bool insideY = (my >= boxes[i].y && my <= (boxes[i].y + BOX_SIZE));

				if (insideX && insideY) {
					if (i == correctIndex) {
						score++;
						checkGameEnd();
						if (appState == APP_PUZZLE) startNewRound();
					}
					else {
						miss++;
						checkGameEnd();
						if (appState == APP_PUZZLE) startNewRound();
					}
					break;
				}
			}
		}

		// 3. STORY & CREDITS POPUP EXIT 
		else if (gameState == 3 || gameState == 4) {
			if (mx < 100 || mx > 900 || my < 200 || my > 760) {
				gameState = 0;
			}
		}

		// 5. RUNE PUZZLE MANUAL -> Start 3x3 Rune Grid
		else if (gameState == 7 && appState == APP_RUNE_MANUAL) {
			appState = APP_RUNE;
		}

		// 6. RUNE PUZZLE (3x3 Grid)
		else if (gameState == 7 && appState == APP_RUNE) {
			for (int r = 0; r < 3; r++) {
				for (int c = 0; c < 3; c++) {
					int rx = 330 + c * 115;
					int ry = 300 + (2 - r) * 115;

					if (mx >= rx && mx <= (rx + 100) && my >= ry && my <= (ry + 100)) {
						toggleRune(r, c);

						int sum = 0;
						for (int i = 0; i < 3; i++) {
							for (int j = 0; j < 3; j++) sum += runeGrid[i][j];
						}

						if (sum == 9) {
							isTotemSolved = true;
							maxHealth += 4;
							playerHealth += 4;
							appState = APP_MAP;
							victoryTextTimer = 240;
							portal3Map[8][10] = 0;
							portal3Map[9][10] = 0;
							saveGame();
							saveExists = true;
						}
						break;
					}
				}
			}
		}

		// 7. PORTAL 3 ENTRY POPUP EXIT
		else if (gameState == 7 && appState == APP_INFO) {
			appState = APP_MAP;
		}

		// 8. GAME OVER SCREEN CLICK 
		else if (gameState == 10) {
			resetAllGameData(); 
			appState = APP_MAP;
			gameState = 0;
		}

		// 9. GAME CLEARED SCREEN CLICK 
		else if (gameState == 11) {
			resetAllGameData();
			appState = APP_MAP;
			gameState = 0;
		}
	} 
}

void iKeyboard(unsigned char key) {
}

void iSpecialKeyboard(unsigned char key) {}
void iMouseMove(int mx, int my) {}
void iPassiveMouseMove(int mx, int my) {}

void fixedUpdate() {
	if (victoryTextTimer > 0) {
		victoryTextTimer--;
	}
	if (gameState == 6)
	{
		checkSpeedBooster();
		updateSpeedBooster();
	}
	if (mapHintTimer > 0) {
		mapHintTimer--;
	}
	if (playerIFrames > 0)
		playerIFrames--;

	//  STONE THROW COOLDOWN 
	if (throwCooldown > 0) throwCooldown--;


	if (levelClearTimer > 0) {
		levelClearTimer--;
	
		if (levelClearTimer == 0) {
			if (gameState == 5) {
				portal1Cleared = true;
				portal2Unlocked = true;
			}
			else if (gameState == 6) {
				portal2Cleared = true;
				portal3Unlocked = true;
			}

			gameState = 2; // Return to Main Map
			playerX = MAIN_SPAWN_X;
			playerY = MAIN_SPAWN_Y;
			mapHintTimer = 180; 
			saveGame();
			saveExists = true;
		}
	}


	// STONE THROW COOLDOWN 
	if (throwCooldown > 0) throwCooldown--;

	// FIRE A STONE 
	if (gameState != 9 && gameState != 7 && isKeyPressed(' ') && throwCooldown == 0) {
		for (int i = 0; i < MAX_STONES; i++) {
			if (!playerStones[i].active) {
				playerStones[i].active = true;
				playerStones[i].x = playerX + 20.0;
				playerStones[i].y = playerY + 20.0;
				playerStones[i].direction = playerDirection;
				playerStones[i].isLightning = lightningCollected;
				throwCooldown = 20;
				break;
			}
		}
	}


	// MOVE ACTIVE STONES 
	for (int i = 0; i < MAX_STONES; i++) {
		if (playerStones[i].active) {
			double speed = 8.0;

			if (playerStones[i].direction == 3) playerStones[i].y += speed;      
			else if (playerStones[i].direction == 0) playerStones[i].y -= speed; 
			else if (playerStones[i].direction == 1) playerStones[i].x -= speed; 
			else if (playerStones[i].direction == 2) playerStones[i].x += speed; 

			// Boundary Check
			if (playerStones[i].x < 0 || playerStones[i].x > 1000 ||
				playerStones[i].y < 0 || playerStones[i].y > 1000) {
				playerStones[i].active = false;
			}

			// Obstacle Collision Check 
			if (gameState == 7) {
				int col = (int)(playerStones[i].x / PORTAL3_TILE);
				int row = PORTAL3_ROWS - 1 - (int)(playerStones[i].y / PORTAL3_TILE);

				if (row >= 0 && row < PORTAL3_ROWS && col >= 0 && col < PORTAL3_COLS) {
					if (portal3Map[row][col] == 1) {
						playerStones[i].active = false; // Destroy stone on obstacle hit
					}
				}

				// Enemy Hit / Kill Check
				for (int e = 0; e < 2; e++) {
					if (portalEnemies[e].alive) {
						double distX = playerStones[i].x - portalEnemies[e].x;
						double distY = playerStones[i].y - portalEnemies[e].y;
						double distance = sqrt(distX * distX + distY * distY);

						if (distance < 25.0) { 
							portalEnemies[e].alive = false; 
							playerStones[i].active = false; 
						}
					}
				}
				for (int e2 = 0; e2 < 2; e2++) {
					if (portalEnemy2[e2].alive) {
						double distX = playerStones[i].x - portalEnemy2[e2].x;
						double distY = playerStones[i].y - portalEnemy2[e2].y;
						double distance = sqrt(distX * distX + distY * distY);

						if (distance < 25.0) {
							portalEnemy2[e2].alive = false; 
							playerStones[i].active = false; 
						}
					}
				}
			}
		}
	}

	if (gameState == 2 && appState == APP_MAP) {
		playerWalking = false;

		double moveSpeed = 1.2;
		double newX = playerX;
		double newY = playerY;

		if (isKeyPressed('w') || isKeyPressed('W') || isSpecialKeyPressed(GLUT_KEY_UP)) {
			newY += moveSpeed;
			playerDirection = 3;
			playerWalking = true;
		}
		if (isKeyPressed('s') || isKeyPressed('S') || isSpecialKeyPressed(GLUT_KEY_DOWN)) {
			newY -= moveSpeed;
			playerDirection = 0;
			playerWalking = true;
		}
		if (isKeyPressed('a') || isKeyPressed('A') || isSpecialKeyPressed(GLUT_KEY_LEFT)) {
			newX -= moveSpeed;
			playerDirection = 1;
			playerWalking = true;
		}
		if (isKeyPressed('d') || isKeyPressed('D') || isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
			newX += moveSpeed;
			playerDirection = 2;
			playerWalking = true;
		}

		// Screen Boundary Clamping
		if (newX < 18.0) newX = 18.0;
		if (newX > SCREEN_WIDTH - 18.0) newX = SCREEN_WIDTH - 18.0;
		if (newY < 10.0) newY = 10.0;
		if (newY > SCREEN_HEIGHT - 48.0) newY = SCREEN_HEIGHT - 48.0;

		// Collision checking
		if (!isSolid(newX, playerY)) playerX = newX;
		if (!isSolid(playerX, newY)) playerY = newY;

		if (playerWalking) {
			walkFrame += 0.08;
			if (walkFrame >= 2 * PI) walkFrame -= 2 * PI;
		}
		else {
			walkFrame = 0;
		}

		// Open Minigame via [F] 
		if (isKeyPressed('f') || isKeyPressed('F')) {
			if (isNearPuzzle(playerX, playerY) && !isPortalOpen && !portal1Cleared) {
				appState = APP_PUZZLE;
				score = 0;
				miss = 0;
				startNewRound();
				return;
			}
		}

		// Enter Portal 1 
		if ((isKeyPressed('f') || isKeyPressed('F')) && (isPortalOpen && !portal1Cleared) && playerX < 200 && playerY > 700) {
			gameState = 5;
			playerX = PORTAL1_SPAWN_X;
			playerY = PORTAL1_SPAWN_Y;
			return;
		}

		// Enter Portal 2 
		if ((isKeyPressed('f') || isKeyPressed('F')) && (portal2Unlocked && !portal2Cleared) && playerX > 740 && playerY > 700) {
			gameState = 6;
			playerX = PORTAL2_SPAWN_X;
			playerY = PORTAL2_SPAWN_Y;
			return;
		}

		// Enter Portal 3 
		if ((isKeyPressed('f') || isKeyPressed('F')) && (portal3Unlocked && !isTotemSolved)) {
			if (isNearBigTree(playerX, playerY)) {
				gameState = 7;
				playerX = 200.0;
				playerY = 240.0;
				appState = APP_INFO;
				return;
			}
		}
	}
	else if (appState == APP_PUZZLE) {
		gameTick();
	}

	else if (gameState == 6) {
		playerWalking = false;

		double newX = playerX;


		double newY = playerY;

		if (isKeyPressed('w') || isKeyPressed('W') || isSpecialKeyPressed(GLUT_KEY_UP)) {
			newY += moveSpeed;
			playerDirection = 3;
			playerWalking = true;
		}
		if (isKeyPressed('s') || isKeyPressed('S') || isSpecialKeyPressed(GLUT_KEY_DOWN)) {
			newY -= moveSpeed;
			playerDirection = 0;
			playerWalking = true;
		}
		if (isKeyPressed('a') || isKeyPressed('A') || isSpecialKeyPressed(GLUT_KEY_LEFT)) {
			newX -= moveSpeed;
			playerDirection = 1;
			playerWalking = true;
		}
		if (isKeyPressed('d') || isKeyPressed('D') || isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
			newX += moveSpeed;
			playerDirection = 2;
			playerWalking = true;
		}

		// Screen Boundary 
		if (newX < 18.0) newX = 18.0;
		if (newX > SCREEN_WIDTH - 18.0) newX = SCREEN_WIDTH - 18.0;
		if (newY < 10.0) newY = 10.0;
		if (newY > SCREEN_HEIGHT - 48.0) newY = SCREEN_HEIGHT - 48.0;

		// Collision checking
		if (!isPortal2Solid(newX, playerY)) playerX = newX;
		if (!isPortal2Solid(playerX, newY)) playerY = newY;


		if (playerWalking) {
			walkFrame += 0.08;
			if (walkFrame >= 2 * PI) walkFrame -= 2 * PI;
		}
		else {
			walkFrame = 0;
		}
	}
	else if ((gameState == 5 || gameState == 6) && appState == APP_MAP) {
		playerWalking = false;

		double moveSpeed = 1.2;
		double newX = playerX;
		double newY = playerY;

		if (isKeyPressed('w') || isKeyPressed('W') || isSpecialKeyPressed(GLUT_KEY_UP)) {
			newY += moveSpeed;
			playerDirection = 3;
			playerWalking = true;
		}
		if (isKeyPressed('s') || isKeyPressed('S') || isSpecialKeyPressed(GLUT_KEY_DOWN)) {
			newY -= moveSpeed;
			playerDirection = 0;
			playerWalking = true;
		}
		if (isKeyPressed('a') || isKeyPressed('A') || isSpecialKeyPressed(GLUT_KEY_LEFT)) {
			newX -= moveSpeed;
			playerDirection = 1;
			playerWalking = true;
		}
		if (isKeyPressed('d') || isKeyPressed('D') || isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
			newX += moveSpeed;
			playerDirection = 2;
			playerWalking = true;
		}

		// Boundary Clamping
		if (newX < 18.0) newX = 18.0;
		if (newX > SCREEN_WIDTH - 18.0) newX = SCREEN_WIDTH - 18.0;
		if (newY < 10.0) newY = 10.0;
		if (newY > SCREEN_HEIGHT - 48.0) newY = SCREEN_HEIGHT - 48.0;

		// Portal Collision Checking
		if (gameState == 5) {
			if (!isPortalSolid(newX, playerY)) playerX = newX;
			if (!isPortalSolid(playerX, newY)) playerY = newY;
		}
		else if (gameState == 6) {
			if (!isPortal2Solid(newX, playerY)) playerX = newX;
			if (!isPortal2Solid(playerX, newY)) playerY = newY;
		}

		if (playerWalking) {
			walkFrame += 0.08;
			if (walkFrame >= 2 * PI) walkFrame -= 2 * PI;
		}
		else {
			walkFrame = 0;
		}

	}


	// --- PORTAL 3 UPDATE ---
	else if (gameState == 7 && appState == APP_MAP) {

		updatePortal3Enemies();
		updatePortal3Enemy2();

		playerWalking = false;

		double moveSpeed = 1.2;
		double newX = playerX;
		double newY = playerY;

		if (isKeyPressed('w') || isKeyPressed('W') || isSpecialKeyPressed(GLUT_KEY_UP)) {
			newY += moveSpeed;
			playerDirection = 3;
			playerWalking = true;
		}
		if (isKeyPressed('s') || isKeyPressed('S') || isSpecialKeyPressed(GLUT_KEY_DOWN)) {
			newY -= moveSpeed;
			playerDirection = 0;
			playerWalking = true;
		}
		if (isKeyPressed('a') || isKeyPressed('A') || isSpecialKeyPressed(GLUT_KEY_LEFT)) {
			newX -= moveSpeed;
			playerDirection = 1;
			playerWalking = true;
		}
		if (isKeyPressed('d') || isKeyPressed('D') || isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
			newX += moveSpeed;
			playerDirection = 2;
			playerWalking = true;
		}
		
		// Boundary Clamping
		if (newX < 18.0) newX = 18.0;
		if (newX > SCREEN_WIDTH - 18.0) newX = SCREEN_WIDTH - 18.0;
		if (newY < 10.0) newY = 10.0;
		if (newY > SCREEN_HEIGHT - 48.0) newY = SCREEN_HEIGHT - 48.0;

		// Portal 3 Solid Collision Checking
		if (!isPortal3Solid(newX, playerY)) playerX = newX;
		if (!isPortal3Solid(playerX, newY)) playerY = newY;

		if (playerWalking) {
			walkFrame += 0.08;
			if (walkFrame >= 2 * PI) walkFrame -= 2 * PI;
		}
		else {
			walkFrame = 0;
		}
		if (isKeyPressed(' ') || isKeyPressed(' ')) {
			throwBlueFireball();
		}
		// Portal 3 Totem Interaction via [F]
		if (isKeyPressed('f') || isKeyPressed('F')) {
			if (playerX >= 200.0 && playerX <= 400.0 && playerY >= 560.0 && playerY <= 880.0 && !isTotemSolved) {
				appState = APP_RUNE_MANUAL;

				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) runeGrid[i][j] = 0;
				}
			}
		}
		if (areAllPortal3EnemiesDead() && isNearTopRightDoor(playerX, playerY)) {
			iSetColor(255, 215, 0);

			if (isKeyPressed('f') || isKeyPressed('F')) {
				gameState = 9; // Switch to Final Boss state
				// Set initial position for final boss arena if needed
				playerX = 500.0;
				playerY = 200.0;
				bossIntroTimer = 540;
			}
		}

	}
	else if (gameState == 9) {
		if (bossIntroTimer > 0) {
			// Phase 1: Intro Cutscene (Game is frozen)
			bossIntroTimer--;
		}
		else if (bossHealth <= 0) {
			// Phase 3: Outro Cutscene (Boss is dead, game freezes again)
			if (bossOutroTimer > 1) {
				bossOutroTimer--;
			}
			else if (bossOutroTimer == 1) {
				bossOutroTimer = 0;
				gameState = 11; // Cutscene finished, go to Game Cleared screen
			}
			else if (bossOutroTimer == 0) {
				// Trigger the timer the exact frame the boss dies
				bossOutroTimer = 360; // 2 phases * 3 seconds = 6 seconds total
			}
		}
		else {
			// Phase 2: ACTIVE BOSS FIGHT
			updateBattleMechanics(playerHealth, playerIFrames);

			playerWalking = false;
			double moveSpeed = 1.5;
			double newX = playerX;
			double newY = playerY;

			if (isKeyPressed('w') || isKeyPressed('W') || isSpecialKeyPressed(GLUT_KEY_UP)) {
				newY += moveSpeed; playerDirection = 3; playerWalking = true;
			}
			if (isKeyPressed('s') || isKeyPressed('S') || isSpecialKeyPressed(GLUT_KEY_DOWN)) {
				newY -= moveSpeed; playerDirection = 0; playerWalking = true;
			}
			if (isKeyPressed('a') || isKeyPressed('A') || isSpecialKeyPressed(GLUT_KEY_LEFT)) {
				newX -= moveSpeed; playerDirection = 1; playerWalking = true;
			}
			if (isKeyPressed('d') || isKeyPressed('D') || isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
				newX += moveSpeed; playerDirection = 2; playerWalking = true;
			}

			// Boundary Clamping
			if (newX < 30.0) newX = 30.0;
			if (newX > SCREEN_WIDTH - 30.0) newX = SCREEN_WIDTH - 30.0;
			if (newY < 30.0) newY = 30.0;
			if (newY > SCREEN_HEIGHT - 30.0) newY = SCREEN_HEIGHT - 30.0;

			playerX = newX;
			playerY = newY;

			// Fire Lightning Ball in the direction the character is facing
			if ((isKeyPressed('c') || isKeyPressed('C')) && lightningCollected) {
				throwLightningBall();
			}
		}
	}
	// Check for Player Death across active gameplay states
	if (playerHealth <= 0 && gameState != 10) {
		resetAllGameData(); // Immediately wipes savegame.txt and resets progress on death!
		gameState = 10;     // Switch to Game Over screen
	}
	// Check for Boss Victory in the final boss arena (gameState == 9)
}

int main() {
	iInitialize(1000, 1000, "Mystic Grove");

	menuBgImage = iLoadImage("menu.png");
	mainmap = iLoadImage("mainmap.png");
	heartFullImg = iLoadImage("full.png");
	heartHalfImg = iLoadImage("half.png");
	imgPortal1Map = iLoadImage("Portal1.png");
	slimeImg = iLoadImage("slime.png");
	slimeBulletImg = iLoadImage("bullet.png");
	bookImg = iLoadImage("book.png");
	portal3TextImg = iLoadImage("text1.png");
	manualImg = iLoadImage("manual.png");
	hintImg = iLoadImage("hint.png");
	lockedImg = iLoadImage("locked.png");
	solvedImg = iLoadImage("solved.png");
	imgPortal2Map = iLoadImage("map.png");
	imgPortal2Drones[0] = iLoadImage("enemy1.png");
	imgPortal2Drones[1] = iLoadImage("enemy2.png");
	imgPortal2Drones[2] = iLoadImage("enemy3.png");
	imgPortal2Drones[3] = iLoadImage("enemy4.png");
	imgPortal2Drones[4] = iLoadImage("enemy5.png");

	imgWeaponFront = iLoadImage("weapon_front.png");
	imgWeaponLeft = iLoadImage("weapon_left.png");
	imgWeaponRight = iLoadImage("weapon_right.png");
	imgWeaponBack = iLoadImage("weapon_back.png");

	imgFireball = iLoadImage("red_fireball.png");
	imgWaterball = iLoadImage("waterball.png");
	imgPortal3FullMap = iLoadImage("portal3map.png");
	portal3EnemyImg = iLoadImage("portal3enemy.png");
	portal3Enemy2Img = iLoadImage("portal3enemy2.png");
	blueFireballImg = iLoadImage("bluefireball.png");
	portal3LightningImg = iLoadImage("lightning.png");
	portal3TextImg = iLoadImage("entry.png");
	manualImg = iLoadImage("manual.png");
	imgLevelCleared = iLoadImage("clear.png");
	imgPuzzleSolved = iLoadImage("puzzle_solved.png");
	bgArenaImg = iLoadImage("finalbossmap.png");
	bossImg = iLoadImage("boss.png");
	bossGreenSpellImg = iLoadImage("hakai.png");
	trappedFairyImg = iLoadImage("rescue.png");
	imgGameCleared = iLoadImage("win.png");
	imgGameOver = iLoadImage("over.png");
	imgVillainDefeat = iLoadImage("villain3.png");
	imgVillainIntro2 = iLoadImage("villain2.png");
	imgVillainIntro1 = iLoadImage("villain1.png");
	imgFairyHelped = iLoadImage("helped.png");
	imgFairyHelp = iLoadImage("help.png");
	storyImg = iLoadImage("story.png");
	creditImg = iLoadImage("credit.png");
	setupBoxPositions();
	initPortal2Drones();
	initPortalSlimes();

	checkSaveFile();
	playerX = MAIN_SPAWN_X;
	playerY = MAIN_SPAWN_Y;

	iSetTimer(16, fixedUpdate);
	iSetTimer(15, updatePortalSlimes);
	iSetTimer(15, updatePortalSpell);
	iSetTimer(3000, shootSlimeBullets);
	iSetTimer(15, updatePortal2Drones);
	iSetTimer(3000, shootPortal2DroneBullets);

	iStart();
	return 0;
}
