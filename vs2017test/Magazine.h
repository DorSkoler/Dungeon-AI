#pragma once
#include "Bullet.h"
#include <vector>

class Magazine
{
private:
	std::vector <Bullet*> bullets;
	Bullet* hit = nullptr;
public:
	Magazine();
	void fire(double x, double y, double angle, int t);
	void show();
	bool Move(int maze[MSZ][MSZ]);
	Bullet* getHit() { return hit; };
	int getBulletsLeft() { return bullets.size(); };
	bool isEmpty() { return bullets.empty(); };
};

