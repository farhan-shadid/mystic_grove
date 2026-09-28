#ifndef MAP_AND_PUZZLE_HPP
#define MAP_AND_PUZZLE_HPP

extern int mainmap;

bool isPortalOpen = false;

const int ROWS = 25;
const int COLS = 25;
const int TILE_SIZE = 40;

enum AppState { APP_MAP, APP_PUZZLE, APP_RUNE_MANUAL, APP_RUNE, APP_INFO };
AppState appState = APP_MAP;

#define NUM_BOXES 5
#define BOX_SIZE 100
#define TICK_MS 20
#define ROUND_TICKS 150
#define WIN_SCORE 5
#define MAX_MISS 5

// 0=Dirt Path, 1=Grass, 2=Stones, 3=Tree, 4=Portal(2x2), 5=Puzzle Box(2x2), 6=Giant Tree(4x4)
const int rawLayout[25][25] = {
	{ 3, 3, 3, 3, 2, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 2, 3, 3, 3, 3, 3 },
	{ 3, 3, 1, 2, 1, 1, 1, 2, 1, 1, 6, 6, 6, 6, 1, 2, 1, 1, 1, 1, 2, 3, 3, 3, 3 },
	{ 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3 },
	{ 3, 1, 1, 4, 4, 1, 1, 1, 1, 1, 6, 6, 6, 6, 1, 1, 1, 1, 1, 4, 4, 1, 1, 3, 3 },
	{ 2, 1, 1, 4, 4, 1, 1, 1, 1, 1, 6, 6, 6, 6, 1, 1, 1, 1, 1, 4, 4, 1, 1, 2, 3 },
	{ 1, 3, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 3, 1, 1, 1 },
	{ 1, 3, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 3, 1, 1, 1 },
	{ 1, 1, 3, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 3, 1, 1, 1, 2, 1 },
	{ 1, 1, 3, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 3, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 3 },
	{ 3, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 3, 1, 1 },
	{ 3, 1, 1, 0, 1, 1, 1, 1, 1, 1, 5, 5, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 3, 1, 1 },
	{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 5, 5, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
	{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
	{ 1, 0, 1, 1, 1, 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 2, 1, 1, 1, 0, 1, 1, 1, 1 },
	{ 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 },
	{ 3, 1, 1, 2, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 2, 1, 1, 1, 3, 1, 1 },
	{ 3, 3, 1, 1, 1, 0, 0, 1, 1, 1, 3, 3, 1, 1, 1, 0, 0, 1, 1, 1, 1, 3, 3, 1, 1 },
	{ 3, 3, 3, 1, 1, 0, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 0, 1, 1, 1, 3, 3, 3, 1, 1 },
	{ 3, 3, 3, 1, 0, 1, 1, 2, 1, 1, 0, 0, 1, 1, 2, 1, 1, 0, 1, 1, 3, 3, 3, 3, 1 },
	{ 3, 3, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 3, 3, 3, 1 },
	{ 3, 1, 1, 2, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 3, 3, 1 },
	{ 1, 1, 2, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 2, 1, 1, 1, 3, 1 },
	{ 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3 },
	{ 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3 }
};

// Returns true if the player is within a 60-pixel radius of the Big Tree
inline bool isNearBigTree(double px, double py) {
	double treeX = 500.0;
	double treeY = 760.0;

	double dx = px - treeX;
	double dy = py - treeY;

	return (dx * dx + dy * dy) <= (60.0 * 60.0);
}

// Collision
inline bool isSolid(double x, double y) {
	int col = (int)(x / TILE_SIZE);
	int row = ROWS - 1 - (int)(y / TILE_SIZE);

	if (row < 0 || row >= ROWS || col < 0 || col >= COLS) return true;

	int tile = rawLayout[row][col];
	// 2: Stones, 3: Tree, 4: Portal, 5: Puzzle Box, 6: Giant Tree
	return (tile == 2 || tile == 3 || tile == 4 || tile == 5 || tile == 6);
}

// Puzzle Area 
inline bool isNearPuzzle(double x, double y) {
	int centerCol = (int)(x / TILE_SIZE);
	int centerRow = ROWS - 1 - (int)(y / TILE_SIZE);

	for (int r = centerRow - 1; r <= centerRow + 1; r++) {
		for (int c = centerCol - 1; c <= centerCol + 1; c++) {
			if (r >= 0 && r < ROWS && c >= 0 && c < COLS) {
				if (rawLayout[r][c] == 5) return true;
			}
		}
	}
	return false;
}

struct Box {
	int x, y;
	int shapeType;
};

Box boxes[NUM_BOXES];
int correctIndex;
int targetShape;

int score = 0;
int miss = 0;
int roundTimer = 0;
char txt[50];

inline void setupBoxPositions() {
	int margin = 100;
	int gap = 75;
	int rowY = 300;

	for (int i = 0; i < NUM_BOXES; i++) {
		boxes[i].x = margin + i * (BOX_SIZE + gap);
		boxes[i].y = rowY;
	}
}

inline void startNewRound() {
	int availableShapes[5] = { 0, 1, 2, 3, 4 };
	for (int i = 4; i > 0; i--) {
		int j = rand() % (i + 1);
		int temp = availableShapes[i];
		availableShapes[i] = availableShapes[j];
		availableShapes[j] = temp;
	}

	for (int i = 0; i < NUM_BOXES; i++) {
		boxes[i].shapeType = availableShapes[i];
	}

	correctIndex = rand() % NUM_BOXES;
	targetShape = boxes[correctIndex].shapeType;
	roundTimer = 0;
}

inline void checkGameEnd() {
	if (score >= WIN_SCORE) {
		isPortalOpen = true;
		appState = APP_MAP;
		score = 0;
		miss = 0;
	}
	else if (miss >= MAX_MISS) {
		isPortalOpen = false;
		appState = APP_MAP;
		score = 0;
		miss = 0;
	}
}

inline void gameTick() {
	if (appState != APP_PUZZLE) return;

	roundTimer++;
	if (roundTimer >= ROUND_TICKS) {
		miss++;
		checkGameEnd();
		if (appState == APP_PUZZLE) startNewRound();
	}
}

inline void drawShape(int shapeType, double centerX, double centerY, double size) {
	if (shapeType == 0) {
		iSetColor(230, 80, 80);
		iFilledCircle(centerX, centerY, size / 2.5);
	}
	else if (shapeType == 1) {
		iSetColor(80, 150, 230);
		iFilledRectangle(centerX - size / 2.5, centerY - size / 2.5, size / 1.25, size / 1.25);
	}
	else if (shapeType == 2) {
		iSetColor(80, 220, 100);
		double tx[] = { centerX, centerX - size / 2.2, centerX + size / 2.2 };
		double ty[] = { centerY + size / 2.2, centerY - size / 2.2, centerY - size / 2.2 };
		iFilledPolygon(tx, ty, 3);
	}
	else if (shapeType == 3) {
		iSetColor(240, 200, 60);
		double dx[] = { centerX, centerX + size / 2.2, centerX, centerX - size / 2.2 };
		double dy[] = { centerY + size / 2.2, centerY, centerY - size / 2.2, centerY };
		iFilledPolygon(dx, dy, 4);
	}
	else if (shapeType == 4) {
		iSetColor(200, 90, 220);
		double headHeight = size / 2.0;
		double headWidth = size / 2.2;
		double stemWidth = size / 5.0;
		double stemHeight = size / 2.0;

		double px[] = {
			centerX, centerX + headWidth, centerX + stemWidth, centerX + stemWidth, centerX - stemWidth, centerX - stemWidth, centerX - headWidth
		};
		double py[] = {
			centerY + headHeight, centerY, centerY, centerY - stemHeight, centerY - stemHeight, centerY, centerY
		};
		iFilledPolygon(px, py, 7);
	}
}

// 4. MAP RENDERING  
struct PortalMap {
	void draw() {
		// Draw main map background image only
		iShowImage(0, 0, COLS * TILE_SIZE, ROWS * TILE_SIZE, mainmap);
	}
};

PortalMap currentLevel;

inline void drawPuzzleMinigame() {
	iSetColor(0, 0, 0);
	iFilledRectangle(0, 0, 1000, 1000);

	for (int i = 0; i < NUM_BOXES; i++) {
		iSetColor(30, 30, 30);
		iFilledRectangle(boxes[i].x, boxes[i].y, BOX_SIZE, BOX_SIZE);
		iSetColor(255, 255, 255);
		iRectangle(boxes[i].x, boxes[i].y, BOX_SIZE, BOX_SIZE);

		drawShape(boxes[i].shapeType, boxes[i].x + BOX_SIZE / 2, boxes[i].y + BOX_SIZE / 2, BOX_SIZE);
	}

	int targetX = 500 - BOX_SIZE / 2;
	int targetY = 650;

	iSetColor(255, 255, 255);
	iText(targetX - 40, targetY + BOX_SIZE + 25, (char*)"MATCH THIS SHAPE:", GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(30, 30, 30);
	iFilledRectangle(targetX, targetY, BOX_SIZE, BOX_SIZE);
	iSetColor(255, 255, 255);
	iRectangle(targetX, targetY, BOX_SIZE, BOX_SIZE);

	drawShape(targetShape, targetX + BOX_SIZE / 2, targetY + BOX_SIZE / 2, BOX_SIZE);

	sprintf_s(txt, "SCORE : %d", score);
	iText(750, 900, txt, GLUT_BITMAP_TIMES_ROMAN_24);

	sprintf_s(txt, "MISS : %d", miss);
	iText(750, 860, txt, GLUT_BITMAP_TIMES_ROMAN_24);

	int timeLeftTicks = ROUND_TICKS - roundTimer;
	sprintf_s(txt, "TIME : %d", (timeLeftTicks * TICK_MS) / 1000 + 1);
	iText(750, 820, txt, GLUT_BITMAP_TIMES_ROMAN_24);
}

#endif // MAP_AND_PUZZLE_HPP