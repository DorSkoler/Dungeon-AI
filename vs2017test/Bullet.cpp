#include "Bullet.h"
#include "glut.h"
#include "NPC.h"
#include <math.h>
#include <iostream>


Bullet::Bullet()
{
	x = -1;
	y = -1;
}

// angle must be in radians
Bullet::Bullet(double x, double y, double angle, int t, int sX, int sY)
{
	this->x = x;
	this->y = y;
	direction_angle = angle;
	dx = cos(direction_angle);
	dy = sin(direction_angle);
	isMoving = 0;
	bullet_team = t;
	sourceX = sX;
	sourceY = sY;
}


void Bullet::show()
{
	glColor3d(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2d(x - 0.5, y);
	glVertex2d(x , y + 0.5);
	glVertex2d(x + 0.5, y);
	glVertex2d(x , y - 0.5);
	glEnd();
}

Bullet::Bullet(double x, double y, double dx, double dy, int t)
{
	this->x = x;
	this->y = y;
	isMoving = 0;
	bullet_team = t;
	sourceX = (int)x;
	sourceY = (int)y;
	this->dx = dx;
	this->dy = dy;
}

Bullet::~Bullet()
{
}

bool Bullet::checkHit(int maze[MSZ][MSZ], int cx, int cy, int hits[NUM_PLAYERS])
{
	for (int i = BEGIN_COUNT_TEAM_A; i < BEGIN_COUNT_TEAM_A + 6; i++)
	{
		if (maze[(int)(cy)][(int)(cx)] == i) {
			if ((bullet_team == 1 && i > 7) || (bullet_team == 2 && i < 8)) {
				int distance = sqrt(pow(sourceX - cx, 2) + pow(sourceY - cy, 2));
				hits[i - BEGIN_COUNT_TEAM_A] = distance;
				return true;
			}
		}
	}
	return false;
}

void Bullet::Move(int maze[MSZ][MSZ], int hits[NUM_PLAYERS])
{
	if (isMoving == 1)
	{
		x += dx * SPEED_BULLET;
		y += dy * SPEED_BULLET;
		if (maze[(int)y][(int)x] == WALL || maze[(int)y][(int)x] == PASS)
			isMoving++;
		checkHit(maze, x, y, hits);
	}
}

void Bullet::SimulateMotion(const int maze[MSZ][MSZ], double security_map[MSZ][MSZ], double damage)
{
	double dx, dy;
	dx = cos(direction_angle);
	dy = sin(direction_angle);
	while (isMoving)
	{
		x += dx * SPEED_BULLET;
		y += dy * SPEED_BULLET;

		security_map[(int)y][(int)x] += damage; // drawing in map

		if (maze[(int)y][(int)x] == WALL || maze[(int)y][(int)x] == PASS)
			isMoving = false;
	}

}

void Bullet::SimulateVisibility(const int maze[MSZ][MSZ], double visibility_map[MSZ][MSZ])
{
	double dx, dy;
	dx = cos(direction_angle);
	dy = sin(direction_angle);
	while (isMoving)
	{
		x += dx * SPEED_BULLET;
		y += dy * SPEED_BULLET;

		visibility_map[(int)y][(int)x] = 1; // drawing in map

		if (maze[(int)y][(int)x] == WALL || maze[(int)y][(int)x] == PASS)
			isMoving = false;
	}

}
