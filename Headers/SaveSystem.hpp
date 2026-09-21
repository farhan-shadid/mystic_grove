#pragma once
#include <stdio.h>

bool saveExists = false;

// Pull these variables from iMain.cpp and Character.hpp
extern double playerX;
extern double playerY;
extern int playerHealth;
extern int maxHealth;

// Core Progression Flags Only
extern bool portal1Cleared;
extern bool portal2Cleared;
extern bool portal2Unlocked;
extern bool portal3Unlocked;
extern bool spellCollected;
extern bool isTotemSolved;

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

		// Removed isPortalOpen from the save format
		fprintf(fp, "%d %d %d %d %d %d\n",
			portal1Cleared, portal2Cleared, portal2Unlocked,
			portal3Unlocked, spellCollected, isTotemSolved);

		fclose(fp);
	}
}

void loadGame() {
	FILE* fp = fopen("savegame.txt", "r");
	if (fp != NULL) {
		int p1C, p2C, p2U, p3U, sC, tS;

		fscanf(fp, "%lf %lf", &playerX, &playerY);
		fscanf(fp, "%d %d", &playerHealth, &maxHealth);

		// Removed isPortalOpen from the load format
		fscanf(fp, "%d %d %d %d %d %d", &p1C, &p2C, &p2U, &p3U, &sC, &tS);

		portal1Cleared = p1C;
		portal2Cleared = p2C;
		portal2Unlocked = p2U;
		portal3Unlocked = p3U;
		spellCollected = sC;
		isTotemSolved = tS;

		fclose(fp);
	}

}

void clearSaveData() {
	// Deletes the file from the hard drive
	remove("savegame.txt");

	// Tells the game UI to switch back to "NEW GAME"
	saveExists = false;
}