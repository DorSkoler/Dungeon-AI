#include "Soldier.h"
#include "NPC.h"
#include "glut.h"
#include <math.h>

Soldier::Soldier(double cx, double cy, int t)
{
	init();
	x = cx;
	y = cy;
	team = t;
}

void Soldier::init()
{
	hp = MAX_HP_SOLDIER;
	magazines[MAX_MAGAZINE_SOLDIER];
	grenades[MAX_GRENADES_SOLDIER];
}

void Soldier::DrawMe()
{
	NPC::DrawMe();

	// hp
	glLineWidth(3);
	glColor3d(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(x - 0.7, y + 3);
	glVertex2d(x - 0.7 + 2 * hp / MAX_HP_SOLDIER, y + 3);
	glEnd();
	glLineWidth(1);
}
