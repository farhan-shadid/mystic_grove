#pragma once
#define _CRT_SECURE_NO_WARNINGS // Silences Visual Studio warnings for fopen/fscanf
#include <stdio.h>

bool saveExists = false;

// Pull these variables from iMain.cpp and Character.hpp
extern double playerX;
extern double playerY;
extern int playerHealth;
extern int maxHealth;

// Core Progression Flags
extern bool portal1Cleared;
extern bool portal2Cleared;
extern bool portal2Unlocked;
extern bool portal3Unlocked;
extern bool spellCollected;      // Portal 1 Reward
extern bool isTotemSolved;       // Portal 3 Puzzle
extern bool lightningCollected;  // Portal 3 Reward 

void checkSaveFile() {
	FILE* fp = fopen("savegame.txt", "r");
	if (fp != NULL) {
		saveExists = true;
		fclose(fp);
	}
	else {
		saveExists = false;
	}
}

void saveGame() {
	FILE* fp = fopen("savegame.txt", "w");
	if (fp != NULL) {
		fprintf(fp, "%lf %lf\n", playerX, playerY);
		fprintf(fp, "%d %d\n", playerHealth, maxHealth);

		fprintf(fp, "%d %d %d %d %d %d %d\n",
			portal1Cleared, portal2Cleared, portal2Unlocked,
			portal3Unlocked, spellCollected, isTotemSolved, lightningCollected);

		fclose(fp);
	}
}

void loadGame() {
	FILE* fp = fopen("savegame.txt", "r");
	if (fp != NULL) {
		int p1C, p2C, p2U, p3U, sC, tS, lC;

		fscanf(fp, "%lf %lf", &playerX, &playerY);
		fscanf(fp, "%d %d", &playerHealth, &maxHealth);

		fscanf(fp, "%d %d %d %d %d %d %d", &p1C, &p2C, &p2U, &p3U, &sC, &tS, &lC);

		// Explicit boolean casting (!= 0) to prevent C4800 performance warnings
		portal1Cleared = (p1C != 0);
		portal2Cleared = (p2C != 0);
		portal2Unlocked = (p2U != 0);
		portal3Unlocked = (p3U != 0);
		spellCollected = (sC != 0);
		isTotemSolved = (tS != 0);
		lightningCollected = (lC != 0);

		fclose(fp);
	}
}

void clearSaveData() {
	// Deletes the file from the hard drive
	remove("savegame.txt");

	// Tells the game UI to switch back to "NEW GAME"
	saveExists = false;
}

extern bool isPortalOpen;
extern double bossHealth;
extern double maxBossHealth;
extern bool bossActive;
extern bool rightGateOpened;
void initPortalSlimes();
void initPortal2Drones();

inline void resetAllGameData() {
	clearSaveData(); // Deletes savegame.txt and sets saveExists = false

	playerX = 460.0;
	playerY = 100.0;
	playerHealth = 6;
	maxHealth = 6;

	isPortalOpen = false;
	portal1Cleared = false;
	portal2Cleared = false;
	portal2Unlocked = false;
	portal3Unlocked = false;
	spellCollected = false;
	isTotemSolved = false;
	lightningCollected = false;
	rightGateOpened = false;

	bossHealth = maxBossHealth;
	bossActive = true;

	initPortalSlimes();
	initPortal2Drones();
}
