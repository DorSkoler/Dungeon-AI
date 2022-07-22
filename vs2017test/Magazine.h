#pragma once
#include <vector>
#include "Definitions.h"

class Bullet;
class Magazine
{
private:
	std::vector <Bullet*> bullets;
	Bullet* hit = nullptr;
public:
	Magazine();
	void fire(double x, double y, double angle, int t, int sX, int sY);
	void fire(double x, double y, double dx, double dy, int t);
	void show();
	bool Move(int maze[MSZ][MSZ], int hits[NUM_PLAYERS]);
	Bullet* getHit() { return hit; };
	int getBulletsLeft() { return bullets.size(); };
	bool isEmpty() { return bullets.empty(); };
};

