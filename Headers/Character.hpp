#ifndef MYSTIC_GROVE_HPP
#define MYSTIC_GROVE_HPP

#include <math.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000


#define PI 3.14159265358979323846

extern int heartFullImg;
extern int heartHalfImg;
// ======================================================
// PLAYER POSITION
// playerX, playerY = character's FOOT/GROUND position
// ======================================================

double playerX = 350.0;
double playerY = 200.0;


// ======================================================
// PLAYER DIRECTION
//
// 0 = FRONT, 1 = LEFT, 2 = RIGHT, 3 = BACK
// ======================================================

int playerDirection = 0;


// ======================================================
// WALKING ANIMATION
// ======================================================

bool playerWalking = false;
double walkFrame = 0;


// ======================================================
// CHARACTER SIZE (Scaled up 3x from original)
// ======================================================

#define LEG_LENGTH 10.8
#define LEG_WIDTH 3.6

#define ARM_LENGTH 8.7
#define ARM_WIDTH 3.0

#define BODY_WIDTH 15.6
#define BODY_HEIGHT 15.6

#define HEAD_RADIUS 8.7

// 1. Define the blueprint for a projectile
struct Stone {
	double x;
	double y;
	bool active;    // Is it currently flying?
	int direction;  // Which way is it going?
};

// 2. Create the Object Pool
const int MAX_STONES = 5;
Stone playerStones[MAX_STONES];

// 3. Prevent rapid-fire machine gun stones
int throwCooldown = 0;


// ======================================================
// COLORS
// ======================================================

inline void skin() { iSetColor(255, 205, 165); }
inline void hair() { iSetColor(90, 60, 40); }
inline void green() { iSetColor(50, 95, 45); }
inline void darkGreen() { iSetColor(30, 60, 30); }
inline void lightGreen() { iSetColor(75, 120, 55); }
inline void pants() { iSetColor(80, 60, 45); }
inline void boot() { iSetColor(45, 40, 35); }
inline void beltColor() { iSetColor(75, 50, 30); }
inline void black() { iSetColor(20, 20, 20); }


// ======================================================
// SHADOW
// ======================================================

inline void drawShadow(double x, double y)
{
	iSetColor(25, 30, 25);
	iFilledEllipse(x, y - 1.5, 11.4, 2.1);
}


// ======================================================
// LIMB DRAWING
// ======================================================

inline void drawLimb(double jointX, double jointY, double length, double width, double angle)
{
	double rad = angle * PI / 180.0;
	double dx = sin(rad);
	double dy = -cos(rad);
	double px = cos(rad);
	double py = sin(rad);
	double halfWidth = width / 2.0;

	double x1 = jointX - px * halfWidth;
	double y1 = jointY - py * halfWidth;
	double x2 = jointX + px * halfWidth;
	double y2 = jointY + py * halfWidth;

	double endX = jointX + dx * length;
	double endY = jointY + dy * length;

	double x3 = endX + px * halfWidth;
	double y3 = endY + py * halfWidth;
	double x4 = endX - px * halfWidth;
	double y4 = endY - py * halfWidth;

	double xPoints[4] = { x1, x2, x3, x4 };
	double yPoints[4] = { y1, y2, y3, y4 };

	iFilledPolygon(xPoints, yPoints, 4);
}


// ======================================================
// LIMB END X & Y
// ======================================================

inline double limbEndX(double jointX, double length, double angle)
{
	double rad = angle * PI / 180.0;
	return jointX + sin(rad) * length;
}

inline double limbEndY(double jointY, double length, double angle)
{
	double rad = angle * PI / 180.0;
	return jointY - cos(rad) * length;
}


// ======================================================
// FRONT BOOT
// ======================================================

