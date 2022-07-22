#pragma once
#include "Bullet.h"
#include "Definitions.h"


class Grenade
{

private: 
	double x, y;
	Bullet* bullets[NUM_BULLETS_PER_GRENADE];
	bool isExploded;
	Bullet* hit = nullptr;
public:
	Grenade();
	Grenade(double x, double y, int t, int sX, int sY);
	~Grenade();
	void setXandY(int cx, int cy) {  }
	bool getIsExploded() { return isExploded; }
	void Explode();
	Bullet* getHit() { return hit; };
	bool Exploding(int maze[MSZ][MSZ], int hits[NUM_PLAYERS]);
	void show();
	void SimulateExplosion(int maze[MSZ][MSZ], double security_map[MSZ][MSZ], double damage);
	void SimulateVisibility(int maze[MSZ][MSZ], double visibility_map[MSZ][MSZ]);
};

