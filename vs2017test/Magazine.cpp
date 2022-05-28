#include "Magazine.h"

Magazine::Magazine()
{
	for (int i = 0; i < NUM_BULLETS_PER_MAGAZINE; i++)
		bullets.push_back(new Bullet());
}

void Magazine::fire(double x, double y, double angle, int t)
{
	if (!bullets.empty()) {
		bullets.pop_back();
		bullets.push_back(new Bullet(x, y, angle, t));
		bullets.back()->Fire();
	}
}

void Magazine::show()
{
	if (bullets.back()->getIsMoving() == 1)
		bullets.back()->show();
}

bool Magazine::Move(int maze[MSZ][MSZ])
{
	if (bullets.back()->getIsMoving() == 1)
		bullets.back()->Move(maze);
	if (bullets.back()->getIsMoving() == 2) {
		if (bullets.back()->getHitX() > -1)
			hit = bullets.back();
		bullets.pop_back();
		return false;
	}
	return true;
}
