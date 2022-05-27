#include "Soldier.h"
#include "NPC.h"
#include "glut.h"
#include <math.h>

Soldier::Soldier()
{
}

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
	grenade_count = MAX_GRENADES_SOLDIER;
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

bool Soldier::Move(int maze[MSZ][MSZ])
{
	double dx, dy, nextX = x, nextY = y;
	dx = cos(direction_angle);
	dy = sin(direction_angle);
	nextX = x + dx * SPEED_SOLDIER;
	nextY = y + dy * SPEED_SOLDIER;
	if (maze[(int)y][(int)x] != WALL)
	{
		maze[(int)y][(int)x] = spaceOrPass;
		spaceOrPass = maze[(int)nextY][(int)nextX];
		maze[(int)nextY][(int)nextX] = SOLDIER;
		x = nextX;
		y = nextY;
		return true;
	}
	return false;
}