inline void drawFrontBoot(double x, double y, int side)
{
	double bx[4];
	double by[4];

	if (side < 0)
	{
		// LEFT FOOT
		bx[0] = x - 1.8; by[0] = y + 0.6;
		bx[1] = x + 1.5; by[1] = y + 0.6;
		bx[2] = x + 3.9; by[2] = y - 2.1;
		bx[3] = x - 2.1; by[3] = y - 2.1;
	}
	else
	{
		// RIGHT FOOT
		bx[0] = x - 1.5; by[0] = y + 0.6;
		bx[1] = x + 1.8; by[1] = y + 0.6;
		bx[2] = x + 2.1; by[2] = y - 2.1;
		bx[3] = x - 3.9; by[3] = y - 2.1;
	}
	iFilledPolygon(bx, by, 4);
}


// ======================================================
// SIDE BOOT
// ======================================================

inline void drawSideBoot(double x, double y, int direction)
{
	double bx[5];
	double by[5];

	if (direction < 0)
	{
		// LEFT FACING
		bx[0] = x - 0.9; by[0] = y + 0.9;
		bx[1] = x + 1.5; by[1] = y + 0.9;
		bx[2] = x - 3.0; by[2] = y - 1.8;
		bx[3] = x - 5.7; by[3] = y - 1.8;
		bx[4] = x - 4.2; by[4] = y + 0.3;
	}
	else
	{
		// RIGHT FACING
		bx[0] = x - 1.5; by[0] = y + 0.9;
		bx[1] = x + 0.9; by[1] = y + 0.9;
		bx[2] = x + 4.2; by[2] = y + 0.3;
		bx[3] = x + 5.7; by[3] = y - 1.8;
		bx[4] = x + 3.0; by[4] = y - 1.8;
	}
	iFilledPolygon(bx, by, 5);
}


// ======================================================
// FRONT VIEW
// ======================================================

inline void drawFront(double x, double y)
{
	double s = 0;
	if (playerWalking) s = sin(walkFrame);

	double leftLegAngle = s * 18;
	double rightLegAngle = -s * 18;
	double leftArmAngle = -s * 14;
	double rightArmAngle = s * 14;
	double bob = 0;

	if (playerWalking) bob = fabs(s) * 0.6;

	double hipY = y + 11.4;
	double shoulderY = y + 25.8 + bob;
	double headY = y + 38.4 + bob;

	double leftHipX = x - 2.7;
	double rightHipX = x + 2.7;
	double leftShoulderX = x - 7.5;
	double rightShoulderX = x + 7.5;

	drawShadow(x, y);

	// LEGS
	pants();
	drawLimb(leftHipX, hipY, LEG_LENGTH, LEG_WIDTH, leftLegAngle);
	pants();
	drawLimb(rightHipX, hipY, LEG_LENGTH, LEG_WIDTH, rightLegAngle);

	// FEET
	double leftFootX = limbEndX(leftHipX, LEG_LENGTH, leftLegAngle);
	double leftFootY = limbEndY(hipY, LEG_LENGTH, leftLegAngle);
	double rightFootX = limbEndX(rightHipX, LEG_LENGTH, rightLegAngle);
	double rightFootY = limbEndY(hipY, LEG_LENGTH, rightLegAngle);

	boot();
	drawFrontBoot(leftFootX, leftFootY, -1);
	boot();
	drawFrontBoot(rightFootX, rightFootY, 1);

	// BODY
	green();
	iFilledRectangle(x - 7.8, y + 12.0 + bob, 15.6, 15.6);
	darkGreen();
	iFilledRectangle(x - 7.8, y + 12.0 + bob, 15.6, 2.4);

	// ARMS
	darkGreen();
	drawLimb(leftShoulderX, shoulderY, ARM_LENGTH, ARM_WIDTH, leftArmAngle);
	green();
	drawLimb(rightShoulderX, shoulderY, ARM_LENGTH, ARM_WIDTH, rightArmAngle);

	// HANDS
	double leftHandX = limbEndX(leftShoulderX, ARM_LENGTH, leftArmAngle);
	double leftHandY = limbEndY(shoulderY, ARM_LENGTH, leftArmAngle);
	double rightHandX = limbEndX(rightShoulderX, ARM_LENGTH, rightArmAngle);
	double rightHandY = limbEndY(shoulderY, ARM_LENGTH, rightArmAngle);

	skin();
	iFilledCircle(leftHandX, leftHandY, 2.1);
	iFilledCircle(rightHandX, rightHandY, 2.1);

	// BELT
	beltColor();
	iFilledRectangle(x - 7.8, y + 17.7 + bob, 15.6, 1.8);

	// BUCKLE
	iSetColor(220, 180, 70);
	iFilledRectangle(x - 1.5, y + 17.1 + bob, 3.0, 3.0);

	// NECK
	skin();
	iFilledRectangle(x - 2.4, y + 27.3 + bob, 4.8, 3.3);

	// HOOD
	green();
	iFilledCircle(x, headY, HEAD_RADIUS);

	// FACE
	skin();
	iFilledEllipse(x, headY - 0.9, 6.9, 7.5);

	// HAIR
	hair();
	double hairX[7] = { x - 6.0, x - 4.5, x - 2.1, x, x + 2.1, x + 4.5, x + 6.0 };
	double hairY[7] = { headY + 4.2, headY + 6.9, headY + 8.1, headY + 6.9, headY + 8.1, headY + 6.9, headY + 4.2 };
	iFilledPolygon(hairX, hairY, 7);

	// EYES
	black();
	iFilledCircle(x - 2.4, headY - 0.3, 0.9);
	iFilledCircle(x + 2.4, headY - 0.3, 0.9);

	// SMILE
	iSetColor(100, 55, 45);
	iLine(x - 2.1, headY - 3.0, x - 1.2, headY - 3.6);
	iLine(x - 1.2, headY - 3.6, x, headY - 3.9);
	iLine(x, headY - 3.9, x + 1.2, headY - 3.6);
	iLine(x + 1.2, headY - 3.6, x + 2.1, headY - 3.0);
}


