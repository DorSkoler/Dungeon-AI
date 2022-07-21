#pragma once
#include "Soldier.h"
#include "Definitions.h"
#include "Room.h"
#include "ArmourBearer.h"

class Team
{
private:
	Soldier * s1 = nullptr;
	Soldier * s2 = nullptr;
	ArmourBearer * ab = nullptr;
	int team_num;
	int x, y;
	bool allDead = false;
public:
	Team(int t, Room* r, int maze[MSZ][MSZ], int begin);
	void drawTeam();
	void setTeamInfo(int cx, int cy);
	void drawInfo();
	Soldier* getSoldier1() { return s1; }
	Soldier* getSoldier2() { return s2; }
	ArmourBearer* getAB() { return ab; }
	void gotHit(int hits[NUM_PLAYERS]);
	void checkMoveBullets(int maze[MSZ][MSZ], int hits[NUM_PLAYERS]);
	void checkShowBullets();
	bool checkAlive(int maze[MSZ][MSZ]);
	void doSomething(Team* enemy, int maze[MSZ][MSZ], Room rooms[NUM_ROOMS]);
	int* getRoomsOfNpc(Room rooms[NUM_ROOMS]);
	NPC* getNpcByIndex(int index);
};

