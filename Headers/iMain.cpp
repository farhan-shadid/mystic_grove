#include "iGraphics.h"

int gameState = 0;
int menuBgImage;
int playerHealth = 10;
int maxHealth = 10;
int victoryTextTimer = 0;
int playerIFrames = 0;
int levelClearTimer = 0;
int slimeImg = -1;
int slimeBulletImg = -1; 
int stoneImg = -1;
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
int fireballImg = -1;


// --- PORTAL UNLOCK STATES ---
bool portal1Cleared = false;
bool portal2Cleared = false;
bool portal2Unlocked = false; // Unlocks after Portal 1
bool portal3Unlocked = false; // Unlocks after Portal 2
extern bool spellCollected;
extern bool isTotemSolved;

#include "SaveSystem.hpp"
#include "Menu.hpp"
#include "Portal.hpp"
#include "Mainmap.hpp"
#include "Character.hpp"
#include "portal2.hpp"
#include "portal3.hpp"
#include "RunePuzzle.hpp"

void drawLevelClearedOverlay() {
	if (levelClearTimer > 0) {
		iSetColor(0, 0, 0);
		iFilledRectangle(250, 420, 500, 150);

		iSetColor(255, 215, 0);
		iRectangle(250, 420, 500, 150);

		if (gameState == 5) {
			iSetColor(255, 255, 255);
			iText(400, 520, "LEVEL CLEARED!", GLUT_BITMAP_TIMES_ROMAN_24);

			iSetColor(255, 100, 50);
			iText(410, 480, "Acquired fire spell", GLUT_BITMAP_HELVETICA_18);

			iSetColor(150, 150, 150);
			iText(360, 450, "Skill ROCK THROW is now gone", GLUT_BITMAP_HELVETICA_18);
		}
		else {
			iSetColor(255, 255, 255);
			iText(410, 490, "LEVEL CLEARED!", GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}
}

void iDraw() {
	iClear();

	if (gameState == 0) drawMenuScreen();
	else if (gameState == 2) {
		if (appState == APP_MAP) {
			currentLevel.draw();
			drawPlayer();

			// Display the general map instruction for 3 seconds
			if (mapHintTimer > 0) {
				if (hintImg != -1) {
					// Centers the wide banner at the top of the screen
					iShowImage(200, 750, 600, 200, hintImg);
				}
			}

		}
		else if (appState == APP_PUZZLE) {
			drawPuzzleMinigame();
		}


		// --- PORTAL 1 (Top-Left) ---
		if (playerX < 200 && playerY > 700) {
			if (portal1Cleared) {
				if (solvedImg != -1) iShowImage(70, 840, 180, 120, solvedImg);
			}
			else if (!isPortalOpen) { // Locked if main puzzle isn't solved
				if (lockedImg != -1) iShowImage(70, 840, 180, 120, lockedImg);
			}
		}

		// --- PORTAL 2 (Top-Right) ---
		if (playerX > 800 && playerY > 700) {
			if (portal2Cleared) {
				if (solvedImg != -1) iShowImage(760, 840, 180, 120, solvedImg);
			}
			else if (!portal2Unlocked) { // Locked before Portal 1 is solved
				if (lockedImg != -1) iShowImage(760, 840, 180, 120, lockedImg);
			}
		}

		// --- PORTAL 3 (Near Big Tree) ---
		if (isNearBigTree(playerX, playerY)) {
			if (isTotemSolved) {
				if (solvedImg != -1) iShowImage(410, 820, 180, 120, solvedImg);
			}
			else if (!portal3Unlocked) { // Locked before Portal 2 is solved
				if (lockedImg != -1) iShowImage(410, 820, 180, 120, lockedImg);
			}
		}
	}
	else if (gameState == 3) drawStoryPopup();
	else if (gameState == 4) drawCreditsPopup();
	else if (gameState == 5) {
		drawPortal1Map();
		drawPlayer();
	}
	else if (gameState == 6) {
		// Draw Level from portal2.hpp
		drawPortal2Map();
		drawPlayer();
	}

	else if (gameState == 7) {
		// Draw Level from portal3.hpp
		drawPortal3Map();
		drawPlayer();
	}

	//  DRAW ACTIVE PROJECTILES 
	if (gameState == 2 || gameState == 5 || gameState == 6 || gameState == 7) {
		for (int i = 0; i < MAX_STONES; i++) {
			if (playerStones[i].active) {
				if (spellCollected) {
					// Draw the Fireball Upgrade
					if (fireballImg != -1) {
						// Offset by 12 to center the 24x24 image exactly on the collision point
						iShowImage(playerStones[i].x - 12, playerStones[i].y - 12, 24, 24, fireballImg);
					}
				}
				else {
					// Draw the Default Rock
					iSetColor(169, 169, 169);
					iFilledCircle(playerStones[i].x, playerStones[i].y, 6);

					iSetColor(211, 211, 211);
					iFilledCircle(playerStones[i].x - 2, playerStones[i].y + 2, 2);
				}
			}
		}
	}

	//  STONE X SLIME  
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
							slimes[j].active = 0; // Slime disappear
							playerStones[i].active = false; // Stone shatters
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

		// REQUIRES BOTH: All slimes dead AND the spell book collected!
		if (!slimesRemaining && spellCollected) {
			if (levelClearTimer == 0) {
				levelClearTimer = 300; 
			}
		}
	}

	//  STONE TO DRONE COLLISION (Portal 2) 
	if (gameState == 6) {
		for (int i = 0; i < MAX_STONES; i++) {
			if (playerStones[i].active) {
				for (int j = 0; j < NUM_PORTAL2_DRONES; j++) {

					double droneCenterX = portal2Drones[j].x + 20.0;
					double droneCenterY = portal2Drones[j].y + 21.0;

					double dx = playerStones[i].x - droneCenterX;
					double dy = playerStones[i].y - droneCenterY;

					if (dx * dx + dy * dy <= 22.0 * 22.0) {
						portal2Drones[j].bulletActive = 0;
						portal2Drones[j].x = -9999.0; // Disable drone off-screen

						playerStones[i].active = false; // Stone shatters
						break;
					}
				}
			}
		}
	}

	//  WIN CONDITION: PORTAL 2  
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

	//  LEVEL CLEAR TIMER 
	if (levelClearTimer > 0) {
		drawLevelClearedOverlay();
	}

	if (gameState == 2 || gameState == 5 || gameState == 6 || gameState == 7) {
		drawHealthUI();
	}
	// Portal 3
	if (gameState == 7) {
		if (appState == APP_MAP) {
			double dx = playerX - 500.0;
			double dy = playerY - 500.0;
			if (dx * dx + dy * dy <= 80.0 * 80.0) {
				if (!isTotemSolved) {
				}
				else if (victoryTextTimer > 0) {
					iSetColor(0, 255, 255);
					// Centered text slightly higher than the totem
					iText(350, 560, (char*)"The Runes glow brightly. You've solved it!", GLUT_BITMAP_HELVETICA_18);
				}
			}
		}
		else if (appState == APP_RUNE) {
			drawRunePuzzle();
		}
		else if (appState == APP_INFO) {
			// Renders the stylized parchment text image
			if (portal3TextImg != -1) {
				// Drawn at (200, 300) with a 600x400 size to match the old popup dimensions
				iShowImage(200, 300, 600, 400, portal3TextImg);
			}
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
						// RESUME OR NEW GAME
						if (saveExists) {
							loadGame();
						}
						else {
							// Reset to default New Game state
							playerX = 350.0;
							playerY = 200.0;
							playerHealth = 10;
							maxHealth = 10;
							portal1Cleared = false;
							portal2Unlocked = false;
						}
						gameState = 2;
						mapHintTimer = 180;
					}
					else if (i == 1) gameState = 3;  // STORY
					else if (i == 2) gameState = 4;  // CREDITS
					else if (i == 3) {
						// CLEAR DATA
						clearSaveData();

						// Reset all live variables to a completely fresh state
						playerX = 350.0;
						playerY = 200.0;
						playerHealth = 10;
						maxHealth = 10;
						portal1Cleared = false;
						portal2Cleared = false;
						portal2Unlocked = false;
						portal3Unlocked = false;
						spellCollected = false;
						isTotemSolved = false;
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

		// 3. STORY POPUP 
		else if (gameState == 3) {
			if (mx < 200 || mx > 800 || my < 200 + 50 || my > 800 + 50) {
				gameState = 0;
			}
		}

		// 4. CREDITS POPUP
		else if (gameState == 4) {
			if (mx < 300 || mx > 700 || my < 300 + 50 || my > 700 + 50) {
				gameState = 0;
			}
		}
		// RUNE PUZZLE 
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
							maxHealth += 2;
							playerHealth = maxHealth;
							appState = APP_MAP;
							victoryTextTimer = 180;
						}
						break;
					}
				}
			}
		}
		// Popup exit
		else if (gameState == 7 && appState == APP_INFO) {
			if (mx < 200 || mx > 800 || my < 300 || my > 700) {
				appState = APP_MAP;
			}
		}
	}
}