// ======================================================
// LEFT VIEW
// ======================================================

inline void drawLeft(double x, double y)
{
	double s = 0;
	if (playerWalking) s = sin(walkFrame);

	double frontLegAngle = s * 18;
	double backLegAngle = -s * 18;
	double frontArmAngle = -s * 14;
	double backArmAngle = s * 14;
	double bob = 0;

	if (playerWalking) bob = fabs(s) * 0.6;

	double hipY = y + 11.4;
	double shoulderY = y + 25.8 + bob;
	double headY = y + 38.4 + bob;

	double frontHipX = x - 1.2;
	double backHipX = x + 1.2;
	double frontShoulderX = x - 3.6;
	double backShoulderX = x + 3.6;

	drawShadow(x, y);

	pants();
	drawLimb(backHipX, hipY, LEG_LENGTH, LEG_WIDTH, backLegAngle);
	pants();
	drawLimb(frontHipX, hipY, LEG_LENGTH, LEG_WIDTH, frontLegAngle);

	double backFootX = limbEndX(backHipX, LEG_LENGTH, backLegAngle);
	double backFootY = limbEndY(hipY, LEG_LENGTH, backLegAngle);
	double frontFootX = limbEndX(frontHipX, LEG_LENGTH, frontLegAngle);
	double frontFootY = limbEndY(hipY, LEG_LENGTH, frontLegAngle);

	boot();
	drawSideBoot(backFootX, backFootY, -1);
	boot();
	drawSideBoot(frontFootX, frontFootY, -1);

	green();
	iFilledRectangle(x - 6.3, y + 12.0 + bob, 12.6, 15.6);

	darkGreen();
	drawLimb(backShoulderX, shoulderY, ARM_LENGTH, 2.7, backArmAngle);
	green();
	drawLimb(frontShoulderX, shoulderY, ARM_LENGTH, ARM_WIDTH, frontArmAngle);

	double handX = limbEndX(frontShoulderX, ARM_LENGTH, frontArmAngle);
	double handY = limbEndY(shoulderY, ARM_LENGTH, frontArmAngle);

	skin();
	iFilledCircle(handX, handY, 2.1);

	beltColor();
	iFilledRectangle(x - 6.3, y + 17.7 + bob, 12.6, 1.8);

	skin();
	iFilledRectangle(x - 3.9, y + 27.3 + bob, 3.9, 3.3);

	green();
	iFilledCircle(x - 1.2, headY, 9.9);

	skin();
	iFilledEllipse(x - 4.8, headY - 0.9, 6.3, 7.5);
	iFilledEllipse(x - 10.8, headY - 0.9, 2.1, 1.5);

	black();
	iFilledCircle(x - 7.5, headY - 0.3, 0.9);

	hair();
	double leftHairX[6] = { x - 2.4, x - 3.9, x - 5.4, x - 5.7, x - 4.5, x - 2.1 };
	double leftHairY[6] = { headY + 5.4, headY + 7.5, headY + 6.0, headY + 3.0, headY + 4.5, headY + 4.8 };
	iFilledPolygon(leftHairX, leftHairY, 6);
}


