#pragma once
#include "Bullet.h"
#include "Definitions.h"

class Magazine
{
private:
	Bullet *bullets[NUM_BULLETS_PER_MAGAZINE];
	int bullets_left = NUM_BULLETS_PER_MAGAZINE;
public:
	Magazine();
	void fire();
	int getBulletsLeft() { return bullets_left; };
	bool isEmpty() { return bullets_left == 0; };
};

