#include "NPC.h"
#include "glut.h"
#include "Definitions.h"
#include <math.h>
#include <iostream>

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
