#include "ArmourBearer.h"
#include "NPC.h"
#include "glut.h"
#include "Definitions.h"
#include <math.h>

ArmourBearer::ArmourBearer()
{
}

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
	grenade_count = MAX_GRENADES_AB;
	for (int i = 0; i < MAX_MAGAZINE_AB; i++)
		magazines.push_back(new Magazine());
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

bool ArmourBearer::Move(int maze[MSZ][MSZ])
{
	double dx, dy, nextX = x, nextY = y;
	dx = cos(direction_angle);
	dy = sin(direction_angle);
	nextX = x + dx * SPEED_AB;
	nextY = y + dy * SPEED_AB;
	if (maze[(int)y][(int)x] != WALL)
	{
		maze[(int)y][(int)x] = spaceOrPass;
		spaceOrPass = maze[(int)nextY][(int)nextX];
		maze[(int)nextY][(int)nextX] = ARMOURBEARER;
		x = nextX;
		y = nextY;
		return true;
	}
	return false;
}

bool ArmourBearer::getSupplies(int g, int m)
{
	if (magazines.size() + m > MAX_MAGAZINE_AB || g + grenade_count > MAX_GRENADES_AB)
		return false;
	for (int i = 0; i < m; i++)
		magazines.push_back(new Magazine());
	grenade_count += g;
}