void iKeyboard(unsigned char key) {}
void iSpecialKeyboard(unsigned char key) {}
void iMouseMove(int mx, int my) {}
void iPassiveMouseMove(int mx, int my) {}

void fixedUpdate() {
	if (victoryTextTimer > 0) {
		victoryTextTimer--;
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
		// When the 3-second portal clear timer hits zero, trigger the teleport
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
			playerX = 500.0;
			playerY = 500.0;
			mapHintTimer = 180; // Trigger the 3-second map hint display
			saveGame();
			saveExists = true;
		}
	}

	//  FIRE A PROJECTILE 
	if (isKeyPressed(' ') && throwCooldown == 0) {
		for (int i = 0; i < MAX_STONES; i++) {
			if (!playerStones[i].active) {
				playerStones[i].active = true;
				playerStones[i].x = playerX + 20.0;
				playerStones[i].y = playerY + 20.0;
				playerStones[i].direction = playerDirection;
				throwCooldown = 20;
				break;
			}
		}
	}

	//  MOVE ACTIVE STONES 
	for (int i = 0; i < MAX_STONES; i++) {
		if (playerStones[i].active) {
			double speed = 8.0;

			if (playerStones[i].direction == 3) playerStones[i].y += speed;      // UP
			else if (playerStones[i].direction == 0) playerStones[i].y -= speed; // DOWN
			else if (playerStones[i].direction == 1) playerStones[i].x -= speed; // LEFT
			else if (playerStones[i].direction == 2) playerStones[i].x += speed; // RIGHT

			if (playerStones[i].x < 0 || playerStones[i].x > 1000 ||
				playerStones[i].y < 0 || playerStones[i].y > 1000) {
				playerStones[i].active = false;
			}
		}
	}

	if (gameState == 2) {
		if (appState == APP_MAP) {
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

			// Open Minigame
			if (isKeyPressed('f') || isKeyPressed('F')) {
				if (isNearPuzzle(playerX, playerY)) {
					appState = APP_PUZZLE;
					score = 0;
					miss = 0;
					startNewRound();
				}
			}

			// Enter Portal 1 
			if (isPortalOpen && !portal1Cleared && (isKeyPressed('f') || isKeyPressed('F'))) {
				if (playerX < 200 && playerY > 700) {
					gameState = 5;
					playerX = 500.0;
					playerY = 100.0;
				}
			}

			// Enter Portal 2 
			if (portal2Unlocked && !portal2Cleared && (isKeyPressed('f') || isKeyPressed('F'))) {
				if (playerX > 800 && playerY > 700) {
					gameState = 6;
					playerX = 500.0;
					playerY = 100.0;
				}
			}

			// Enter Portal 3
			if (portal3Unlocked && !isTotemSolved && (isKeyPressed('f') || isKeyPressed('F'))) {
				if (isNearBigTree(playerX, playerY)) {
					gameState = 7;
					playerX = 500.0;
					playerY = 50.0;
					appState = APP_INFO;
					return;
				}
			}

			// Screen Boundary 
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
		}
		else if (appState == APP_PUZZLE) {
			gameTick();
		}
	}
	else if ((gameState == 5 || gameState == 6 || gameState == 7) && appState == APP_MAP) {
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
		else if (gameState == 7) {
			if (!isPortal3Solid(newX, playerY)) playerX = newX;
			if (!isPortal3Solid(playerX, newY)) playerY = newY;
		}

		if (playerWalking) {
			walkFrame += 0.08;
			if (walkFrame >= 2 * PI) walkFrame -= 2 * PI;
		}
		else {
			walkFrame = 0;
		}

		// Portal 3 Totem Interaction
		if (gameState == 7 && (isKeyPressed('f') || isKeyPressed('F'))) {
			double dx = playerX - 500.0;
			double dy = playerY - 500.0;
			if (dx * dx + dy * dy <= 80.0 * 80.0 && !isTotemSolved) {
				appState = APP_RUNE;

				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) runeGrid[i][j] = 0;
				}
			}
		}
	}
}


int main() {
	iInitialize(1000, 1000, "Mystic Grove");

	menuBgImage = iLoadImage("menu.png");
	heartFullImg = iLoadImage("full.png");
	heartHalfImg = iLoadImage("half.png");
	stoneImg = iLoadImage("stone.png");
	slimeImg = iLoadImage("slime.png");       
	slimeBulletImg = iLoadImage("bullet.png"); 
	bookImg = iLoadImage("book.png");
	portal3TextImg = iLoadImage("text1.png");
	manualImg = iLoadImage("manual.png");
	hintImg = iLoadImage("hint.png"); 
	lockedImg = iLoadImage("locked.png");
	solvedImg = iLoadImage("solved.png");
	fireballImg = iLoadImage("fireball.png");
	setupBoxPositions();

	initPortalSlimes();
	initPortal2Drones();

	checkSaveFile();

	iSetTimer(16, fixedUpdate);

	// Portal 1 Slimes
	iSetTimer(15, updatePortalSlimes);
	iSetTimer(15, updatePortalSpell);
	iSetTimer(3000, shootSlimeBullets);

	// Portal 2 Drones
	iSetTimer(15, updatePortal2Drones);
	iSetTimer(3000, shootPortal2DroneBullets);

	iStart();
	return 0;
}
