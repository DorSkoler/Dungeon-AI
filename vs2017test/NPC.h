#pragma once
#include "State.h"
#include "Definitions.h"
#include "Bullet.h"
#include "Magazine.h"
#include "Grenade.h"

class NPC
{
protected:
	double x, y;
	double targetX, targetY;
	double dx, dy; // vector to the target
	int hp;
	int team;
	Magazine *magazines;
	Grenade *grenades;
	/*State* pCurrentState;
	State* pInterruptedState;*/
public:
	void DrawMe();
	int getHp() { return hp; };

	void setHp(int _hp) { hp = _hp; };
	void setXandY(int cx, int cy) { x = cx; y = cy; };
};

