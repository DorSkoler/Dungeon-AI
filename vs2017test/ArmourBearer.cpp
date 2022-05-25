#include "ArmourBearer.h"
#include "NPC.h"
#include "glut.h"
#include "Definitions.h"
#include <math.h>

ArmourBearer::ArmourBearer(double cx, double cy, int t)
{
	init();
	x = cx;
	y = cy;
	team = t;
}

ArmourBearer::~ArmourBearer()
{
}

void ArmourBearer::init()
{
	hp = MAX_HP_AB;
	magazines[MAX_MAGAZINE_AB];
	grenades[MAX_GRENADES_AB];
}

void ArmourBearer::DrawMe()
{
	NPC::DrawMe();

	// cart
	glBegin(GL_LINE_STRIP);
	glVertex2d(x - 3, y);
	glVertex2d(x - 2, y - 1);
	glVertex2d(x - 0.5, y - 1);
	glVertex2d(x - 0.5, y);
	glEnd();

	// hp bar
	glLineWidth(3);
	glColor3d(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(x - 0.7, y + 3);
	glVertex2d(x - 0.7 + 2 * hp / MAX_HP_AB, y + 3);
	glEnd();
}
