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
	int myMazeNum;
	double x, y;
	double xForInfo, yForInfo;
	double targetX, targetY;
	double dx, dy; // vector to the target
	int hp;
	int team;
	double direction_angle;
	int spaceOrPass;
	int grenade_count;
	bool isMoving, isShooting, isFilling;
	bool idle, fighting, fillAmmo, fillHp, helping;
	std::vector<Magazine*> magazines;
	State* pCurrentState;
	State* pInterruptedState;
public:
	NPC();
	NPC(double cx, double cy, int t);
	void DrawMe();
	void drawInfo();
	int getHp() { return hp; }
	double getTargetX() { return targetX; }
	double getTargetY() { return targetY; }
	double getX() { return x; }
	double getY() { return y; }
	double getAngle() { return direction_angle; }
	double getInfoY() { return yForInfo; }
	double getInfoX() { return xForInfo; }
	int getTeam() { return team; }
	int getMagazinesLeft() { return magazines.size(); }
	int getGrenadeCount() { return grenade_count; }
	bool Move(int maze[MSZ][MSZ]);

	void setDirectionAngle(double direction) { direction_angle = direction; };
	State* getCurrentState() { return pCurrentState; }
	State* getInterruptedState() { return pInterruptedState; }
	void setCurrentState(State* ps) { pCurrentState = ps; }
	void setInterruptedState(State* ps) { pInterruptedState = ps; }
	void setMazeNum(int num) { myMazeNum = num; }
	void setIsMoving(bool value) { isMoving = value; }
	void setIsShooting(bool value) { isShooting = value; }
	void setIsFilling(bool value) { isFilling = value; }
	void setIdle(bool value) { idle = value; }
	void setFighting(bool value) { fighting = value; }
	void setFillAmmo(bool value) { fillAmmo = value; }
	void setFillHp(bool value) { fillHp = value; }
	void setHelping(bool value) { helping = value; }
	void setDestination(double destX, double destY);
	bool isThisXandYisNPC(int cx, int cy);
	void setHp(int _hp);
	void setInfoXandY(int cx, int cy) { xForInfo = cx; yForInfo = cy; }
};

