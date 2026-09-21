#pragma once
extern bool saveExists;
extern int gameState;
extern int menuBgImage;

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
	iSetColor(243, 206, 161);
	iFilledRectangle(200, 200, 600, 600);
	iSetColor(255, 0, 0);
	iText(420, 750, "-- STORY --", GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(0, 0, 0);
	iText(250, 650, "A great evil has corrupted the Mystic Grove...", GLUT_BITMAP_HELVETICA_18);
	iText(250, 630, "The holy spirit has been captured...", GLUT_BITMAP_HELVETICA_18);
	iText(250, 610, "You are the holy saint whom the fairy prophesied about", GLUT_BITMAP_HELVETICA_18);
	iText(250, 590, "You must rescue the holy spirit....", GLUT_BITMAP_HELVETICA_18);
	iText(250, 570, "No matter the obstacle that may stand in your way...", GLUT_BITMAP_HELVETICA_18);
	iText(250, 550, "You must overcome 'em all to save the holy spirit!", GLUT_BITMAP_HELVETICA_18);
	iText(250, 530, "You are the last hope the forest has...", GLUT_BITMAP_HELVETICA_18);
	iText(250, 510, "Shall you fail to save the holy spirit..........", GLUT_BITMAP_HELVETICA_18);
	iText(250, 490, " ", GLUT_BITMAP_HELVETICA_18);
	iText(250, 470, "All the lives in this forest will be doomed..!!", GLUT_BITMAP_HELVETICA_18);


}

void drawCreditsPopup() {
	drawMenuScreen();
	iSetColor(243, 206, 161);
	iFilledRectangle(300, 300, 400, 400);
	iSetColor(255, 0, 0);
	iText(420, 650, "-- CREDITS --", GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(0, 0, 0);
	iText(350, 550, "Faheem Shahrier", GLUT_BITMAP_HELVETICA_18);
	iText(350, 530, "ID: 00725105101061", GLUT_BITMAP_HELVETICA_18);
	iText(350, 500, "Maimuna Alam", GLUT_BITMAP_HELVETICA_18);
	iText(350, 480, "ID: 00725105101077", GLUT_BITMAP_HELVETICA_18);
	iText(350, 450, "Farhan Shadid", GLUT_BITMAP_HELVETICA_18);
	iText(350, 430, "ID: 00725105101063", GLUT_BITMAP_HELVETICA_18);
}