#pragma once
int runeGrid[3][3] = { 0 };
bool isTotemSolved = false;

inline void toggleRune(int r, int c) {
	runeGrid[r][c] ^= 1;
	if (r - 1 >= 0) runeGrid[r - 1][c] ^= 1;
	if (r + 1 < 3)  runeGrid[r + 1][c] ^= 1;
	if (c - 1 >= 0) runeGrid[r][c - 1] ^= 1;
	if (c + 1 < 3)  runeGrid[r][c + 1] ^= 1;
}
inline void drawRunePuzzle() {
	
	iSetColor(20, 25, 30);
	iFilledRectangle(0, 0, 1000, 1000);

	iSetColor(255, 255, 255);
	iText(250, 800, "IGNITE ALL 9 RUNES TO PROVE YOUR WORTH", GLUT_BITMAP_TIMES_ROMAN_24);

	int startX = 330;
	int startY = 300;
	int tileSize = 100;
	int gap = 15;

	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			int x = startX + c * (tileSize + gap);
			int y = startY + (2 - r) * (tileSize + gap);

			if (runeGrid[r][c] == 1) {
				iSetColor(0, 255, 255); 
			}
			else {
				iSetColor(50, 55, 60);  
			}

			iFilledRectangle(x, y, tileSize, tileSize);

			iSetColor(200, 200, 200); 
			iRectangle(x, y, tileSize, tileSize);
		}
	}
}