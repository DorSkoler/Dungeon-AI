#pragma once
#include "State.h"
#include "Definitions.h"
#include "Bullet.h"
#include "Magazine.h"
#include "Grenade.h"
#include <stdlib.h>
#include <vector>

class NPC
{
protected:
	double x, y;
	double targetX, targetY;
	double dx, dy; // vector to the target
	int hp;
	int team;
	double direction_angle = (rand() % 360) * 3.14 / 180;
	int spaceOrPass = SPACE;
	int grenade_count;
	std::vector<Magazine*> magazines;
	/*State* pCurrentState;
	State* pInterruptedState;*/
public:
	void DrawMe();
	int getHp() { return hp; };
	double getTargetX() { return targetX; };
	double getTargetY() { return targetY; };
	int getMagazinesLeft() { return magazines.size(); };
	int getGrenadeCount() { return grenade_count; };

	void setHp(int _hp) { hp = _hp; };
	void setTargetX(int cx) { targetX = cx; };
	void setTargetY(int cy) { targetY = cy; };

};

