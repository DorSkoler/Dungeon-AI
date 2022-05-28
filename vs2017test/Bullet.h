#pragma once
#include "Definitions.h"
const double SPEED_BULLET = 0.1;

class Bullet
{

private:
	double x, y;
	double direction_angle;
	int isMoving;
	int team;
	int hitX, hitY;
public:
	Bullet();
	Bullet(double x, double y, double angle, int t);
	void show();
	~Bullet();
	void Fire() { isMoving++; }
	void Move(int maze[MSZ][MSZ]);
	int getIsMoving() { return isMoving; }
	bool getHitX() { return hitX; }
	bool getHitY() { return hitY; }
	void SimulateMotion(int maze[MSZ][MSZ], double security_map[MSZ][MSZ], double damage);
	void SimulateVisibility(int maze[MSZ][MSZ], double visibility_map[MSZ][MSZ]);

};