// ======================================================
// RIGHT VIEW
// ======================================================

inline void drawRight(double x, double y)
{
	double s = 0;
	if (playerWalking) s = sin(walkFrame);

	double frontLegAngle = s * 18;
	double backLegAngle = -s * 18;
	double frontArmAngle = -s * 14;
	double backArmAngle = s * 14;
	double bob = 0;

	if (playerWalking) bob = fabs(s) * 0.6;

	double hipY = y + 11.4;
	double shoulderY = y + 25.8 + bob;
	double headY = y + 38.4 + bob;

	double frontHipX = x + 1.2;
	double backHipX = x - 1.2;
	double frontShoulderX = x + 3.6;
	double backShoulderX = x - 3.6;

	drawShadow(x, y);

	pants();
	drawLimb(backHipX, hipY, LEG_LENGTH, LEG_WIDTH, backLegAngle);
	pants();
	drawLimb(frontHipX, hipY, LEG_LENGTH, LEG_WIDTH, frontLegAngle);

	double backFootX = limbEndX(backHipX, LEG_LENGTH, backLegAngle);
	double backFootY = limbEndY(hipY, LEG_LENGTH, backLegAngle);
	double frontFootX = limbEndX(frontHipX, LEG_LENGTH, frontLegAngle);
	double frontFootY = limbEndY(hipY, LEG_LENGTH, frontLegAngle);

	boot();
	drawSideBoot(backFootX, backFootY, 1);
	boot();
	drawSideBoot(frontFootX, frontFootY, 1);

	green();
	iFilledRectangle(x - 6.3, y + 12.0 + bob, 12.6, 15.6);

	darkGreen();
	drawLimb(backShoulderX, shoulderY, ARM_LENGTH, 2.7, backArmAngle);
	green();
	drawLimb(frontShoulderX, shoulderY, ARM_LENGTH, ARM_WIDTH, frontArmAngle);

	double handX = limbEndX(frontShoulderX, ARM_LENGTH, frontArmAngle);
	double handY = limbEndY(shoulderY, ARM_LENGTH, frontArmAngle);

	skin();
	iFilledCircle(handX, handY, 2.1);

	beltColor();
	iFilledRectangle(x - 6.3, y + 17.7 + bob, 12.6, 1.8);

	skin();
	iFilledRectangle(x, y + 27.3 + bob, 3.9, 3.3);

	green();
	iFilledCircle(x + 1.2, headY, 9.9);

	skin();
	iFilledEllipse(x + 4.8, headY - 0.9, 6.3, 7.5);
	iFilledEllipse(x + 10.8, headY - 0.9, 2.1, 1.5);

	black();
	iFilledCircle(x + 7.5, headY - 0.3, 0.9);

	hair();
	double rightHairX[6] = { x + 2.4, x + 3.9, x + 5.4, x + 5.7, x + 4.5, x + 2.1 };
	double rightHairY[6] = { headY + 5.4, headY + 7.5, headY + 6.0, headY + 3.0, headY + 4.5, headY + 4.8 };
	iFilledPolygon(rightHairX, rightHairY, 6);
}


// ======================================================
// BACK VIEW
// ======================================================

