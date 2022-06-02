#pragma once
#include "Soldier.h"
#include "Definitions.h"
#include "Room.h"
#include "ArmourBearer.h"

class Team
{
private:
	Soldier *s1;
	Soldier *s2;
	ArmourBearer *ab;
	int team_num;
	int x, y;
	bool allDead = false;
public:
	Team(int t, Room* r, int maze[MSZ][MSZ], int begin);
	void drawTeam();
	void setTeamInfo(int cx, int cy);
	void drawInfo();
	Soldier* getSoldier1() { return s1; };
	Soldier* getSoldier2() { return s2; };
	ArmourBearer* getAB() { return ab; };
	void gotHit(int cx, int cy);
	std::vector<Bullet*> checkMoveBullets(int maze[MSZ][MSZ]);
	void checkShowBullets();
	bool checkAlive();
};

