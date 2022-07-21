#include "Grenade.h"
#include <math.h>

Grenade::Grenade()
{
}

Grenade::Grenade(double x, double y, int t, int sX, int sY)
{
	double teta = 2 * 3.14 / NUM_BULLETS_PER_GRENADE;
	this->x = x;
	this->y = y;
	for (int i = 0; i < NUM_BULLETS_PER_GRENADE; i++)
		bullets[i] = new Bullet(x, y, i*teta, t, sX, sY);

	isExploded = false;
}


Grenade::~Grenade()
{
}

void Grenade::Explode()
{
	isExploded = true;
	for (int i = 0; i < NUM_BULLETS_PER_GRENADE; i++)
		bullets[i]->Fire();
}

bool Grenade::Exploding(int maze[MSZ][MSZ], int hits[NUM_PLAYERS])
{
	bool done = true;
	if (isExploded)
		for (int i = 0; i < NUM_BULLETS_PER_GRENADE; i++) {
			bullets[i]->Move(maze, hits);
			done &= (bullets[i]->getIsMoving() == 2);
		}
	return done;
}

void Grenade::show()
{
	for (int i = 0; i < NUM_BULLETS_PER_GRENADE; i++)
		bullets[i]->show();
}

void Grenade::SimulateExplosion(int maze[MSZ][MSZ], double security_map[MSZ][MSZ], double damage)
{
	int i;

	for (i = 0; i < NUM_BULLETS_PER_GRENADE; i++)
		bullets[i]->Fire();

	for (i= 0; i < NUM_BULLETS_PER_GRENADE; i++)
		bullets[i]->SimulateMotion(maze, security_map, damage);

}

void Grenade::SimulateVisibility(int maze[MSZ][MSZ], double visibility_map[MSZ][MSZ])
{
	int i;

	for (i = 0; i < NUM_BULLETS_PER_GRENADE; i++)
		bullets[i]->Fire();

	for (i = 0; i < NUM_BULLETS_PER_GRENADE; i++)
		bullets[i]->SimulateVisibility(maze, visibility_map);

}