inline void drawBack(double x, double y)
{
	double s = 0;
	if (playerWalking) s = sin(walkFrame);

	double leftLegAngle = s * 18;
	double rightLegAngle = -s * 18;
	double leftArmAngle = -s * 14;
	double rightArmAngle = s * 14;
	double bob = 0;

	if (playerWalking) bob = fabs(s) * 0.6;

	double hipY = y + 11.4;
	double shoulderY = y + 25.8 + bob;
	double headY = y + 38.4 + bob;

	drawShadow(x, y);

	pants();
	drawLimb(x - 2.7, hipY, LEG_LENGTH, LEG_WIDTH, leftLegAngle);
	pants();
	drawLimb(x + 2.7, hipY, LEG_LENGTH, LEG_WIDTH, rightLegAngle);

	double leftFootX = limbEndX(x - 2.7, LEG_LENGTH, leftLegAngle);
	double leftFootY = limbEndY(hipY, LEG_LENGTH, leftLegAngle);
	double rightFootX = limbEndX(x + 2.7, LEG_LENGTH, rightLegAngle);
	double rightFootY = limbEndY(hipY, LEG_LENGTH, rightLegAngle);

	boot();
	drawFrontBoot(leftFootX, leftFootY, -1);
	boot();
	drawFrontBoot(rightFootX, rightFootY, 1);

	green();
	iFilledRectangle(x - 7.8, y + 12.0 + bob, 15.6, 15.6);
	black();
	iFilledRectangle(x - 6.3, y + 14.4 + bob, 12.6, 11.4);
	lightGreen();
	iFilledRectangle(x - 5.1, y + 24.3 + bob, 10.2, 1.2);

	iLine(x - 5.4, y + 24.6 + bob, x - 2.7, y + 15.9 + bob);
	iLine(x + 5.4, y + 24.6 + bob, x + 2.7, y + 15.9 + bob);

	green();
	drawLimb(x - 7.5, shoulderY, ARM_LENGTH, ARM_WIDTH, leftArmAngle);
	green();
	drawLimb(x + 7.5, shoulderY, ARM_LENGTH, ARM_WIDTH, rightArmAngle);

	double leftHandX = limbEndX(x - 7.5, ARM_LENGTH, leftArmAngle);
	double leftHandY = limbEndY(shoulderY, ARM_LENGTH, leftArmAngle);
	double rightHandX = limbEndX(x + 7.5, ARM_LENGTH, rightArmAngle);
	double rightHandY = limbEndY(shoulderY, ARM_LENGTH, rightArmAngle);

	skin();
	iFilledCircle(leftHandX, leftHandY, 2.1);
	iFilledCircle(rightHandX, rightHandY, 2.1);

	skin();
	iFilledRectangle(x - 2.4, y + 27.3 + bob, 4.8, 3.3);

	green();
	iFilledCircle(x, headY, 10.2);
}


// ======================================================
// PLAYER CONTROLLER
// ======================================================


// Health Bar
inline void drawPlayer()
{
	if (playerIFrames > 0) {
		
		if (playerIFrames % 4 < 2) return;
	}
	if (playerDirection == 0) drawFront(playerX, playerY);
	else if (playerDirection == 1) drawLeft(playerX, playerY);
	else if (playerDirection == 2) drawRight(playerX, playerY);
	else drawBack(playerX, playerY);
}

void drawHealthUI() {
	int fullHearts = playerHealth / 2;
	int hasHalfHeart = playerHealth % 2;
	int maxHearts = maxHealth / 2;

	for (int i = 0; i < maxHearts; i++) {
		int xPos = 20 + (i * 40);
		int yPos = 938;

		if (i < fullHearts) {
			// Full Heart Image
			if (heartFullImg != -1) {
				iShowImage(xPos, yPos, 24, 24, heartFullImg);
			}
		}
		else if (i == fullHearts && hasHalfHeart == 1) {
			// Half Heart Image
			if (heartHalfImg != -1) {
				iShowImage(xPos, yPos, 24, 24, heartHalfImg);
			}
		}
	}
}





#endif // MYSTIC_GROVE_HPP