#include "NPC.h"
#include "glut.h"
#include "Definitions.h"
#include <math.h>
#include <iostream>
#include <string>

void NPC::DrawMe()
{
	if (team == TEAM_RED)
		glColor3d(1, 0, 0);
	else
		glColor3d(0, 0, 1);

	// head
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	double r = 0.5;
	for (int i = 0; i < 100; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(100);//get the current angle 
		float cx = r * cosf(theta);//calculate the x component 
		float cy = r * sinf(theta);//calculate the y component 
		glVertex2f(cx + x + 0.3, cy + y + 2);//output vertex 
	}
	glEnd();

	// body
	glBegin(GL_LINES);
	glVertex2d(x + 0.3, y + 1.4);
	glVertex2d(x + 0.3, y);
	glEnd();

	// right leg
	glBegin(GL_LINES);
	glVertex2d(x + 0.3, y);
	glVertex2d(x + 1, y - 1);
	glEnd();

	// left leg
	glBegin(GL_LINES);
	glVertex2d(x + 0.3, y);
	glVertex2d(x - 0.4, y - 1);
	glEnd();

	// left arm
	glBegin(GL_LINES);
	glVertex2d(x + 0.3, y + 1);
	glVertex2d(x - 0.4, y);
	glEnd();

	// right arm
	glBegin(GL_LINES);
	glVertex2d(x + 0.3, y + 1);
	glVertex2d(x + 1, y);
	glEnd();
}

NPC::NPC()
{
	direction_angle = (rand() % 360) * 3.14 / 180;
	spaceOrPass = SPACE;
}

void NPC::setDestination(double destX, double destY)
{
	double distance;
	targetX = destX;
	targetY = destY;
	distance = sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));
	// [dx,dy] must be vector of length 1 to the direction to target
	dx = (targetX - x) / distance;
	dy = (targetY - y) / distance;
}

void NPC::drawInfo()
{
	glColor3d(0, 0, 0);
	unsigned char string[] = "| Grenades -";
	int w = glutBitmapLength(GLUT_BITMAP_8_BY_13, string);
	glRasterPos2f(xForInfo + 21, yForInfo - 1);
	for (int i = 0; i < 13; i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
	}

	unsigned char string1[] = "| Magazines -";
	w = glutBitmapLength(GLUT_BITMAP_8_BY_13, string1);
	glRasterPos2f(xForInfo + 21, yForInfo - 6);
	for (int i = 0; i < 14; i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string1[i]);
	}

	std::string tmp = std::to_string(magazines.size());
	char const* num_char = tmp.c_str();
	w = glutBitmapLength(GLUT_BITMAP_8_BY_13, (unsigned char*)num_char);
	glRasterPos2f(xForInfo + 48, yForInfo - 6);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, num_char[0]);


	w = glutBitmapLength(GLUT_BITMAP_8_BY_13, (unsigned char*)"\\");
	glRasterPos2f(xForInfo + 51, yForInfo - 6);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '\\');
	
	glRasterPos2f(xForInfo + 51, yForInfo - 1);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '\\');

	std::string tmp1 = std::to_string(grenade_count);
	char const* num_char1 = tmp1.c_str();
	w = glutBitmapLength(GLUT_BITMAP_8_BY_13, (unsigned char*)num_char1);
	glRasterPos2f(xForInfo + 48, yForInfo - 1);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, num_char1[0]);
}

NPC::NPC(double cx, double cy, int t)
{
	x = cx;
	y = cy;
	team = t;
}


