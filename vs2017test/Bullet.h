#pragma once
#include "Definitions.h"


class Bullet
{

private:
	double x, y;
	double dx, dy;
	double direction_angle;
	int isMoving;
	int bullet_team;
	int sourceX, sourceY;
public:
	Bullet();
	Bullet(double x, double y, double angle, int t, int sX, int sY);
	Bullet(double x, double y, double dx, double dy, int t);
	void show();
	~Bullet();
	bool checkHit(int maze[MSZ][MSZ], int cx, int cy, int hits[NUM_PLAYERS]);
	void Fire() { isMoving++; }
	void Move(int maze[MSZ][MSZ], int hits[NUM_PLAYERS]);
	int getIsMoving() { return isMoving; }
	void SimulateMotion(int maze[MSZ][MSZ], double security_map[MSZ][MSZ], double damage);
	void SimulateVisibility(int maze[MSZ][MSZ], double visibility_map[MSZ][MSZ]);

};

