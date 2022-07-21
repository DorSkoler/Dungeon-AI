#include "Magazine.h"
#include <iostream>

Magazine::Magazine()
{
	for (int i = 0; i < NUM_BULLETS_PER_MAGAZINE; i++)
		bullets.push_back(new Bullet());
}

void Magazine::fire(double x, double y, double angle, int t, int sX, int sY)
{
	if (!bullets.empty()) {
		bullets.pop_back();
		bullets.push_back(new Bullet(x, y, angle, t, sX, sY));
		bullets.back()->Fire();
	}
}

void Magazine::fire(double x, double y, double dx, double dy, int t)
{
	if (!bullets.empty()) {
		bullets.pop_back();
		bullets.push_back(new Bullet(x, y, dx, dy, t));
		bullets.back()->Fire();
	}
}

void Magazine::show()
{
	if (bullets.back()->getIsMoving() == 1)
		bullets.back()->show();
}

bool Magazine::Move(int maze[MSZ][MSZ], int hits[NUM_PLAYERS])
{
	if (bullets.back()->getIsMoving() == 1)
		bullets.back()->Move(maze, hits);

	if (bullets.back()->getIsMoving() == 2) {
		bullets.pop_back();
		return false;
	}
	return true;
}
