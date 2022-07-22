#include "Arsenal.h"
#include "glut.h"

Arsenal::Arsenal(double cx, double cy)
{
	x = cx;
	y = cy;
}

void Arsenal::DrawMe()
{
	// draw arsenal
	glColor3d(0.7, 0.4, 0); // brown
	glBegin(GL_POLYGON);
	glVertex2d(x - 2, y);
	glVertex2d(x - 2, y + 3);
	glVertex2d(x + 2, y + 3);
	glVertex2d(x + 2, y);
	glEnd();
	glColor3d(0, 0, 0); //frame
	glBegin(GL_LINE_LOOP);
	glVertex2d(x - 2, y);
	glVertex2d(x - 2, y + 3);
	glVertex2d(x + 2, y + 3);
	glVertex2d(x + 2, y);
	glEnd();

	glColor3d(0.6, 0.2, 0); // door
	glBegin(GL_POLYGON);
	glVertex2d(x - 0.5, y);
	glVertex2d(x - 0.5, y + 2);
	glVertex2d(x + 0.5, y + 2);
	glVertex2d(x + 0.5, y);
	glEnd();

	// arsenal text
	glColor3d(0, 0, 0);
	unsigned char string[] = "Arsenal";
	int w;
	w = glutBitmapLength(GLUT_BITMAP_8_BY_13, string);
	glRasterPos2f(x - 2.2, y + 3.3);
	for (int i = 0; i < 8; i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
	}
}
