#pragma once
#include "Definitions.h"
#include "Bullet.h"
#include "Magazine.h"
#include "Grenade.h"
#include <stdlib.h>
#include <vector>
#include "State.h"

class State;
class NPC
{
protected:
	double x, y;
	double xForInfo, yForInfo;
	double targetX, targetY;
	double dx, dy; // vector to the target
	int hp;
	int team;
	double direction_angle;
	int spaceOrPass;
	int grenade_count;
	std::vector<Magazine*> magazines;
	State* pCurrentState;
	State* pInterruptedState;
public:
	NPC();
	NPC(double cx, double cy, int t);
	void DrawMe();
	void drawInfo();
	int getHp() { return hp; };
	double getTargetX() { return targetX; };
	double getTargetY() { return targetY; };
	double getX() { return x; };
	double getY() { return y; };
	double getAngle() { return direction_angle; };
	double getInfoY() { return yForInfo; };
	double getInfoX() { return xForInfo; };
	int getTeam() { return team; };
	int getMagazinesLeft() { return magazines.size(); };
	int getGrenadeCount() { return grenade_count; };

	void setDestination(double destX, double destY);
	bool isThisXandYisNPC(int cx, int cy) { return y == cy && x == cx; };
	void setHp(int _hp) { hp = _hp; };
	void setInfoXandY(int cx, int cy) { xForInfo = cx; yForInfo = cy; };
};

