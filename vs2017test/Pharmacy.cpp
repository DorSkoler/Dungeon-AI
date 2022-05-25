#include "Pharmacy.h"
#include "glut.h"

Pharmacy::Pharmacy(double cx, double cy)
{
	x = cx;
	y = cy;
}

// return the amount taken
int Pharmacy::updateStock(int s)
{
	int num = stock;
	if (s > stock) {
		stock = 0;
		return num;
	}
	stock -= s;
	return s;
}

void Pharmacy::DrawMe()
{
	// draw pharmacy
	glColor3d(1, 1, 1); // white
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

	glColor3d(1, 0, 0); // door
	glBegin(GL_POLYGON);
	glVertex2d(x - 0.5, y);
	glVertex2d(x - 0.5, y + 2);
	glVertex2d(x + 0.5, y + 2);
	glVertex2d(x + 0.5, y);
	glEnd();

	// pharmacy text
	glColor3d(0, 0, 0);
	unsigned char string[] = "Pharmacy";
	int w;
	w = glutBitmapLength(GLUT_BITMAP_8_BY_13, string);
	glRasterPos2f(x - 2.4, y + 3.3);
	for (int i = 0; i < 8; i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
	}
}
