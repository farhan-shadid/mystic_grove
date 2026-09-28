#pragma once
extern bool saveExists;
extern int gameState;
extern int menuBgImage;
extern int storyImg;
extern int creditImg;
struct MenuButton {
	int x, y, width, height;
	char label[20];
};

MenuButton menuBtns[4] = {
	{ 400, 520, 200, 50, "  ENTER PORTAL" },
	{ 400, 440, 200, 50, "        STORY" },
	{ 400, 360, 200, 50, "       CREDITS" },
	{ 400, 280, 200, 50, "    CLEAR DATA" }
};

void drawBrickButton(int x, int y, int w, int h, char* text) {

	iSetColor(85, 60, 42);
	iFilledRectangle(x, y, w, h);

	iSetColor(20, 5, 5);
	iRectangle(x, y, w, h);
	iLine(x, y + (h / 2), x + w, y + (h / 2));
	iLine(x + (w / 3), y + (h / 2), x + (w / 3), y + h);
	iLine(x + (w / 3) * 2, y, x + (w / 3) * 2, y + (h / 2));

	iSetColor(247, 174, 122);

	iText(x + 25, y + 18, text, GLUT_BITMAP_HELVETICA_18);
}

void drawMenuScreen() {
	iShowImage(0, 0, 1000, 1000, menuBgImage);

	for (int i = 0; i < 4; i++) {
		// Intercept the first button (Index 0)
		if (i == 0) {
			if (saveExists) {
				drawBrickButton(menuBtns[i].x, menuBtns[i].y, menuBtns[i].width, menuBtns[i].height, (char*)"      RESUME");
			}
			else {
				drawBrickButton(menuBtns[i].x, menuBtns[i].y, menuBtns[i].width, menuBtns[i].height, (char*)"    NEW GAME");
			}
		}
		// Draw the rest of the buttons normally
		else {
			drawBrickButton(menuBtns[i].x, menuBtns[i].y, menuBtns[i].width, menuBtns[i].height, menuBtns[i].label);
		}
	}
}

void drawStoryPopup() {
	drawMenuScreen();
	if (storyImg != -1) {
		iShowImage(100, 200, 800, 560, storyImg);
	}
}

void drawCreditsPopup() {
	drawMenuScreen();
	if (creditImg != -1) {
		iShowImage(100, 200, 800, 560, creditImg);
	}
}
