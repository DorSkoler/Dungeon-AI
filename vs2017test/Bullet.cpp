#include "Bullet.h"
#include "glut.h"
#include <math.h>
#include <iostream>


Bullet::Bullet()
{
}

// angle must be in radians
Bullet::Bullet(double x, double y, double angle, int t)
{
	this->x = x;
	this->y = y;
	direction_angle = angle;
	isMoving = 0;
	team = t;
	hitX = -1;
	hitY = -1;
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

Bullet::~Bullet()
{
}

bool checkHit(int maze[MSZ][MSZ], int cx, int cy)
{
	for (int i = BEGIN_COUNT_TEAM_A; i < BEGIN_COUNT_TEAM_A + 6; i++)
	{
		if (maze[(int)cy][(int)cx] == i)
			return true;
	}
	return false;
}

void Bullet::Move(int maze[MSZ][MSZ])
{
	double dx, dy;
	if (isMoving == 1)
	{
		dx = cos(direction_angle);
		dy = sin(direction_angle);
		x += dx * SPEED_BULLET;
		y += dy * SPEED_BULLET;
		if (maze[(int)y][(int)x] == WALL || maze[(int)y][(int)x] == PASS)
			isMoving++;
		if (checkHit(maze, x, y)) {
			hitX = x;
			hitY = y;
		}
	}
}

void Bullet::SimulateMotion(int maze[MSZ][MSZ], double security_map[MSZ][MSZ], double damage)
{
	double dx, dy;
	dx = cos(direction_angle);
	dy = sin(direction_angle);
	while (isMoving)
	{
		x += dx * SPEED_BULLET;
		y += dy * SPEED_BULLET;

		security_map[(int)y][(int)x] += damage; // drawing in map

		if (maze[(int)y][(int)x] == WALL)
			isMoving = false;
	}

}

void Bullet::SimulateVisibility(int maze[MSZ][MSZ], double visibility_map[MSZ][MSZ])
{
	double dx, dy;
	dx = cos(direction_angle);
	dy = sin(direction_angle);
	while (isMoving)
	{
		x += dx * SPEED_BULLET;
		y += dy * SPEED_BULLET;

		visibility_map[(int)y][(int)x] = 1; // drawing in map

		if (maze[(int)y][(int)x] == WALL)
			isMoving = false;
	}

}
